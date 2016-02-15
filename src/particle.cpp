#include "..\include\particle.h"

Particle::Particle() : Sprite(NULL) {

}

Particle::Particle(Image * image, double velx, double vely, double angularVel, double lifetime, bool autofade) : Sprite(image) {
	this->velocityx = velx; 
	this->velocityy = vely;
	this->angularVelocity = angularVel;
	this->initialLifetime = lifetime;
	this->lifetime = lifetime;
	this->autofade = autofade;
	this->affected = false;
}

double Particle::GetLifetime() const {
	return lifetime;
}

void Particle::Update(double elapsed) {
	
	this->SetAngle(GetAngle() + elapsed * angularVelocity);

	double despX = GetX() + elapsed * this->velocityx;
	double despY = GetY() + elapsed * this->velocityy;

	SetPosition(despX, despY);

	lifetime -= elapsed; 

	if (lifetime < 0.5 && autofade) {
		uint8 alpha = GetAlpha(); 
		if (alpha >= 5) {
			SetAlpha(alpha - 5);
		}
	}
}

void Particle::SetVelocityX(double velx) {
	this->velocityx = velx;
}

void Particle::SetVelocityY(double vely) {
	this->velocityy = vely;
}

void Particle::SetAngularVelocity(double angvel) {
	this->angularVelocity = angvel;
}

void Particle::Affected() {
	this->affected = true; 
}

bool Particle::IsAffected() {
	return affected;
}



