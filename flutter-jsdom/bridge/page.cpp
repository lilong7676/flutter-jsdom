/*
 * page.cpp
 * @Author: lilonglong
 * @Date: 2022-08-19 22:47:59
 * @Last Modified by: lilonglong
 * @Last Modified time: 2022-08-24 11:02:03
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

  // 这里测试执行js,一切正常
  testEvaluateScript();
}

JSDomPage::~JSDomPage() {
  std::cout << "JSDomPage::析构" << std::endl;
  delete m_context;
  JSDomPage::pagePool[pageId] = nullptr;
}

void JSDomPage::testEvaluateScript() {
  // test js execution
  if (m_context != nullptr) {
    const char* script = "var a = 1 + 1; a;";
    m_context->evaluateJavaScript(script, strlen(script), nullptr, 0);

  } else {
    std::cout << "JSDomPage::JSDomPage error m_context" << std::endl;
  }
}

void JSDomPage::evaluateScript(const char* script) {
  std::cout << "JSDomPage::evaluateScript: " << script << std::endl;

  // FIXME: 问题：为什么这里执行的时候，应用直接崩溃了，flutter控制台没有任何信息
  testEvaluateScript();
}

}  // namespace jsdom
