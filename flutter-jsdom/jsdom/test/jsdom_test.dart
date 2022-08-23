import 'package:flutter_test/flutter_test.dart';
import 'package:jsdom/jsdom.dart';
import 'package:jsdom/jsdom_platform_interface.dart';
import 'package:jsdom/jsdom_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockJsdomPlatform 
    with MockPlatformInterfaceMixin
    implements JsdomPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final JsdomPlatform initialPlatform = JsdomPlatform.instance;

  test('$MethodChannelJsdom is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelJsdom>());
  });

  test('getPlatformVersion', () async {
    Jsdom jsdomPlugin = Jsdom();
    MockJsdomPlatform fakePlatform = MockJsdomPlatform();
    JsdomPlatform.instance = fakePlatform;
  
    expect(await jsdomPlugin.getPlatformVersion(), '42');
  });
}
