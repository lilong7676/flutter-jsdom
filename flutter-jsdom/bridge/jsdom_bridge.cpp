/*
 * bridge.cc
 * @Author: lilonglong
 * @Date: 2022-08-19 22:05:26
 * @Last Modified by: lilonglong
 * @Last Modified time: 2022-08-23 14:34:52
 */

#include "include/jsdom_bridge.h"
#include "page.h"

int maxPagePoolSize = 0;
bool inited = false;

void initJSDomPagePool(int pageSize) {
  // 初始化 pagePool 数组
  jsdom::JSDomPage::pagePool = new jsdom::JSDomPage*[pageSize];
  for (int i = 1; i < pageSize; i++) {
    jsdom::JSDomPage::pagePool[i] = nullptr;
  }

  // 初始化 JSDomPage
  int32_t pageId = 0;
  jsdom::JSDomPage::pagePool[0] = new jsdom::JSDomPage(pageId);

  // 设置最大 pagePoll
  maxPagePoolSize = pageSize;
  // 标记已初始化完成
  inited = true;
}

// 根据 pageId 获取 jsdomPage 实例
void* getPage(int32_t pageId) {
  if (!inited || pageId < maxPagePoolSize) {
    return nullptr;
  }
  return jsdom::JSDomPage::pagePool[pageId];
}

/**
 * @brief 执行 js 脚本
 *
 * @param contextId 要在哪个 pageContext 执行
 * @param script 要执行的脚本
 */
void evaluateScript(int32_t contextId, const char* script) {
  auto page = static_cast<jsdom::JSDomPage*>(getPage(contextId));
  page->evaluateScript(script);
}
