#include "..\include\parallaxscene.h"
#include "..\include\screen.h"

ParallaxScene::ParallaxScene(Image * imageBack, Image * imageFront) {
	this->backLayer = imageBack; 
	this->frontLayer = imageFront; 
	this->backX = 0; 
	this->backY = 0; 
	this->frontX = 0; 
	this->frontY = 0; 
}

const Image * ParallaxScene::GetBackLayer() const {
	return this->backLayer;
}

const Image * ParallaxScene::GetFrontLayer() const {
	return this->frontLayer;
}

void ParallaxScene::SetRelativeBackSpeed(double x, double y) {
	this->relBackSpeedX = x; 
	this->relBackSpeedY = y; 
}

void ParallaxScene::SetRelativeFrontSpeed(double x, double y) {
	this->relFrontSpeedX = x;
	this->relFrontSpeedY = y; 
}

void ParallaxScene::SetAutoBackSpeed(double x, double y) {
	this->autoBackSpeedX = x; 
	this->autoBackSpeedY = y; 
}

void ParallaxScene::SetAutoFrontSpeed(double x, double y) {
	this->autoFrontSpeedX = x; 
	this->autoFrontSpeedY = y; 
}

void ParallaxScene::Update(double elapsed, Map * map) {
	Scene::Update(elapsed, map); 
	// p = v  * t 
	this->backX += this->autoBackSpeedX * elapsed;
	this->backY += this->autoBackSpeedY * elapsed;
	this->frontX += this->autoFrontSpeedX * elapsed; 
	this->frontY += this->autoFrontSpeedY * elapsed; 
}

void ParallaxScene::RenderBackground() const { // relativas * pos camara - absolutas. 

	Renderer::Instance().SetBlendMode(Renderer::ALPHA);
	if (this->backLayer)
		Renderer::Instance().DrawTiledImage(this->backLayer, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), GetCamera().GetX() * relBackSpeedX - backX, GetCamera().GetY() * relBackSpeedY - backY);
	if (this->frontLayer)
		Renderer::Instance().DrawTiledImage(this->frontLayer, 0, 0, Screen::Instance().GetWidth(), Screen::Instance().GetHeight(), GetCamera().GetX() * relFrontSpeedX - frontX, GetCamera().GetY() * relFrontSpeedY - frontY);
}
