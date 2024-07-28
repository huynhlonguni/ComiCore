CXX ?= g++

.PHONY: main wasm

all: main

RAYLIB_DIR = raylib
SRC_DIR = src
INCLUDE_DIR = include

CLIPPER_SOURCE = $(wildcard clipper2/*.cpp)

DEPENDENCY = $(CLIPPER_SOURCE)

DESKTOP_FLAGS = -Wno-multichar -lopengl32 -lgdi32 -lwinmm
DESKTOP_NO_CONSOLE = -mwindows
DESKTOP_MAIN = src/main.cpp
WASM_FLAGS = -std=c++17 -s -Wall -Wno-missing-braces -Wno-multichar -s USE_GLFW=3 -sALLOW_MEMORY_GROWTH -s TOTAL_MEMORY=67108864 -s EXPORTED_RUNTIME_METHODS=ccall -D PLATFORM_WEB
WASM_SHELL = --shell-file raylib/shell.html
WASM_DATA = 
WASM_MAIN = src/main.cpp

raylib_desktop:
	$(MAKE) -C $(RAYLIB_DIR) -B

raylib_wasm:
	$(MAKE) -C $(RAYLIB_DIR) PLATFORM=PLATFORM_WEB -B

main:
	$(CXX) $(DESKTOP_MAIN) $(DEPENDENCY) -I$(RAYLIB_DIR) -L$(RAYLIB_DIR) -lraylib -I$(INCLUDE_DIR) $(DESKTOP_FLAGS)
	a.exe
wasm:
	emcc -O3 -g0 $(WASM_MAIN) $(DEPENDENCY) -I$(RAYLIB_DIR) -L$(RAYLIB_DIR) -lraylibwasm -I$(INCLUDE_DIR) -o main.html $(WASM_FLAGS) $(WASM_SHELL)