import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'jsdom_platform_interface.dart';

/// An implementation of [JsdomPlatform] that uses method channels.
class MethodChannelJsdom extends JsdomPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('jsdom');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }
}
