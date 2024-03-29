# Radar

Simulation definition stored into assets/game.rdr

![](medias/demo.png)

### Windows

**Needs:**

- Git
- CMake (>= 3.19)
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

### Mac OS

**Needs:**

- Brew
- CMake (>= 3.19)

**Build**

```
brew install csfml
cmake -DCMAKE_BUILD_TYPE=Release -B dist -S .
cmake --build dist
```

**Launch**

```
cd dist/bin
./radar
```

### Linux

**Needs:**

- Build essentials
- CSFML package (sudo apt install libcsfml-dev / sudo dnf install CSFML)

**Build**

```
cmake -DCMAKE_BUILD_TYPE=Release -B dist -S .
cmake --build dist
```

**Launch**

```
cd dist/bin
./radar
```
