#define RAYLIB_NUKLEAR_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_ASSERT(...) (void)0
#define NK_BUTTON_TRIGGER_ON_RELEASE
#include "raylib-nuklear.h"

class UI {
private:
	nk_context *ctx;
public:
	UI(int fontSize) {
		ctx = InitNuklear(fontSize);
	}

	nk_context* getCtx() {
		return ctx;
	}

	void update(int &activeTool) {
		UpdateNuklear(ctx);

		if (nk_begin(ctx, "Nuklear", nk_rect(0, 0, 300, 720), 0)) {
			nk_layout_row_dynamic(ctx, 50, 0);
			nk_layout_row_dynamic(ctx, 50, 3);
			if (nk_button_label(ctx, "None")) {
				activeTool = -1;
			}
			if (nk_button_label(ctx, "Slice")) {
				activeTool = 0;
			}
			if (nk_button_label(ctx, "Panel")) {
				activeTool = 1;
			}
			if (nk_button_label(ctx, "Transform")) {
				activeTool = 2;
			}
			if (nk_button_label(ctx, "Bubble")) {
				activeTool = 3;
			}
			if (nk_button_label(ctx, "Text")) {
				activeTool = 4;
			}
		}
		nk_end(ctx);
	}

	void draw() {
		DrawNuklear(ctx);
	}

	~UI() {
		UnloadNuklear(ctx);
	}
};