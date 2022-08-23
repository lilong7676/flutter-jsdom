/*
 * page.cpp
 * @Author: lilonglong
 * @Date: 2022-08-19 22:47:59
 * @Last Modified by: lilonglong
 * @Last Modified time: 2022-08-23 14:27:31
 */
#include "page.h"

namespace jsdom {
using namespace binding::qjs;

jsdom::JSDomPage** JSDomPage::pagePool{nullptr};


JSDomPage::JSDomPage(int32_t pageId) {
  m_context = new ExecutionContext(pageId, nullptr);
}

void JSDomPage::evaluateScript(const char* script) {
  m_context->evaluateJavaScript(script, strlen(script), nullptr, 0);
}

}  // namespace jsdom
