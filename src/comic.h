#pragma once

#include "page.h"

#include <vector>
using namespace std;

class Comic {
private:
	vector<Page> pages;
	int activePage = 0;

public:
	Comic() {
		pages.push_back(Page(1000,1410));
	}

	void loadFromMemory(unsigned char *data) {

	}

	void writeToMemory(unsigned char *data, unsigned long long *size) {

	}

	void update() {
		if (activePage < pages.size())
			pages[activePage].update();
	}

	void draw() {
		if (activePage < pages.size())
			pages[activePage].draw();
	}

	void slice(Paths sliceLines) {
		if (activePage < pages.size())
			pages[activePage].slice(sliceLines);
	}
};