#pragma once

#include "page.h"
#include "./attachments/bubble.h"

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

	void addPage() {
		pages.push_back(Page(1000,1410));
	}

	void setActivePage(int id) {
		if (id >= 0 && id <= pages.size())
		activePage = id;
	}

	int getAttachmentCount() {
		normPage();
		return pages[activePage].getAttachmentCount();
	}

	int getPanelCount() {
		normPage();
		return pages[activePage].getPanelCount();
	}

	int getAttachmentPanel(int id) {
		normPage();
		return pages[activePage].getAttachmentPanel(id);
	}

	int getAttachmentType(int id) {
		normPage();
		return pages[activePage].getAttachmentType(id);
	}

	void setAttachmentPanel(int id, int panel) {
		normPage();
		pages[activePage].setAttachmentPanel(id, panel);
	}

	void addIllust(Image img) {
		normPage();
		pages[activePage].addIllust(img);
	}

	void addBubble(Bubble bubble) {
		normPage();
		pages[activePage].addBubble(bubble);
	}

	void addText(Text text) {
		normPage();
		pages[activePage].addText(text);
	}

	void update() {
		normPage();
		pages[activePage].update();
	}

	void draw(TextEngine *textEngine) {
		normPage();
		pages[activePage].draw(textEngine);
	}

	Page* getActivePage() {
		normPage();
		return &pages[activePage];
	}
};