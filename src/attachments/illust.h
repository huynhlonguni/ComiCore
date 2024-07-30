#pragma once

#include "raylib.h"
#include "attachment.h"

#include <vector>
using namespace std;

class Illust : public Attachment {
private:
	Texture2D texture;
public:
	int getType() {
		return Attachment::Illust;
	}

	Illust(Image image) {
		texture = LoadTextureFromImage(image);
		bound.x = 0;
		bound.y = 0;
		bound.w = texture.width;
		bound.h = texture.height;
	}

	void setW(int w) {
		bound.w = w;
	}

	void setH(int h) {
		bound.h = h;
	}

	int getW() {
		return bound.w;
	}

	int getH() {
		return bound.h;
	}

	float getAspectRatio() {
		return texture.width / (float)texture.height;
	}

	void draw(TextEngine *textEngine) {
	    Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
	    Rectangle dest = { (float)bound.x, (float)bound.y, (float)bound.w, (float)bound.h };
	    Vector2 origin = { 0, 0 };
	    DrawTexturePro(texture, source, dest, origin, 0, WHITE);
	}

	~Illust() {
		UnloadTexture(texture);
	}
};