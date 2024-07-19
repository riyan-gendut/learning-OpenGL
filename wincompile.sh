#!/bin/bash
x86_64-w64-mingw32-c++-win32 $1 -I ./include -L ./lib-mingw-w64 -lglfw3 -lopengl32 -lmingw32 -lgdi32 -luser32 -lkernel32 -static-libstdc++ -static-libgcc -o $2
