cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.11)
project(JSDom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")

# 获取 dart_sdk 位置
execute_process(
  COMMAND bash "-c" "read dart_sdk < <(type -p dart) && echo $\{dart_sdk%/*\}/cache/dart-sdk/include | xargs"
  OUTPUT_VARIABLE DART_SDK
)
string(REGEX REPLACE "\n$" "" DART_SDK "${DART_SDK}")
message(STATUS "dart_sdk ${DART_SDK}")

list(APPEND JSDom_PUBLIC_HEADERS
      ${CMAKE_CURRENT_SOURCE_DIR}/include/jsdom_bridge.h
)

set(QUICKJS_PUBLIC_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/cutils.h
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/libregexp.h
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/libregexp-opcode.h
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/libunicode.h
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/libunicode-table.h
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/list.h
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/quickjs.h
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/quickjs-atom.h
  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/quickjs-opcode.h
)

# BINDING_DIR
set(BINDING_DIR ${CMAKE_CURRENT_LIST_DIR}/bindings)

# quickjs start ----------
add_compile_options(-DJSDOM_QUICK_JS_ENGINE=1)

execute_process(
  COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/VERSION
  OUTPUT_VARIABLE QUICKJS_VERSION
)

list(APPEND QUICK_JS_SOURCE
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/libbf.c
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/libbf.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/cutils.c
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/cutils.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/libregexp.c
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/libregexp.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/libregexp-opcode.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/libunicode.c
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/libunicode.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/libunicode-table.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/list.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/quickjs.c
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/quickjs.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/quickjs-atom.h
${CMAKE_CURRENT_SOURCE_DIR}/third_party/quickjs/quickjs-opcode.h
)
 ## 构造 quickjs lib
if(${STATIC_QUICKJS})
  add_library(quickjs STATIC ${QUICK_JS_SOURCE})
else()
  add_library(quickjs SHARED ${QUICK_JS_SOURCE})
endif ()

 ## Quickjs use __builtin_frame_address() to get stack pointer, we should add follow options to get it work with -O2
 ## https://stackoverflow.com/questions/14735010/how-do-you-get-gccs-builtin-frame-address-to-work-with-o2
add_compile_options(-fno-optimize-sibling-calls -fno-omit-frame-pointer)
target_compile_options(quickjs PUBLIC -DCONFIG_VERSION=${\"QUICKJS_VERSION\"})
# quickjs end ----------

# BRIDGE_INCLUDE
list(APPEND BRIDGE_INCLUDE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${DART_SDK}
  ${ADDITIONAL_INCLUDE_DIRS}
)
list(APPEND BRIDGE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

# BRIDGE_LINK_LIBS
list(APPEND BRIDGE_LINK_LIBS quickjs)


# BRIDGE_SOURCE
list(APPEND BRIDGE_SOURCE
        jsdom_bridge.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/jsdom_bridge.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/dart_methods.h
        dart_methods.cpp
)
list(APPEND BRIDGE_SOURCE
    page.cpp
    page.h
    ${CMAKE_CURRENT_SOURCE_DIR}/bindings/qjs/execution_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bindings/qjs/execution_context.h
)

# PUBLIC_HEADER
list(APPEND PUBLIC_HEADER
  include/jsdom_bridge.h
)

# jsdom lib
add_library(jsdom SHARED ${BRIDGE_SOURCE})
add_library(jsdom_static STATIC ${BRIDGE_SOURCE})

target_compile_definitions(jsdom PUBLIC -DFLUTTER_BACKEND=1)

### jsdom
target_include_directories(jsdom PRIVATE
  ${BRIDGE_INCLUDE}
  ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ./include)
# jsdom 链接 BRIDGE_LINK_LIBS
target_link_libraries(jsdom PRIVATE ${BRIDGE_LINK_LIBS})

if (${CMAKE_BUILD_TYPE} STREQUAL "Release" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
  target_compile_options(jsdom PRIVATE -fno-exceptions -fvisibility=hidden -fno-rtti)
else ()
  ### remove dynamic_cast and exceptions
  target_compile_options(jsdom PRIVATE -fno-exceptions -fno-rtti)
endif ()

### jsdom Static
target_include_directories(jsdom_static PRIVATE
  ${BRIDGE_INCLUDE}
  ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ./include)
# jsdom_static 链接 BRIDGE_LINK_LIBS
target_link_libraries(jsdom_static ${BRIDGE_LINK_LIBS})


if (${ENABLE_TEST})
  add_compile_definitions(IS_TEST=true)
endif ()

# 设置 target lib 的生成路径
if (DEFINED ENV{LIBRARY_OUTPUT_DIR})
  set_target_properties(jsdom
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "$ENV{LIBRARY_OUTPUT_DIR}"
  )
  set_target_properties(jsdom_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "$ENV{LIBRARY_OUTPUT_DIR}")
  set_target_properties(quickjs PROPERTIES LIBRARY_OUTPUT_DIRECTORY "$ENV{LIBRARY_OUTPUT_DIR}")
endif ()
