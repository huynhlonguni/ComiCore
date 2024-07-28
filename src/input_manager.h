#pragma once

#include "raylib.h"
#include "config.h"

#include <vector>
using namespace std;

class InputManager {
private:
	//Keyboard buttons
	bool currentKeyState[MAX_KEYBOARD_KEYS + MAX_MOUSE_BUTTONS];
	bool previousKeyState[MAX_KEYBOARD_KEYS + MAX_MOUSE_BUTTONS];

	bool shift;
	bool control;
	bool alt;
	bool super;

	Vector2 screenMouse;
	Vector2 worldMouse;
	Vector2 wheel;

	int gesture;
public:
	enum {
		Mouse,
		Keyboard
	};

	enum Modifier {
		Shift,
		Control,
		Alt,
		Super,
	};

	void updateMouse(Camera2D camera) {
		for (int i = 0; i < MAX_MOUSE_BUTTONS; i++)
			currentKeyState[MAX_KEYBOARD_KEYS + i] = IsMouseButtonDown(i);

		wheel = GetMouseWheelMoveV();

		screenMouse = GetMousePosition();
		worldMouse = GetScreenToWorld2D(screenMouse, camera);
	}

	void updateKeyboard() {
	    shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
		control = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
	    alt = IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT);
	    super = IsKeyDown(KEY_LEFT_SUPER) || IsKeyDown(KEY_RIGHT_SUPER);

	    for (int i = 0; i < MAX_KEYBOARD_KEYS; i++)
	    	currentKeyState[i] = IsKeyDown(i);
	}

	void updateGesture() {
		gesture = GetGestureDetected();
	}

	void update(Camera2D camera) {
		memcpy(previousKeyState, currentKeyState, sizeof(previousKeyState));
		updateMouse(camera);
		updateKeyboard();
		updateGesture();
	}

	bool isOn(Modifier modifier) {
		switch (modifier) {
			case Shift:
				return shift;
			case Control:
				return control;
			case Alt:
				return alt;
			case Super:
				return super;
		}
		return false;
	}

	bool isPressed(int button, int key, bool consume = false) {
		if (button == Mouse) key += MAX_KEYBOARD_KEYS;

		bool pressed = previousKeyState[key] == 0 && currentKeyState[key] == 1;

		if (pressed && consume) previousKeyState[key] = currentKeyState[key];

		return pressed;
	}

	bool isDown(int button, int key, bool consume = false) {
		if (button == Mouse) key += MAX_KEYBOARD_KEYS;

		bool down = currentKeyState[key] == 1;

		if (down && consume) currentKeyState[key] = 0;

		return down;
	}

	bool isReleased(int button, int key, bool consume = false) {
		if (button == Mouse) key += MAX_KEYBOARD_KEYS;

		bool released = previousKeyState[key] == 1 && currentKeyState[key] == 0;

		if (released && consume) previousKeyState[key] = currentKeyState[key];

		return released;
	}

	bool isUp(int button, int key) {
		if (button == Mouse) key += MAX_KEYBOARD_KEYS;

		return currentKeyState[key] == 0;
	}

	float getWheel(bool consume = false) {
		float result = 0.0f;

		if (fabsf(wheel.x) > fabsf(wheel.y))
			result = wheel.x;
		else
			result = wheel.y;

		if (result && consume) wheel = {0.0, 0.0};

		return result;
	}

	// Vector2 getMousePosition(bool world = false) {
	// 	if (world) return worldMouse;
	// 	else return screenMouse;
	// }

	int getMouseX(bool world = false) {
		if (world) return worldMouse.x;
		else return screenMouse.x;
	}

	int getMouseY(bool world = false) {
		if (world) return worldMouse.y;
		else return screenMouse.y;
	}

	int getGesture(bool consume = false) {
		int res = gesture;
		if (gesture && consume) gesture = GESTURE_NONE;
		return res;
	}
};