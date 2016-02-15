#include "..\include\camera.h"
#include "..\include\screen.h"


Camera::Camera() {
	x = y = boundx0 = boundy0 = boundx1 = boundy1 = 0; 
	followingSprite = NULL; 
}

void Camera::SetPosition(double x, double y) {
	this->x = x; 
	this->y = y; 
}

void Camera::SetX(double x) {
	this->x = x;
}

void Camera::SetY(double y) {

	this->y = y;

}

double Camera::GetX() const {
	return this->x;
}

double Camera::GetY() const {
	return this->y;
}

void Camera::SetBounds(double bx0, double by0, double bx1, double by1) {
	this->boundx0 = bx0; 
	this->boundx1 = bx1; 
	this->boundy0 = by0; 
	this->boundy1 = by1; 
}

bool Camera::HasBounds() const {
	return !(this->boundx0 == this->boundx1);
}

double Camera::GetMinX() const {
	return this->boundx0;
}

double Camera::GetMinY() const {
	return this->boundy0;
}

double Camera::GetMaxX() const {
	return this->boundx1;
}

double Camera::GetMaxY() const {
	return this->boundy1;
}

void Camera::FollowSprite(Sprite * sprite) {
	this->followingSprite = sprite; 
}

void Camera::Update() {
	if (this->followingSprite) {
		double coordX = followingSprite->GetScreenX() - Screen::Instance().GetWidth() / 2; 
		double coordY = followingSprite->GetScreenY() - Screen::Instance().GetHeight() / 2;
		if (HasBounds()){
			if (coordX < boundx0)
				this->SetX(boundx0);
			else if (coordX > boundx1 - Screen::Instance().GetWidth())
				this->SetX(boundx1 - Screen::Instance().GetWidth());
			else
				this->SetX(coordX);

			if (coordY < boundy0)
				this->SetY(boundy0);
			else if (coordY > boundy1 - Screen::Instance().GetHeight())
				this->SetY(boundy1 - Screen::Instance().GetHeight());
			else
				this->SetY(coordY);
		}
		else {
			this->SetX(coordX);
			this->SetY(coordY);
		}
	}	
}
