/*
 * executing_context.h
 * @Author: lilonglong
 * @Date: 2022-08-19 22:03:52
 * @Last Modified by: lilonglong
 * @Last Modified time: 2022-08-22 14:45:22
 */

#ifndef EXECUTING_CONTEXT_H_
#define EXECUTING_CONTEXT_H_

#include <cstdint>
#include <stddef.h>

namespace jsdom::binding::qjs {
class ExecutionContext {
 public:
  ExecutionContext(int32_t contextId, void* owner);
  bool evaluateJavaScript(const char* code, size_t codeLength, const char* sourceURL, int startLine);

 private:
  int32_t contextId;
  void* owner;

};
}  // namespace jsdom::bindings::qjs

#endif
