#pragma once

#include "page.h"

#include <vector>
using namespace std;

class Comic {
private:
	vector<Page> pages;
	int activePage = 0;

	void normPage() {
		if (pages.size() == 0)
			pages.push_back(Page(1000,1410));

		if (activePage < 0) activePage = 0;
		else if (activePage >= pages.size()) activePage = pages.size() - 1;
	}
public:
	Comic() {
		pages.push_back(Page(1000,1410));
	}

	void loadFromMemory(unsigned char *data) {

	}

	void writeToMemory(unsigned char *data, unsigned long long *size) {

	}

	void addIllust(Image img) {
		normPage();
		pages[activePage].addIllust(img);
	}

	void update() {
		normPage();
		pages[activePage].update();
	}

	void draw() {
		normPage();
		pages[activePage].draw();
	}

	Page* getActivePage() {
		normPage();
		return &pages[activePage];
	}
};