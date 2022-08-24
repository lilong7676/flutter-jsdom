import 'dart:ffi';
import 'package:ffi/ffi.dart';

import 'jsdom_platform_interface.dart';

import 'src/dynamic_library.dart';

typedef NativeInitJSDomPagePool = Void Function(Int32 poolSize);
typedef DartInitJsDomPagePool = void Function(int poolSize);

typedef NativeEvaluateScripts = Void Function(
    Int32 contextId, Pointer<Utf8> code);
typedef DartEvaluateScripts = void Function(int contextId, Pointer<Utf8> code);

class Jsdom {
  Future<String?> getPlatformVersion() {
    return JsdomPlatform.instance.getPlatformVersion();
  }

  void executeJavascript(String code) {
    DartInitJsDomPagePool initJsDomPage = JsDomDynamicLibrary.ref
        .lookup<NativeFunction<NativeInitJSDomPagePool>>('initJSDomPagePool')
        .asFunction();

    initJsDomPage(1024);

    DartEvaluateScripts evaluateScripts = JsDomDynamicLibrary.ref
        .lookup<NativeFunction<NativeEvaluateScripts>>('evaluateScript')
        .asFunction();
    Pointer<Utf8> nativeCode = code.toNativeUtf8();

    evaluateScripts(0, nativeCode);
  }
}
