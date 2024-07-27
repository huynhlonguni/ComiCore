#include "ui.h"
#include "raylib.h"
#include "raymath.h"

#define MAX_ZOOM 30
#define MIN_ZOOM 0.1
#define ZOOM_SCALE 0.1
#include <math.h>

#include "page.h"

Page page;
UI ui(20);

void UpdateFrame() {
	ui.update();

	page.update();

	BeginDrawing();
		ClearBackground(GRAY);
		page.draw();
		ui.draw();
		DrawFPS(10,10);

	EndDrawing();
}

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
	SetTargetFPS(60);
	InitWindow(1280, 720, "raylib-nuklear example");

	page = Page(1000,1410);

	vector<Point> cutLine(3);
	cutLine[0] = {-20.0, 700};
	cutLine[1] = {500.0, 900};
	cutLine[2] = {1020.0, 700};

	page.slice(cutLine);

	while (!WindowShouldClose()) {
		UpdateFrame();
	}


	CloseWindow();
	return 0;
}