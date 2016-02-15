#include "../include/mousecontroller.h"
#include "../include/imouselistener.h"
#include "../include/inputmanager.h"
#include "../include/glinclude.h"

IMouseListener * MouseController::m_pListener = nullptr; 

void MouseController::Init()
{
	glfwSetMousePosCallback(&MousePosCallback);
	glfwSetMouseButtonCallback(&MouseButtonCallback);
	glfwSetMouseWheelCallback(&MouseWheelCallback);
}

MouseController::MouseController(IMouseListener * pListener) 
{
	m_pListener = pListener;
}

void MouseController::MousePosCallback(int coordX, int coordY)
{
	m_pListener->MousePosition(coordX, coordY);
}

void MouseController::MouseButtonCallback(int buttonCode, int action)
{
	if (action == GLFW_PRESS)
		m_pListener->MouseButtonDown(buttonCode);

	if (action == GLFW_RELEASE)
		m_pListener->MouseButtonUp(buttonCode);
}

void MouseController::MouseWheelCallback(int wheelPos)
{
	m_pListener->MouseWheelPosition(wheelPos);
}


