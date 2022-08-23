/*
 * executing_context.h
 * @Author: lilonglong
 * @Date: 2022-08-19 22:03:52
 * @Last Modified by: lilonglong
 * @Last Modified time: 2022-08-23 09:57:45
 */

#ifndef EXECUTING_CONTEXT_H_
#define EXECUTING_CONTEXT_H_

#include <cstdint>
#include <stddef.h>
#include "third_party/quickjs/list.h"
#include "third_party/quickjs/quickjs.h"
#include "third_party/quickjs/quickjs-libc.h"

namespace jsdom::binding::qjs {
class ExecutionContext {
 public:
  ExecutionContext(int32_t contextId, void* owner);
  bool evaluateJavaScript(const char* code, size_t codeLength, const char* sourceURL, int startLine);
  bool handleException(JSValue* exception);

 private:
  int32_t contextId;
  void* owner;

  JSContext* m_context = nullptr;

};
}  // namespace jsdom::bindings::qjs

#endif
