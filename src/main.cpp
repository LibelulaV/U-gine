#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#pragma warning(disable: 4996)

#include "../include/u-gine.h"
#include "../include/event.h"

#include <stdlib.h>

int main(int argc, char* argv[]) {
	Screen& screen = Screen::Instance();
	screen.Open(800, 600, false);

	InputManager::Instance().Init();

	Image * alien = ResourceManager::Instance().LoadImage("data/alien.png");
	alien->SetMidHandle(); 

	CEntity entity(alien); 

	entity.Subscribe(ON_MOUSE_EVENT);
	entity.Subscribe(ON_KEYBOARD_EVENT);

	String *title = new String();

	while (screen.IsOpened()) {

		InputManager::Instance().DispatchEvents(); 

		screen.SetTitle(*title);
		*title = "CURSOR POSITION: [";
		*title += title->FromInt(entity.GetX());
		*title += ",";
		*title += title->FromInt(entity.GetY());
		*title += "]   ";

		entity.Update(); 

		// Refrescamos la pantalla
		screen.Refresh();

		// Limpiar pantalla
		Renderer::Instance().Clear(0, 0, 0);
	}
	InputManager::Instance().End();
	ResourceManager::Instance().FreeResources(); 
}