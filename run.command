#!/bin/sh
cd "$(dirname "$0")" || exit 1
c++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude src/*.cpp -o bookstore || exit 1
./bookstore
