#ifndef UGINE_ENTITY_H
#define UGINE_ENTITY_H

#include "iobserver.h"
#include "sprite.h"

class CEntity : public IObserver
{
public:
	CEntity(Image* image);

	void Subscribe(EEvent e);
	void Unsubscribe(EEvent e);
	void Update();

	virtual void OnMouseEvent(CMouseEvent * data);
	virtual void OnKeyboardEvent(CKeyboardEvent * data);

	int GetX() { return m_mousex; };
	int GetY() { return m_mousey; };

	void RightButtonController(EMouseAction action, EMouseButton button);
	void LeftButtonController(EMouseAction action, EMouseButton button);
private: 
	int m_mousex, m_mousey; 
	Sprite * sprite; 
	bool m_buttonRightPressed; 
};

#endif