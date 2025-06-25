#ifndef HAZEL_CMAKE_TEST_H
#define HAZEL_CMAKE_TEST_H

// Windows DLL导出/导入宏定义
#ifdef _WIN32
#ifdef HAZEL_BUILD_DLL
#define HAZEL_API __declspec(dllexport)
#else
#define HAZEL_API __declspec(dllimport)
#endif
#else
#define HAZEL_API
#endif

namespace Hazel {
    HAZEL_API void Print();
}

#endif //HAZEL_CMAKE_TEST_H