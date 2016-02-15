#include "..\include\affector.h"

Affector::Affector(double rx, double ry, double regionw, double regionh) {
	this->rx = rx;
	this->ry = ry;
	this->regionw = regionw;
	this->regionh = regionh;
	this->minvelx = 0;
	this->maxvelx = 0;
	this->minvely = 0;
	this->maxvely = 0;
	this->minangvel = 0;
	this->maxangvel = 0;
	this->minr = 0;
	this->ming = 0;
	this->minb = 0;
	this->maxr = 255;
	this->maxg = 255;
	this->maxb = 255;
	this->affectVelX = false; 
	this->affectVelY = false; 
	this->affectColor = false; 
	this->affectVelAng = false; 
}

Affector::Affector(){
}

void Affector::SetRegionPosition(double x, double y) {
	this->rx = x;
	this->ry = y;
}

void Affector::SetRegionX(double x) {
	this->rx = x;
}

void Affector::SetRegionY(double y) {
	this->ry = y;
}

void Affector::SetRegionW(double w) {
	this->regionw = w;
}

void Affector::SetRegionH(double h) {
	this->regionh = h;
}

void Affector::SetVelocityX(double minvelx, double maxvelx) {
	this->minvelx = minvelx;
	this->maxvelx = maxvelx;
	this->affectVelX = true;
}

void Affector::SetVelocityY(double minvely, double maxvely) {
	this->minvely = minvely;
	this->maxvely = maxvely;
	this->affectVelY = true;
}

void Affector::SetAngularVelocity(double minangvel, double maxangvel) {
	this->minangvel = minangvel;
	this->maxangvel = maxangvel;
	this->affectVelAng = true;
}

void Affector::SetMinColor(uint8 r, uint8 g, uint8 b) {
	this->minr = r;
	this->ming = g;
	this->minb = b;
	this->affectColor = true; 
}

void Affector::SetMaxColor(uint8 r, uint8 g, uint8 b) {
	this->maxr = r;
	this->maxg = g;
	this->maxb = b;
	this->affectColor = true;
}

bool Affector::IsInRegion(int x, int y) {
	return (this->rx <= x && this->rx + regionw >= x && this->ry <= y && this->ry + regionh >= y);
}

Affector::~Affector() {
}

void Affector::affect(Particle * particle) {
	if (!particle->IsAffected() && IsInRegion(particle->GetX(), particle->GetY())) {
		if (affectColor)
			particle->SetColor(rand() % (int)(maxr - minr + 1) + minr, rand() % (int)(maxg - ming + 1) + ming, rand() % (int)(maxb - minb + 1) + minb);
		if(affectVelX)
			particle->SetVelocityX(rand() % (int)(maxvelx - minvelx + 1) + minvelx);
		if(affectVelY)
			particle->SetVelocityY(rand() % (int)(maxvely - minvely + 1) + minvely);
		if(affectVelAng)
			particle->SetAngularVelocity(rand() % (int)(maxangvel - minangvel + 1) + minangvel);
		particle->Affected();
	}
}
