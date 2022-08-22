/*
 * page
 * @Author: lilonglong
 * @Date: 2022-08-19 22:14:54
 * @Last Modified by: lilonglong
 * @Last Modified time: 2022-08-22 14:48:35
 */

#ifndef JSDOM_PAGE_H_
#define JSDOM_PAGE_H_

#include <cstdint>
#include <stddef.h>
#include <string.h>
#include "bindings/qjs/executing_context.h"

struct NativeString {
  const uint16_t* string;
  uint32_t length;

  NativeString* clone();
  void free();
};

namespace jsdom {
class JSDomPage {
 public:
  JSDomPage(int32_t jsContext);

  void evaluateScript(int32_t contextId, const char* script);

 private:
  binding::qjs::ExecutionContext* m_context;
};
}  // namespace jsdom

#endif
