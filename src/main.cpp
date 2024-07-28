#include "raylib.h"

#include "editor.h"

#if defined(PLATFORM_WEB)
	#include <emscripten/emscripten.h>
#endif

Editor editor;

void UpdateFrame() {
	editor.update();

	BeginDrawing();
		ClearBackground(GRAY);
		editor.draw();
		DrawFPS(10,10);

	EndDrawing();
}

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
	SetTargetFPS(60);
	InitWindow(1280, 720, "raylib-nuklear example");
	SetExitKey(0);

#if defined(PLATFORM_WEB)
	emscripten_set_main_loop(UpdateFrame, 0, 1);
#else
	while (!WindowShouldClose()) {
		UpdateFrame();
	}
#endif

	CloseWindow();
	return 0;
}