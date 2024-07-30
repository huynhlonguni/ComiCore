#pragma once

#include "../comic.h"
#include "../input_manager.h"

class Tool {
protected:
	Comic *comic = NULL;
public:
	virtual void setTarget(Comic *comic) {
		this->comic = comic;
	}

	virtual bool handleInput(InputManager *input) = 0;

	virtual void setParam(int id, void *value) = 0;

	virtual void reset() = 0;

	virtual void update() = 0;

	virtual void commit() = 0;

	virtual void draw(TextEngine *textEngine) = 0;

	virtual ~Tool() {}
};