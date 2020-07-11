# baba-is-you

## Build

To build the game, make sure the following prerequisites are installed:

- git
- [cmake](https://cmake.org/download/)
- [JRE](https://www.java.com/en/download/)
- [ANTLR jar](https://www.antlr.org/download/antlr-4.8-complete.jar)

First, clone this repository with:

```bash
git clone https://github.com/HowyoungZhou/baba-is-you.git
```

Then, fetch git modules with:

```bash
git submodule init
git submodule update
```

Finally, build the project with:

```bash
cmake -S . -B build -DANTLR_EXECUTABLE=$ANTLR_EXECUTABLE -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Replace the `$ANTLR_EXECUTABLE` with the path to your ANTLR jar file. It will build the godot-cpp and ANTLR runtime library automatically, which will take a while. Please wait with patience.

