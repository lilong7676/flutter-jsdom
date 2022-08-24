#include "execution_context.h"
#include <stdlib.h>
#include <iostream>

namespace jsdom::binding::qjs {

static JSRuntime* m_runtime{nullptr};

ExecutionContext::ExecutionContext(int32_t contextId) : contextId(contextId) {
  std::cout << "ExecutionContext::init" << std::endl;
  // 构造一个 JS 运行时
  if (m_runtime == nullptr) {
    m_runtime = JS_NewRuntime();
    std::cout << "JS_NewRuntime init" << std::endl;
  }
  // 根据运行时构建一个上下文环境
  m_context = JS_NewContext(m_runtime);
  std::cout << "JS_NewContext init" << std::endl;
}

bool ExecutionContext::evaluateJavaScript(const char* code, size_t codeLength, const char* sourceURL, int startLine) {
  std::cout << "ExecutionContext::evaluateJs code:" << code << std::endl;
  if (m_context == nullptr) {
    return false;
  }

  // 调用 C 的 std 方法帮助在控制台输出调试信息
  // js_std_add_helpers(m_context, 0, NULL);

  JSValue result;
  try {
    result = JS_Eval(m_context, code, codeLength, "main", 0);
  } catch (const std::exception& e) {
    std::cerr << "ExecutionContext::evaluateJs error:" << e.what() << '\n';
  }

  bool success = handleException(&result);

  std::cout << "ExecutionContext::evaluateJs success: " << success << std::endl;

  JS_FreeValue(m_context, result);

  return success;
}

bool ExecutionContext::handleException(JSValue* exception) {
  if (JS_IsException(*exception)) {
    std::cout << "JS has error" << std::endl;

    JSValue error = JS_GetException(m_context);
    JS_FreeValue(m_context, error);
    return false;
  }

  return true;
}

}  // namespace jsdom::binding::qjs
