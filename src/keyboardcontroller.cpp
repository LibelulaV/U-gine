#include "../include/keyboardcontroller.h"
#include "../include/inputmanager.h"
#include "../include/glinclude.h"

IKeyboardListener * KeyboardController::m_pListener = nullptr;

void KeyboardController::Init()
{
	glfwSetKeyCallback(&KeyboardKeyCallback);
	glfwSetCharCallback(&KeyboardCharCallback);
}

KeyboardController::KeyboardController(IKeyboardListener * pListener)
{
	m_pListener = pListener;
}

void KeyboardController::KeyboardKeyCallback(int key, int action)
{
	if (action == GLFW_PRESS)
		m_pListener->KeyboardKeyPress(key);

	if (action == GLFW_RELEASE)
		m_pListener->KeyboardKeyRelease(key);
}

void KeyboardController::KeyboardCharCallback(int c, int action)
{
	if (action == GLFW_PRESS)
		m_pListener->KeyboardCharPress(c);

	if (action == GLFW_RELEASE)
		m_pListener->KeyboardCharRelease(c);
}
