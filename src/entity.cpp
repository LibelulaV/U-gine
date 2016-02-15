#include "../include/entity.h"
#include "../include/inputmanager.h"
#include "../include/sprite.h"
#include "../include/screen.h"
#include "../include/image.h"

#include <time.h> 
#include <stdlib.h> 

CEntity::CEntity(Image * image)
{
	m_mousex = m_mousey = 0; 
	sprite = new Sprite(image);
	sprite->SetPosition(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2);
	srand(time(NULL));
	m_buttonRightPressed = false; 
}

void CEntity::Subscribe(EEvent e)
{
	InputManager::Instance().AddObserver(this, e);
}

void CEntity::Unsubscribe(EEvent e)
{
	InputManager::Instance().RemoveObserver(this, e);
}

void CEntity::OnMouseEvent(CMouseEvent * data)
{
	if (data->GetAction() == ON_CURSOR_CHANGE) {
		m_mousex = data->GetX(); 
		m_mousey = data->GetY(); 
	}	
	
	RightButtonController(data->GetAction(), data->GetButton());

	LeftButtonController(data->GetAction(), data->GetButton());
}

void CEntity::OnKeyboardEvent(CKeyboardEvent * data)
{
	if (data->GetKey() == KEY_SPACE && data->GetAction() == ON_PRESS) {
		sprite->SetPosition(Screen::Instance().GetWidth() / 2, Screen::Instance().GetHeight() / 2);
		sprite->SetColor(255, 255, 255);
	}
}

void CEntity::Update()
{
	if (m_buttonRightPressed)
		sprite->SetColor(rand() % 255, rand() % 255, rand() % 255);
	sprite->Update(Screen::Instance().ElapsedTime(), nullptr);
	sprite->Render(); 
}

void CEntity::RightButtonController(EMouseAction action, EMouseButton button) {
	if (action == ON_BUTTON_DOWN && button == RIGHT_BUTTON)
		m_buttonRightPressed = true;
	else if (action == ON_BUTTON_UP && button == RIGHT_BUTTON)
		m_buttonRightPressed = false;
}

void CEntity::LeftButtonController(EMouseAction action, EMouseButton button) {
	if (action == ON_CLICK && button == LEFT_BUTTON)
		sprite->MoveTo(m_mousex, m_mousey, 100);

	if (action == ON_DRAG_BEGIN && button == LEFT_BUTTON) {
		const Image * image = sprite->GetImage(); 
		if (m_mousex > sprite->GetX() - image->GetWidth() / 2 && m_mousex < sprite->GetX() + image->GetWidth() / 2 &&
			m_mousey > sprite->GetY() - image->GetHeight() / 2 && m_mousey < sprite->GetY() + image->GetHeight() / 2) {	
			sprite->SetPosition(m_mousex, m_mousey);
		}	
	}
}