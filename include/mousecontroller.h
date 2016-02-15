#ifndef UGINE_MOUSE_CONTROLLER_H
#define UGINE_MOUSE_CONTROLLER_H

#include "imouselistener.h"

class MouseController {
public:
	MouseController(IMouseListener *pListener);
	static void MousePosCallback(int coordX, int coordY);
	static void MouseButtonCallback(int buttonCode, int action);
	static void MouseWheelCallback(int wheelPos);
	void Init(); 
private:
	static IMouseListener * m_pListener;
};

#endif

