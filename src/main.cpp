#include "raylib.h"

#include "editor.h"

#ifdef __EMSCRIPTEN__
	#include <emscripten/emscripten.h>
#endif

Editor editor;

#ifdef __EMSCRIPTEN__
extern "C" { //name mangling
	EMSCRIPTEN_KEEPALIVE void EditorAddPage() {
		editor.addPage();
	}

	EMSCRIPTEN_KEEPALIVE void EditorSetActivePage(int id) {
		editor.setActivePage(id);
	}

	EMSCRIPTEN_KEEPALIVE void EditorSetActiveTool(int id) {
		editor.setActiveTool(id);
	}

	EMSCRIPTEN_KEEPALIVE int EditorGetAttachmentCount() {
		return editor.getAttachmentCount();
	}

	EMSCRIPTEN_KEEPALIVE int EditorGetPanelCount() {
		return editor.getPanelCount();
	}

	EMSCRIPTEN_KEEPALIVE int EditorGetAttachmentPanel(int id) {
		return editor.getAttachmentPanel(id);
	}

	EMSCRIPTEN_KEEPALIVE int EditorGetAttachmentType(int id) {
		return editor.getAttachmentType(id);
	}

	EMSCRIPTEN_KEEPALIVE void EditorSetAttachmentPanel(int id, int panel) {
		return editor.setAttachmentPanel(id, panel);
	}
}

EM_JS(void, sendStateChangeEvent, (), {
	window.dispatchEvent(
		new CustomEvent("EditorStateChangeEvent")
	);
});
#else
void sendStateChangeEvent() {}
#endif

int prevAttachmentCount = 0;

void UpdateFrame() {
	editor.update();

	int currAttachmentCount = editor.getAttachmentCount();
	if (currAttachmentCount != prevAttachmentCount) {
		sendStateChangeEvent();
	}

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
#ifndef __EMSCRIPTEN__
		DrawFPS(10,10);
#endif

	EndDrawing();
}

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
	SetTargetFPS(60);
	InitWindow(1280, 720, "ComicGen");
	SetExitKey(0);

	editor.init();

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