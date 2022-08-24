/*
 * load native library
 * @Author: lilonglong
 * @Date: 2022-08-24 22:28:21
 * @Last Modified by: lilonglong
 * @Last Modified time: 2022-08-24 14:42:18
 */
import 'dart:ffi';
import 'dart:io' show Platform;
import 'package:path/path.dart';

abstract class JsDomDynamicLibrary {
  static final String _defaultLibraryPath = Platform.isLinux ? '\$ORIGIN' : '';

  /// The search path that dynamic library be load, if null using default.
  static String dynamicLibraryPath = _defaultLibraryPath;

  // The jsdom library name.
  static String libName = 'libjsdom';

  static String get _nativeDynamicLibraryName {
    if (Platform.isMacOS) {
      return '$libName.dylib';
    } else if (Platform.isIOS) {
      return 'jsdom_bridge.framework/jsdom_bridge';
    } else if (Platform.isWindows) {
      return '$libName.dll';
    } else if (Platform.isAndroid || Platform.isLinux) {
      return '$libName.so';
    } else {
      throw UnimplementedError('Not supported platform.');
    }
  }

  static DynamicLibrary? _ref;

  static DynamicLibrary get ref {
    _ref ??= DynamicLibrary.open(
        join(dynamicLibraryPath, _nativeDynamicLibraryName));
    return _ref!;
    //   DynamicLibrary? nativeDynamicLibrary = _ref;
    //   _ref = nativeDynamicLibrary ??= DynamicLibrary.open(
    //       join(_dynamicLibraryPath, _nativeDynamicLibraryName));
    //   return nativeDynamicLibrary;
  }
}
