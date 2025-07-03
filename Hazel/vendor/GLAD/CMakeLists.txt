cmake_minimum_required(VERSION 3.15)
project(glad C)

add_library(glad STATIC
    include/glad/glad.h
    include/KHR/khrplatform.h
    src/glad.c
)

target_include_directories(glad PUBLIC include)

# # Windows 平台相关设置
# if (WIN32)
#     set_target_properties(glad PROPERTIES
#         MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
#     )
#     # 兼容旧 CMake/MSVC
#     if (MSVC)
#         # Release 配置下使用 /MT
#         target_compile_options(glad PRIVATE
#             $<$<AND:$<CONFIG:Release>,$<CXX_COMPILER_ID:MSVC>>:/MT>
#         )
#     endif()
# endif()