#pragma once

#include "fontstash.h"
#include "raylib-fontstash.h"

#include <string>
using namespace std;

class TextEngine {
private:
	FONScontext *fs = NULL;

public:
	TextEngine() {}

	void init() {
		fs = rlfonsCreate(1024, 1024, FONS_ZERO_TOPLEFT);
	}

	void loadFont(string name, string path) {
		fonsAddFont(fs, name.c_str(), path.c_str());
	}

	void drawText(string fontName, float fontSize, Color color, float x, float y, string str) {
		int font = fonsGetFontByName(fs, fontName.c_str());
		unsigned int colori = rlfonsColor(color);
		fonsSetFont(fs, font);
		fonsSetSize(fs, fontSize);
		fonsSetColor(fs, colori);
		fonsSetAlign(fs, FONS_ALIGN_LEFT | FONS_ALIGN_MIDDLE);
		fonsDrawText(fs, x, y, str.c_str(), NULL);
	}

	float getTextWidth(string fontName, string str) {
		float bound[4];
		float w = fonsTextBounds(fs, 0, 0, str.c_str(), NULL, bound);
		return w;
	}

	~TextEngine() {
		if (fs) rlfonsDelete(fs);
		fs = NULL;
	}
};