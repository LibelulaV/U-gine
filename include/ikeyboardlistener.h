#ifndef UGINE_IKEYBOARD_LISTENER_H
#define UGINE_IKEYBOARD_LISTENER_H

class IKeyboardListener {
public:
	virtual void KeyboardKeyPress(int key) = 0;
	virtual void KeyboardKeyRelease(int key) = 0;
	virtual void KeyboardCharPress(int c) = 0;
	virtual void KeyboardCharRelease(int c) = 0;
};

#endif