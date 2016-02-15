#include "../include/glinclude.h"
#include "../include/inputmanager.h"
#include "../include/mousecontroller.h"
#include "../include/iobserver.h"
#include "../include/event.h"
#include "../include/entity.h"
#include "../include/array.h"

InputManager* InputManager::m_pManager = NULL;

InputManager & InputManager::Instance()
{
	if (!m_pManager)
		m_pManager = new InputManager();
	return *m_pManager;
}

void InputManager::MousePosition(int coordX, int coordY)
{
	CMouseEvent * e = new CMouseEvent(ON_MOUSE_EVENT, ON_CURSOR_CHANGE, coordX, coordY);
	m_events.Add(e);

	NotifyManagers(e);
}

void InputManager::MouseButtonDown(int button)
{
	CMouseEvent * e;
	if (button == 0) {
		e = new CMouseEvent(ON_MOUSE_EVENT, ON_BUTTON_DOWN, LEFT_BUTTON);
	}
	else if (button == 1) {
		e = new CMouseEvent(ON_MOUSE_EVENT, ON_BUTTON_DOWN, RIGHT_BUTTON);
	}
	else if (button == 2) {
		e = new CMouseEvent(ON_MOUSE_EVENT, ON_BUTTON_DOWN, MIDDLE_BUTTON);
	}
	m_events.Add(e);

	NotifyManagers(e);
}

void InputManager::MouseButtonUp(int button)
{
	CMouseEvent * e;
	if (button == 0){
		e = new CMouseEvent(ON_MOUSE_EVENT, ON_BUTTON_UP, LEFT_BUTTON);
	}
	else if (button == 1) {
		e = new CMouseEvent(ON_MOUSE_EVENT, ON_BUTTON_UP, RIGHT_BUTTON);
	}
	else if (button == 2) {
		e = new CMouseEvent(ON_MOUSE_EVENT, ON_BUTTON_UP, MIDDLE_BUTTON);
	}
	m_events.Add(e);

	NotifyManagers(e);
}

void InputManager::MouseWheelPosition(int wheelPos)
{
	CMouseEvent * e = new CMouseEvent(ON_MOUSE_EVENT, ON_WHEEL_CHANGE, wheelPos);
	m_events.Add(e);

	NotifyManagers(e);
}

void InputManager::KeyboardKeyPress(int key)
{
	CKeyboardEvent * e = new CKeyboardEvent(ON_KEYBOARD_EVENT, ON_PRESS, static_cast<EKeyboardKey>(key));
	m_events.Add(e);

	NotifyManagers(e);
}

void InputManager::KeyboardKeyRelease(int key)
{
	CKeyboardEvent * e = new CKeyboardEvent(ON_KEYBOARD_EVENT, ON_RELEASE, static_cast<EKeyboardKey>(key));
	m_events.Add(e);

	NotifyManagers(e);
}

void InputManager::KeyboardCharPress(int c)
{
	CKeyboardEvent * e = new CKeyboardEvent(ON_KEYBOARD_EVENT, ON_PRESS, c);
	m_events.Add(e);

	NotifyManagers(e);
}

void InputManager::KeyboardCharRelease(int c)
{
	CKeyboardEvent * e = new CKeyboardEvent(ON_KEYBOARD_EVENT, ON_RELEASE, c);
	m_events.Add(e);

	NotifyManagers(e);
}

void InputManager::Init()
{
	m_pMouseController = new MouseController(this);
	if (m_pMouseController)
		m_pMouseController->Init();

	m_pKeyboardController = new KeyboardController(this);
	if (m_pKeyboardController)
		m_pKeyboardController->Init();

	ClickManager * clickManager = new ClickManager(); 
	m_gestureManagers.Add(clickManager);

	DoubleClickManager * doubleClickManager = new DoubleClickManager();
	m_gestureManagers.Add(doubleClickManager);

	DragManager * dragManager = new DragManager();
	m_gestureManagers.Add(dragManager);
}

void InputManager::End()
{
	delete m_pMouseController; 
	delete m_pKeyboardController;
	
	for (unsigned int i = 0; i < m_events.Size(); i++) {
		delete m_events[i];
	}
	m_events.Clear();

	for (unsigned int i = 0; i < m_gestureManagers.Size(); i++) {
		delete m_gestureManagers[i];
	}
	m_gestureManagers.Clear();
}

void InputManager::AddObserver(IObserver* observer, EEvent e)
{
	std::map<EEvent, Array<IObserver*>>::iterator it = m_observers.find(e);

	if (it != m_observers.end())
		it->second.Add(observer);
	else {
		Array<IObserver*> observers; 
		observers.Add(observer);
		m_observers[e] = observers; 
	}
}

void InputManager::RemoveObserver(IObserver* observer, EEvent e)
{
	std::map<EEvent, Array<IObserver*>>::iterator it = m_observers.find(e);

	if (it != m_observers.end()) {
		it->second.Remove(observer);
		delete observer; 
	}
}

void InputManager::DispatchEvents()
{	
	EEvent e; 
	for (uint32 i = 0; i < m_events.Size(); i++) {
		e = m_events[i]->GetType(); 
		if (e == ON_MOUSE_EVENT) {
			DispatchMouseEvent(m_events[i]);
		}
		else if (e == ON_KEYBOARD_EVENT) {
			DispatchKeyboardEvent(m_events[i]);
		}
		RemoveEvent(m_events[i]);
	}
}

void InputManager::DispatchMouseEvent(CEvent * eventData) {
	std::map<EEvent, Array<IObserver*>>::iterator it = m_observers.find(ON_MOUSE_EVENT);
	if (it != m_observers.end()) {
		Array<IObserver*> observers = it->second;
		if (observers.Size()) {
			for (uint32 i = 0; i < observers.Size(); i++) {
				observers[i]->OnMouseEvent(static_cast<CMouseEvent *>(eventData));
			}
		}
	}	
}

void InputManager::DispatchKeyboardEvent(CEvent * eventData) {
std::map<EEvent, Array<IObserver*>>::iterator it = m_observers.find(ON_KEYBOARD_EVENT);
	if (it != m_observers.end()) {
		Array<IObserver*> observers = it->second;
		if (observers.Size()) {
			for (uint32 i = 0; i < observers.Size(); i++) {
				observers[i]->OnKeyboardEvent(static_cast<CKeyboardEvent *>(eventData));
			}
		}
	}
}

void InputManager::AddEvent(CEvent* e) {
	m_events.Add(e);
}

void InputManager::RemoveEvent(CEvent* e) {
	m_events.Remove(e); 
	delete e; 
}

void InputManager::NotifyManagers(CEvent* e) {
	for (uint32 i = 0; i < m_gestureManagers.Size(); i++)
		m_gestureManagers[i]->ProcessEvent(e);
}