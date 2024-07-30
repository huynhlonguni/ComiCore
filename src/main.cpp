#include "raylib.h"

#include "editor.h"

#ifdef __EMSCRIPTEN__
	#include <emscripten/emscripten.h>
#endif

Editor editor;

void UpdateFrame() {
	editor.update();

	if (IsFileDropped()) {
		FilePathList dropList = LoadDroppedFiles();
		for (int i = 0; i < dropList.count; i++) {
			if (IsFileExtension(dropList.paths[i], ".png") || IsFileExtension(dropList.paths[i], ".jpg")) {
				editor.addIllust(dropList.paths[i]);
			}
		}
		UnloadDroppedFiles(dropList);
	}

	BeginDrawing();
		ClearBackground(GRAY);
		editor.draw();
		DrawFPS(10,10);

	EndDrawing();
}

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
	SetTargetFPS(60);
	InitWindow(1280, 720, "ComicGen");
	SetExitKey(0);

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(UpdateFrame, 0, 1);
#else
	while (!WindowShouldClose()) {
		UpdateFrame();
	}
#endif

	CloseWindow();
	return 0;
}