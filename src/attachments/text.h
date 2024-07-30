#pragma once

#include "attachment.h"

#include <string>
using namespace std;

class Text : public Attachment {
private:
	string content = "Lorem Ipsum";
	string fontName = "ComicSans";
	float fontSize = 40.0;
	Color color = BLACK;
public:
	int getType() {
		return Attachment::Text;
	}

	void setFont(string name) {
		fontName = name;
	}

	string getFont() {
		return fontName;
	}

	void setSize(float size) {
		fontSize = size;
	}

	void setContent(string ct) {
		content = ct;
	}

	string getContent() {
		return content;
	}

	void draw(TextEngine *textEngine) {
		if (textEngine) {
			textEngine->drawText(fontName, fontSize, color, bound.x, bound.y + fontSize / 2, content);
			float w = textEngine->getTextWidth(fontName, content);
			bound.w = w;
			bound.h = fontSize;
		}
	}
};