#include "../include/inputmanager.h"
#include "../include/gesturemanager.h"
#include <time.h>  

#define CLICK_MAX_TIME 0.3
#define DOUBLE_CLICK_MAX_TIME 0.5

ClickManager::ClickManager()
{
	m_onButtonDown = false;
	m_start = 0;
	m_stop = 0;
}

void ClickManager::ProcessEvent(CEvent* e)
{
	if (e->GetType() == ON_MOUSE_EVENT) {
		CMouseEvent * mouseEvent = static_cast<CMouseEvent*>(e);
		if (mouseEvent->GetAction() == ON_BUTTON_DOWN && mouseEvent->GetButton() == LEFT_BUTTON) {
			m_onButtonDown = true; 
			time(&m_start);
		}
		else if (mouseEvent->GetAction() == ON_BUTTON_UP && mouseEvent->GetButton() == LEFT_BUTTON && m_onButtonDown) {
			time(&m_stop);
			if (difftime(m_stop, m_start) <= CLICK_MAX_TIME) {
				CMouseEvent * click = new CMouseEvent(ON_MOUSE_EVENT, ON_CLICK, LEFT_BUTTON);
				InputManager::Instance().AddEvent(click);
			}
			m_onButtonDown = false; 
			m_start = 0; 
			m_stop = 0; 
		}
	}
}

DragManager::DragManager()
{
	m_onButtonDown = false;
	m_onDragBegin = false; 
}

void DragManager::ProcessEvent(CEvent * e)
{
	if (e->GetType() == ON_MOUSE_EVENT) {
		CMouseEvent * mouseEvent = static_cast<CMouseEvent*>(e);
		if (mouseEvent->GetAction() == ON_BUTTON_DOWN && mouseEvent->GetButton() == LEFT_BUTTON) {
			m_onButtonDown = true;
		}
		else if (mouseEvent->GetAction() == ON_CURSOR_CHANGE && m_onButtonDown) {
			m_onDragBegin = true; 
			CMouseEvent * dragBegin = new CMouseEvent(ON_MOUSE_EVENT, ON_DRAG_BEGIN, LEFT_BUTTON);
			InputManager::Instance().AddEvent(dragBegin);
		}
		else if (mouseEvent->GetAction() == ON_BUTTON_UP && mouseEvent->GetButton() == LEFT_BUTTON) {
			if (m_onDragBegin) {
				CMouseEvent * dragEnd = new CMouseEvent(ON_MOUSE_EVENT, ON_DRAG_END, LEFT_BUTTON);
				InputManager::Instance().AddEvent(dragEnd);
			}
			m_onButtonDown = false; 
			m_onDragBegin = false; 
		}
	}
}

DoubleClickManager::DoubleClickManager()
{
	m_onButtonDown = false;
	m_count = 0; 
	m_start = 0;
	m_stop = 0;
	m_first = 0;
	m_last = 0;
}

void DoubleClickManager::ProcessEvent(CEvent * e)
{
	if (e->GetType() == ON_MOUSE_EVENT) {
		CMouseEvent * mouseEvent = static_cast<CMouseEvent*>(e);
		if (mouseEvent->GetAction() == ON_BUTTON_DOWN && mouseEvent->GetButton() == LEFT_BUTTON) {
			m_onButtonDown = true;
			time(&m_start);
		}
		else if (mouseEvent->GetAction() == ON_BUTTON_UP && mouseEvent->GetButton() == LEFT_BUTTON && m_onButtonDown) {
			time(&m_stop);
			if (difftime(m_stop, m_start) <= CLICK_MAX_TIME) {
				m_count++; 
				if (m_count == 1)
					time(&m_first);
				else if (m_count == 2) {
					time(&m_last);
					if (difftime(m_last, m_first) <= DOUBLE_CLICK_MAX_TIME) {
						CMouseEvent * doubleClick = new CMouseEvent(ON_MOUSE_EVENT, ON_DOUBLE_CLICK, LEFT_BUTTON);
						InputManager::Instance().AddEvent(doubleClick);
						m_count = 0; 
						m_first = 0; 
					}
					else {
						m_count --;
						m_first = m_last;
					}
					m_last = 0; 
				}
			}
			m_onButtonDown = false;
			m_start = 0;
			m_stop = 0;
		}
		else {
			m_onButtonDown = false;
			m_start = 0;
			m_stop = 0;
			m_first = 0;
			m_last = 0;
		}
	}
}
