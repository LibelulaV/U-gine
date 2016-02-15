#ifndef UGINE_PARTICLE_H
#define UGINE_PARTICLE_H

#include "..\include\sprite.h"

class Particle : public Sprite {
public:
	Particle();
	Particle(Image* image, double velx, double vely, double angularVel, double lifetime, bool autofade);
	virtual double GetLifetime() const;
	virtual void Update(double elapsed);
	void SetVelocityX(double velx);
	void SetVelocityY(double vely);
	void SetAngularVelocity(double angvel);
	
	void Affected();
	bool IsAffected(); 
private:
	double velocityx, velocityy;
	double angularVelocity;
	double lifetime;
	double initialLifetime;
	bool autofade;
	bool affected; 
};

#endif

