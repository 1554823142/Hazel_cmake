cmake_minimum_required(VERSION 3.28)
project(Sandbox)
set(CMAKE_CXX_STANDARD 17)

# 设置库和头文件路径
set(MYLIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(MYLIB_LIBRARY ${CMAKE_SOURCE_DIR}/Sandbox/lib/Release/dllgen.lib)
set(MYLIB_DLL ${CMAKE_SOURCE_DIR}/Sandbox/lib/Release/dllgen.dll)


# 添加可执行程序
add_executable(Sandbox 
    ./src/SandboxApp.cpp
)

# MSVC: 强制使用 UTF-8 编码
target_compile_options(Sandbox PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# Windows平台特定设置
if(WIN32)
    target_compile_definitions(Sandbox PUBLIC HZ_PLATFORM_WINDOWS)
	message("current platform: Windows ")
elseif(UNIX)
    target_compile_definitions(Sandbox PUBLIC HZ_PLATFORM_LINUX)
	message("current platform: Linux ")
endif()

# 添加头文件搜索路径
target_include_directories(Sandbox PRIVATE ${MYLIB_INCLUDE_DIR})

# 链接库文件
target_link_libraries(Sandbox PRIVATE Hazel)

# 将 DLL 拷贝到可执行文件目录（用于运行时）
add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:Hazel>
    $<TARGET_FILE_DIR:Sandbox>)
