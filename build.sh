#!/bin/bash

set -xe

gcc main.c -lraylib -lm -o main

./main
