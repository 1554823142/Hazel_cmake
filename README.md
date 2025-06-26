# Hazel

这是[Game Engine - YouTube](https://www.youtube.com/playlist?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT)的cmake版本, 不知道能不能坚持下去, 反正用CMake确实很难受, 不像VS那么轮椅



## 编译指令

- 编译:

```powershell
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

可执行文件的位置位于`/build/Sandbox`下