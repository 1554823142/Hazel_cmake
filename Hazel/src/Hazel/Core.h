#pragma once

// DLL 导出/导入宏
 #ifdef HZ_PLATFORM_WINDOWS
    #ifdef HAZEL_BUILD_DLL
        #define HAZEL_API __declspec(dllexport)
    #else
        #define HAZEL_API __declspec(dllimport)
    #endif
#else
    #define HAZEL_API
#endif

#define BIT(x) (1 << x)