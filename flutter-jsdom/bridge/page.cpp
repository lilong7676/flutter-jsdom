/*
 * page.cpp
 * @Author: lilonglong
 * @Date: 2022-08-19 22:47:59
 * @Last Modified by: lilonglong
 * @Last Modified time: 2022-08-22 14:48:17
 */
#include "page.h"

namespace jsdom {
using namespace binding::qjs;

JSDomPage::JSDomPage(int32_t jsContext) {
  m_context = new ExecutionContext(jsContext, nullptr);
}

void JSDomPage::evaluateScript(int32_t contextId, const char* script) {
  m_context->evaluateJavaScript(script, strlen(script), nullptr, 0);
}

}  // namespace jsdom
