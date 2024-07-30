#pragma once

#include "raylib.h"
#include "bound.h"

#include <vector>
using namespace std;

class Illust {
private:
	Texture2D texture;
	int x = 0;
	int y = 0;
	float scale = 1.0;
	int parentPanel = -1;
public:
	Illust(Image image) {
		texture = LoadTextureFromImage(image);
	}

	Bound getBound() {
		return {x, y, (int)(texture.width * scale), (int)(texture.height * scale)};
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	void setX(int v) {
		x = v;
	}

	void setY(int v) {
		y = v;
	}

	int getW() {
		return texture.width;
	}

	int getH() {
		return texture.height;
	}

	float getScale() {
		return scale;
	}

	void setScale(float v) {
		scale = v;
	}

	void setParentPanel(int id) {
		parentPanel = id;
	}

	int getParentPanel() {
		return parentPanel;
	}

	void draw() {
		DrawTextureEx(texture, {(float)x, (float)y}, 0.0, scale, WHITE);
	}

	~Illust() {
		UnloadTexture(texture);
	}
};