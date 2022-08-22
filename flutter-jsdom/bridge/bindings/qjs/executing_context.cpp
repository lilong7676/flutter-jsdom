#include "executing_context.h"
#include <stdlib.h>
#include <iostream>

namespace jsdom::binding::qjs {
ExecutionContext::ExecutionContext(int32_t contextId, void* owner) : contextId(contextId), owner(owner) {
  std::cout<<"ExecutionContext init" << std::endl;
}

bool ExecutionContext::evaluateJavaScript(const char* code, size_t codeLength, const char* sourceURL, int startLine) {
  std::cout<<"ExecutionContext evaluateJs code:" << code << std::endl;
  return true;
}

}  // namespace jsdom::binding::qjs
