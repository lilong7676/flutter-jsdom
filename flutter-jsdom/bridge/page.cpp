/*
 * page.cpp
 * @Author: lilonglong
 * @Date: 2022-08-19 22:47:59
 * @Last Modified by: lilonglong
 * @Last Modified time: 2022-08-24 16:45:20
 */
#include "page.h"

#include <iostream>

namespace jsdom {
using namespace binding::qjs;

jsdom::JSDomPage** JSDomPage::pagePool{nullptr};

JSDomPage::JSDomPage(int32_t _pageId) {
  std::cout << "JSDomPage::pageId: " << _pageId << std::endl;
  pageId = _pageId;

  // 初始化执行上下文
  m_context = new ExecutionContext(_pageId);

}

JSDomPage::~JSDomPage() {
  std::cout << "JSDomPage::析构" << std::endl;
  delete m_context;
  JSDomPage::pagePool[pageId] = nullptr;
}

void JSDomPage::evaluateScript(const char* script) {
  std::cout << "JSDomPage::evaluateScript: " << script << std::endl;

  if (m_context != nullptr) {
    m_context->evaluateJavaScript(script, strlen(script), nullptr, 0);
  } else {
    std::cout << "JSDomPage::JSDomPage error m_context" << std::endl;
  }
}

}  // namespace jsdom
