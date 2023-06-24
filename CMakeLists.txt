cmake_minimum_required(VERSION 3.25)

set(PROJECT DemoPluginApp)

enable_language(C CXX)
project(${PROJECT} CXX)
set(CMAKE_CXX_STANDARD 11)

set(FINAL_BIN_DIR ${CMAKE_BINARY_DIR}/../bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmakeTargets")

if (WIN32)
    add_definitions(-DWIN32)
else()
    add_definitions(-DUNIX)
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/common)
add_subdirectory(${CMAKE_SOURCE_DIR}/plugin)
add_subdirectory(${CMAKE_SOURCE_DIR}/app)
