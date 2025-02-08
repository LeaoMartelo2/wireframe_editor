#!/bin/bash

set -xe

flags="-Wall -Wextra -Wno-missing-field-initializers -Wno-format-overflow -O3 -pedantic -L ./raylib/linux/ -lm -lraylib"


g++ src/main.cpp $flags -o editor
