#pragma once

#include "../comic.h"

class Tool {
protected:
	Comic *comic = NULL;
public:
	virtual void setTarget(Comic *comic) {
		this->comic = comic;
	}

	virtual bool handleInput() = 0;

	virtual void setParam(int id, void *value) = 0;

	virtual void reset() = 0;

	virtual void update() = 0;

	virtual void commit() = 0;

	virtual void draw() = 0;

	virtual ~Tool() {}
};