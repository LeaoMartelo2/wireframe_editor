#!/bin/bash

set -xe

gcc src/main.c -Wall -Wextra -pedantic -lm -O2 -std=c17 -L./raylib/linux/ -lraylib -o wireframe_editor

x86_64-w64-mingw32-gcc src/main.c -Wall -Wextra -pedantic -lm -O2 -std=c17 -L ./raylib/windows/ -lraylib -lgdi32 -lwinmm -o wireframe_editor.exe

./wireframe_editor
