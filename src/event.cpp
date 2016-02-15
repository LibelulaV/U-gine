#include "..\include\event.h"

// EVENT 
CEvent::CEvent(EEvent type)
{
	m_eType = type; 
}

EEvent CEvent::GetType() const
{
	return m_eType;
}

// MOUSE EVENT
CMouseEvent::CMouseEvent(EEvent type, EMouseAction action, EMouseButton button) : CEvent(type)
{
	m_posX = 0; 
	m_posY = 0; 
	m_posWheel = 0; 
	m_action = action;
	m_button = button; 
}

CMouseEvent::CMouseEvent(EEvent type, EMouseAction action, int x, int y) : CEvent(type)
{
	m_posX = x;
	m_posY = y;
	m_posWheel = 0;
	m_action = action;
	m_button = NULL_BUTTON;
}

CMouseEvent::CMouseEvent(EEvent type, EMouseAction action, int posWheel) : CEvent(type)
{
	m_posX = 0;
	m_posY = 0;
	m_posWheel = posWheel;
	m_action = action;
	m_button = NULL_BUTTON;
}

CMouseEvent::CMouseEvent(EEvent type, EMouseAction action) : CEvent(type)
{
	m_posX = 0;
	m_posY = 0;
	m_posWheel = 0;
	m_action = action;
	m_button = NULL_BUTTON;
}

EMouseAction CMouseEvent::GetAction() const
{
	return m_action;
}

EMouseButton CMouseEvent::GetButton() const
{
	return m_button;
}

int CMouseEvent::GetX() const
{
	return m_posX;
}

int CMouseEvent::GetY() const
{
	return m_posY;
}

// KEYBOARD EVENT
CKeyboardEvent::CKeyboardEvent(EEvent type, EKeyboardAction action, EKeyboardKey key) : CEvent(type)
{
	m_action = action;
	m_char = -1;
	m_key = key;
}

CKeyboardEvent::CKeyboardEvent(EEvent type, EKeyboardAction action, int c) : CEvent(type)
{
	m_action = action; 
	m_char = c; 
	m_key = KEY_UNKNOWN;
}

EKeyboardAction CKeyboardEvent::GetAction() const
{
	return m_action;
}

EKeyboardKey CKeyboardEvent::GetKey() const
{
	return m_key;
}

int CKeyboardEvent::GetChar() const
{
	return m_char;
}
