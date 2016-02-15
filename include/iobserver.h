#ifndef UGINE_IOBSERVER_H
#define UGINE_IOBSERVER_H

#include "event.h"

class IObserver {
public:
	virtual void OnMouseEvent(CMouseEvent * data) { };
	virtual void OnKeyboardEvent(CKeyboardEvent * data) { };
};

#endif

