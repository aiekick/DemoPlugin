#pragma once

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32) || defined(__WIN64__) || defined(WIN64) || defined(_WIN64) || defined(_MSC_VER)
#if defined(Common_EXPORTS)
#define COMMON_API __declspec(dllexport)
#elif defined(BUILD_SHARED_LIBS)
#define COMMON_API __declspec(dllimport)
#else
#define COMMON_API
#endif
#elif defined(__linux__) || defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__EMSCRIPTEN__) || defined(__APPLE__)
#define COMMON_API
#endif
