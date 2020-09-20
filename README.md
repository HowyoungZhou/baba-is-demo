# baba-is-demo

## Overview

The project is a demo of Baba Is You built with Godot engine. Baba Is You is an awesome puzzle game, which allows players to move the words to create or alter the rules of the game. Check it out at [Steam](https://store.steampowered.com/app/736260/Baba_Is_You/).

## Build

To build the game, make sure the following prerequisites are installed:

- git
- [CMake](https://cmake.org/download/)
- [JRE](https://www.java.com/en/download/)
- [ANTLR jar](https://www.antlr.org/download/antlr-4.8-complete.jar)

First, clone this repository with:

```bash
git clone https://github.com/HowyoungZhou/baba-is-you.git
```

Then, fetch git modules with:

```bash
git submodule update --init --recursive
```

Finally, build the project with:

```bash
cmake -S . -B build -DANTLR_EXECUTABLE=$ANTLR_EXECUTABLE -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Replace the `$ANTLR_EXECUTABLE` with the path to your ANTLR jar file. It will build the godot-cpp and ANTLR runtime library automatically, which will take a while. Please wait with patience.

After building, launch Godot, import the project, and hit the Run button at the top-right corner of the window.