#ifndef UGINE_INPUT_MANAGER_H
#define UGINE_INPUT_MANAGER_H

#include <map>

#include "mousecontroller.h"
#include "keyboardcontroller.h"
#include "iobserver.h"
#include "imouselistener.h"
#include "ikeyboardlistener.h"
#include "gesturemanager.h"
#include "array.h"

#include "entity.h"

class InputManager: public IMouseListener, public IKeyboardListener {
public:
	static InputManager& Instance();
	virtual void MousePosition(int coordX, int coordY);
	virtual void MouseButtonDown(int button);
	virtual void MouseButtonUp(int button);
	virtual void MouseWheelPosition(int wheelPos);
	virtual void KeyboardKeyPress(int key);
	virtual void KeyboardKeyRelease(int key);
	virtual void KeyboardCharPress(int c);
	virtual void KeyboardCharRelease(int c);
	void Init();
	void End();
	virtual void AddObserver(IObserver* observer, EEvent e);
	void RemoveObserver(IObserver* observer, EEvent e);
	void DispatchEvents();
	void DispatchMouseEvent(CEvent * eventData);
	void DispatchKeyboardEvent(CEvent * eventData);
	void AddEvent(CEvent* e);
protected:
	//InputManager();
	//virtual ~InputManager();
private:
	void RemoveEvent(CEvent * e);
	void NotifyManagers(CEvent * e);
	MouseController * m_pMouseController; 
	KeyboardController * m_pKeyboardController; 
	static InputManager * m_pManager;
	Array<CEvent*> m_events; 
	Array<IGestureManager*> m_gestureManagers; 
	std::map<EEvent, Array<IObserver*>> m_observers;
};

#endif