/*
 * page
 * @Author: lilonglong
 * @Date: 2022-08-19 22:14:54
 * @Last Modified by: lilonglong
 * @Last Modified time: 2022-08-24 10:43:00
 */

#ifndef JSDOM_PAGE_H_
#define JSDOM_PAGE_H_

#include <cstdint>
#include <stddef.h>
#include <string.h>
#include "bindings/qjs/execution_context.h"

struct NativeString {
  const uint16_t* string;
  uint32_t length;

  NativeString* clone();
  void free();
};

namespace jsdom {
class JSDomPage;

class JSDomPage {
 public:
  static jsdom::JSDomPage** pagePool;
  int32_t pageId;

  JSDomPage(int32_t pageId);
  ~JSDomPage();

  void evaluateScript(const char* script);

  void testEvaluateScript();

 private:
  binding::qjs::ExecutionContext* m_context;
};
}  // namespace jsdom

#endif
