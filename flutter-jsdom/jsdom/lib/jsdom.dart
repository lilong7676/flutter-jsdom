import 'dart:ffi';
import 'dart:io' show Platform;

import 'package:ffi/ffi.dart';
import 'package:path/path.dart';
import 'jsdom_platform_interface.dart';

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
    DynamicLibrary dylib = DynamicLibrary.open(join('', 'libjsdom.dylib'));
    var initJsDomPage =
        dylib.lookupFunction<NativeInitJSDomPagePool, DartInitJsDomPagePool>(
            'initJSDomPagePool');

    initJsDomPage(1024);

    var evaluateScripts =
        dylib.lookupFunction<NativeEvaluateScripts, DartEvaluateScripts>(
            'evaluateScript');
    var nativeCode = code.toNativeUtf8();

    evaluateScripts(0, nativeCode);
  }
}
