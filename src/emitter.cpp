#include "..\include\emitter.h"

#include <stdlib.h>
#include <time.h>  

Emitter::Emitter(Image * image, bool autofade) {

	srand(time(NULL));

	this->image = image; 
	this->autofade = autofade; 
	this->x = 0; 
	this->y = 0; 
	this->minrate = 0;
	this->maxrate = 0;
	this->minvelx = 0;
	this->maxvelx = 0;
	this->minvely = 0;
	this->maxvely = 0;
	this->minangvel = 0;
	this->maxangvel = 0;
	this->minlifetime = 0;
	this->maxlifetime = 0;
	this->minr = 0;
	this->ming = 0;
	this->minb = 0;
	this->maxr = 255;
	this->maxg = 255;
	this->maxb = 255;
	this->blendMode = Renderer::ADDITIVE; 
	this->emitting = false; 
}

Emitter::~Emitter() {
	for (uint32 i = 0; i < affectors.Size(); i++) {
		delete affectors[i];
		affectors.RemoveAt(i); 
	}
}

void Emitter::SetPosition(double x, double y) {
	this->x = x;
	this->y = y;
}

void Emitter::SetX(double x) {
	this->x = x; 
}

Affector* Emitter::CreateAffector(double rx, double ry, double regionw, double regionh) {
	Affector* affector = new Affector(rx, ry, regionw, regionh);
	affectors.Add(affector);
	return affector; 
}

void Emitter::RemoveAffector(Affector* affector) {
	affectors.Remove(affector);
	delete affector;
}

void Emitter::SetY(double y) {
	this->y = y; 
}

double Emitter::GetX() const {
	return this->x;
}

double Emitter::GetY() const {
	return this->y;
}

void Emitter::SetRate(double minrate, double maxrate) {
	this->minrate = minrate;
	this->maxrate = maxrate;
}

void Emitter::SetVelocityX(double minvelx, double maxvelx) {
	this->minvelx = minvelx;
	this->maxvelx = maxvelx;
}

void Emitter::SetVelocityY(double minvely, double maxvely) {
	this->minvely = minvely;
	this->maxvely = maxvely;
}

void Emitter::SetAngularVelocity(double minangvel, double maxangvel) {
	this->minangvel = minangvel;
	this->maxangvel = maxangvel;
}

void Emitter::SetLifetime(double minlifetime, double maxlifetime) {
	this->minlifetime = minlifetime;
	this->maxlifetime = maxlifetime;
}

void Emitter::SetMinColor(uint8 r, uint8 g, uint8 b) {
	this->minr = r;
	this->ming = g;
	this->minb = b;
}

void Emitter::SetMaxColor(uint8 r, uint8 g, uint8 b) {
	this->maxr = r; 
	this->maxg = g; 
	this->maxb = b;
}

void Emitter::SetBlendMode(Renderer::BlendMode mode) {
	this->blendMode = mode; 
}

void Emitter::Start() {
	this->emitting = true; 
}

void Emitter::Stop() {
	this->emitting = false;
}

bool Emitter::IsEmitting() const {
	return this->emitting;
}

void Emitter::Update(double elapsed) {	
	if (emitting) {
		
		double numpart = (rand() % (int)(maxrate - minrate + 1) + minrate) * elapsed;

		for (int k = 0; k < numpart; k++) {

			Particle particle = Particle(image, rand() % (int)(maxvelx - minvelx + 1) + minvelx, 
												rand() % (int)(maxvely - minvely + 1) + minvely, 
												rand() % (int)(maxangvel - minangvel + 1) + minangvel, 
												rand() % (int)(maxlifetime - minlifetime + 1) + elapsed, autofade);

			particle.SetColor(rand() % (int)(maxr - minr + 1) + minr, rand() % (int)(maxg - ming + 1) + ming, rand() % (int)(maxb - minb + 1) + minb);
			particle.SetPosition(this->x, this->y);
			particle.SetBlendMode(this->blendMode);
			particles.Add(particle);
		}
	}

	for (uint32 i = 0; i < particles.Size(); i++) {
		for (uint32 j = 0; j < affectors.Size(); j++) {
			affectors[j]->affect(&particles[i]);
		}
		particles[i].Update(elapsed); 
	}

	for (unsigned int j = 0; j < particles.Size(); j++) {
		if (particles[j].GetLifetime()<=0) {
			particles.RemoveAt(j);
		}
	}
}

void Emitter::Render() const {
	for (unsigned int i = 0; i < particles.Size(); i++) {
		particles[i].Render(); 
	}
}
