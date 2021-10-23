#!/bin/sh

# Clean
rm -rf *.o main

# Compile
clang++ -g -std=c++0x -O0 -Wall -I../include -I/usr/local/include -I../deps/imgui -I../deps/imgui-sfml -I../deps/tinyfiledialogs -I../deps/json-develop/src -c ../src/*.cc 

# If we're using TinyFileDialogs
#clang -g -O0 -Wall -I../include -I/usr/local/include -c ../deps/tinyfiledialogs/tinyfiledialogs.c

# If we're using ImGui
#clang++ -g -std=c++0x -O0 -Wall -I../include -I/usr/local/include -I../deps/imgui -I../deps/imgui-sfml -I../deps/tinyfiledialogs -I../deps/json-develop/src -c ../deps/imgui/*.cpp
#clang++ -g -std=c++0x -O0 -Wall -I../include -I/usr/local/include -I../deps/imgui -I../deps/imgui-sfml -I../deps/tinyfiledialogs -I../deps/json-develop/src -c ../deps/imgui-sfml/imgui-SFML.cpp

# Link
clang++ -g -std=c++0x -O0 -Wall -L/usr/local/lib -lsfml-window -lsfml-graphics -lsfml-system -framework OpenGL *.o -o main

