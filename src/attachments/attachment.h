#pragma once

#include "../bound.h"
#include "../text_engine.h"

class Attachment {
protected:
	Bound bound;
	int parentPanel = 0;
public:
	enum {
		Illust, Bubble, Text
	};
	
	virtual int getType() = 0;

	virtual Bound getBound() {
		return bound;
	}

	virtual void setBound(Bound b) {
		bound = b;
	}

	virtual void setParentPanel(int id) {
		parentPanel = id;
	}

	virtual int getParentPanel() {
		return parentPanel;
	}

	virtual void setX(int x) { bound.x = x; }
	virtual void setY(int y) { bound.y = y; }
	virtual void setW(int w) { bound.w = w; }
	virtual void setH(int h) { bound.h = h; }

	virtual int getX() { return bound.x; }
	virtual int getY() { return bound.y; }
	virtual int getW() { return bound.w; }
	virtual int getH() { return bound.h; }

	virtual float getAspectRatio() {
		return bound.w / (float)bound.h;
	}

	virtual void draw(TextEngine *textEngine) = 0;

	virtual ~Attachment() {
		
	}
};