import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'jsdom_method_channel.dart';

abstract class JsdomPlatform extends PlatformInterface {
  /// Constructs a JsdomPlatform.
  JsdomPlatform() : super(token: _token);

  static final Object _token = Object();

  static JsdomPlatform _instance = MethodChannelJsdom();

  /// The default instance of [JsdomPlatform] to use.
  ///
  /// Defaults to [MethodChannelJsdom].
  static JsdomPlatform get instance => _instance;
  
  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [JsdomPlatform] when
  /// they register themselves.
  static set instance(JsdomPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
