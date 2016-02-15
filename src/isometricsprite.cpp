#include "..\include\isometricsprite.h"
#include "..\include\math.h"
#include "..\include\image.h"
#include <math.h>

IsometricSprite::IsometricSprite(Image * image) : Sprite(image) {
	z = 0; 
	screenX = 0; 
	screenY = 0; 
}

void IsometricSprite::SetPosition(double x, double y, double z) {
	Sprite::SetPosition(x, y);
	this->z = z; 
}

void IsometricSprite::SetZ(double z) {
	this->z = z;
}

double IsometricSprite::GetZ() const {
	return z;
}

double IsometricSprite::GetScreenX() const {
	return screenX;
}

double IsometricSprite::GetScreenY() const {
	return screenY;
}

void IsometricSprite::SetCollision(CollisionMode mode) {
	Sprite::SetCollision(mode);
}

void IsometricSprite::Update(double elapsed, const Map * map) {
	Sprite::Update(elapsed, map);
	TransformIsoCoords(Sprite::GetX(), Sprite::GetY(), z, &screenX, &screenY);
}

void IsometricSprite::UpdateCollisionBox() {
	double x, y, w, h; 
	x = screenX - (Sprite::GetImage())->GetHandleX() * fabs(Sprite::GetScaleX());
	y = screenY - Sprite::GetImage()->GetHandleY() * fabs(Sprite::GetScaleY());
	w = Sprite::GetImage()->GetWidth() * fabs(Sprite::GetScaleX());
	h = Sprite::GetImage()->GetHeight() * fabs(Sprite::GetScaleY());
	Sprite::UpdateCollisionBox(x, y, w, h);
}
