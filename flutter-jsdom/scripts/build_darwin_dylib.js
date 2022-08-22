const { execSync } = require('child_process');
const os = require('os');
const { join, resolve } = require('path');
const path = require('path');

const targetJSEngine = process.env.JSDOM_JS_ENGINE || 'quickjs';

const JSDOM_ROOT = join(__dirname, '..');
const TARGET_PATH = join(JSDOM_ROOT, 'targets');
const platform = os.platform();
const buildMode = process.env.WEBF_BUILD || 'Debug';
const paths = {
  targets: resolveJsdom('targets'),
  scripts: resolveJsdom('scripts'),
  example: resolveJsdom('webf/example'),
  webf: resolveJsdom('webf'),
  bridge: resolveJsdom('bridge'),
  polyfill: resolveJsdom('bridge/polyfill'),
  thirdParty: resolveJsdom('third_party'),
  tests: resolveJsdom('integration_tests'),
  sdk: resolveJsdom('sdk'),
  templates: resolveJsdom('scripts/templates'),
  performanceTests: resolveJsdom('performance_tests')
};

function resolveJsdom(submodule) {
  return resolve(JSDOM_ROOT, submodule);
}



function build() {
  let externCmakeArgs = [];
  let buildType = 'Debug';
  if (process.env.JSDOM_BUILD === 'Release') {
    buildType = 'RelWithDebInfo';
  }

  if (process.env.ENABLE_ASAN === 'true') {
    externCmakeArgs.push('-DENABLE_ASAN=true');
  }

  // Bundle quickjs into JSDOM.
  // if (program.staticQuickjs) {
  //   externCmakeArgs.push('-DSTATIC_QUICKJS=true');
  // }

  execSync(`cmake -DCMAKE_BUILD_TYPE=${buildType} -DENABLE_TEST=true ${externCmakeArgs.join(' ')} \
    -G "Unix Makefiles" -B ${paths.bridge}/cmake-build-macos-x86_64 -S ${paths.bridge}`, {
    cwd: paths.bridge,
    stdio: 'inherit',
    env: {
      ...process.env,
      JSDOM_JS_ENGINE: targetJSEngine,
      LIBRARY_OUTPUT_DIR: path.join(paths.bridge, 'build/macos/lib/x86_64')
    }
  });

  let jsdomTargets = ['jsdom'];
  // if (targetJSEngine === 'quickjs') {
  //   jsdomTargets.push('webf_unit_test');
  // }
  // if (buildMode === 'Debug') {
  //   jsdomTargets.push('webf_test');
  // }

  execSync(`cmake --build ${paths.bridge}/cmake-build-macos-x86_64 --target ${jsdomTargets.join(' ')} -- -j 6`, {
    stdio: 'inherit'
  });

  const binaryPath = path.join(paths.bridge, `build/macos/lib/x86_64/libjsdom.dylib`);

  if (buildMode == 'Release' || buildMode == 'RelWithDebInfo') {
    execSync(`dsymutil ${binaryPath}`, { stdio: 'inherit' });
    execSync(`strip -S -X -x ${binaryPath}`, { stdio: 'inherit' });
  }


}

build();
