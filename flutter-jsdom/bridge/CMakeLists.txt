cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.11)
project(JSDom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")

list(APPEND JSDom_PUBLIC_HEADERS
      ${CMAKE_CURRENT_SOURCE_DIR}/include/bridge.h
)

list(APPEND BRIDGE_SOURCE
        bridge.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/bridge.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/dart_methods.h
        dart_methods.cpp
)

list(APPEND BRIDGE_SOURCE
    page.cpp
    page.h
    bindings/qjs/executing_context.cpp
    bindings/qjs/executing_context.h
)

list(APPEND PUBLIC_HEADER
  include/bridge.h
)

add_library(jsdom SHARED ${BRIDGE_SOURCE})
add_library(jsdom_static STATIC ${BRIDGE_SOURCE})

### jsdom
target_include_directories(jsdom PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ./include)

### jsdom Static
target_include_directories(jsdom_static PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR} PUBLIC ./include)

if (${ENABLE_TEST})
  add_compile_definitions(IS_TEST=true)
endif ()

if (DEFINED ENV{LIBRARY_OUTPUT_DIR})
  set_target_properties(jsdom
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "$ENV{LIBRARY_OUTPUT_DIR}"
  )
  set_target_properties(jsdom_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "$ENV{LIBRARY_OUTPUT_DIR}")
endif ()
