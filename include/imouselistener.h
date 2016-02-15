#ifndef UGINE_IMOUSE_LISTENER_H
#define UGINE_IMOUSE_LISTENER_H

class IMouseListener {
public:
	virtual void MousePosition(int coordX, int coordY) = 0;
	virtual void MouseButtonDown(int button) = 0;
	virtual void MouseButtonUp(int button) = 0;
	virtual void MouseWheelPosition(int wheelPos) = 0;
};

#endif