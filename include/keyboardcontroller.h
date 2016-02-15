#ifndef UGINE_KEYBOARD_CONTROLLER_H
#define UGINE_KEYBOARD_CONTROLLER_H

#include "ikeyboardlistener.h"

class KeyboardController {
public:
	KeyboardController(IKeyboardListener *pListener);
	static void KeyboardKeyCallback(int key, int action);
	static void KeyboardCharCallback(int c, int action);
	void Init();
private:
	static IKeyboardListener * m_pListener;
};

#endif

