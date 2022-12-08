# Radar

### Windows

**Needs:**
- Git
- CMake
- MSVC Build tools
 
> Command must be callables in relative path (eg. cmake, git, ...)

**Build**

```
cmake -DCMAKE_BUILD_TYPE=Release -B dist -S .
cmake --build dist
```

**Launch**

```
cd dist\bin
radar.exe
```