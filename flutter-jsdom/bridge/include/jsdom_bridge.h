/*
 * jsdom_bridge
 * @Author: lilonglong
 * @Date: 2022-08-19 22:10:01
 * @Last Modified by: lilonglong
 * @Last Modified time: 2022-08-23 14:32:10
 */
#ifndef JSDOM_BRIDGE_H_
#define JSDOM_BRIDGE_H_

#include <cstdint>
#include <thread>

/**
 * @brief FFI 库只能与 C 符号绑定，因此在 C++ 中，这些符号添加 extern C 标记。
 * 还应该添加属性来表明符号是需要被 Dart 引用的，以防止链接器在优化链接时会丢弃符号。
 * https://flutter.cn/docs/development/platform-integration/ios/c-interop
 */
#define JSDOM_EXPORT_C extern "C" __attribute__((visibility("default"))) __attribute__((used))
#define JSDOM_EXPORT __attribute__((__visibility__("default")))

JSDOM_EXPORT_C
void initJSDomPagePool(int pagesize);

JSDOM_EXPORT_C
void* getPage(int32_t contextId);

JSDOM_EXPORT_C
void evaluateScript(int32_t contextId, const char* script);

#endif
