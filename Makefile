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
ADDITIONAL_CPP = src/text_engine.cpp
WASM_FLAGS = -std=c++17 -s -Wall -Wno-missing-braces -Wno-multichar \
			-s USE_GLFW=3 -sALLOW_MEMORY_GROWTH -s TOTAL_MEMORY=67108864 \
			-s EXPORTED_RUNTIME_METHODS=ccall,cwrap \
			-D PLATFORM_WEB -s ENVIRONMENT=web -s MODULARIZE=1 -s EXPORT_ES6=1 -s USE_ES6_IMPORT_META=1
WASM_DATA = --embed-file fonts/ComicSansMS3.ttf
WASM_MAIN = src/main.cpp
WASM_OUT = web/src/editor.mjs

raylib_desktop:
	$(MAKE) -C $(RAYLIB_DIR) -B

raylib_wasm:
	$(MAKE) -C $(RAYLIB_DIR) PLATFORM=PLATFORM_WEB -B

main:
	$(CXX) $(DESKTOP_MAIN) $(ADDITIONAL_CPP) $(DEPENDENCY) -I$(RAYLIB_DIR) -L$(RAYLIB_DIR) -lraylib -I$(INCLUDE_DIR) $(DESKTOP_FLAGS)
	a.exe
wasm:
	emcc -O3 -g0 $(WASM_MAIN) $(ADDITIONAL_CPP) $(DEPENDENCY) -I$(RAYLIB_DIR) -L$(RAYLIB_DIR) -lraylibwasm -I$(INCLUDE_DIR) $(WASM_FLAGS) -o $(WASM_OUT) $(WASM_DATA)
	cat prewasm.js $(WASM_OUT) > wasm.tmp
	mv wasm.tmp $(WASM_OUT)