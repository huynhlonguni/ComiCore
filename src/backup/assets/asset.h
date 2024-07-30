#pragma once

#include <stdint.h>

#include <string>
using namespace std;

class Asset {
protected:
	string name;
	uint64_t hash;
public:
	Asset(string name, uint64_t hash) : name(name), hash(hash) {}

	virtual void draw() = 0;
};