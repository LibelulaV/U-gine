#ifndef UGINE_AFFECTOR_H
#define UGINE_AFFECTOR_H

#include "particle.h"
#include "types.h"

class Affector {
public:
	Affector(double rx, double ry, double regionw, double regionh);
	Affector();
	~Affector();
	void SetRegionPosition(double x, double y);
	void SetRegionX(double x);
	void SetRegionY(double y);
	void SetRegionW(double w);
	void SetRegionH(double h);
	void SetVelocityX(double minvelx, double maxvelx);
	void SetVelocityY(double minvely, double maxvely);
	void SetAngularVelocity(double minangvel, double maxangvel);
	void SetMinColor(uint8 r, uint8 g, uint8 b);
	void SetMaxColor(uint8 r, uint8 g, uint8 b);
	bool IsInRegion(int x, int y);
	void affect(Particle * particle);
private: 
	double rx, ry;
	double regionw, regionh; 
	double minvelx, maxvelx;
	double minvely, maxvely;
	double minangvel, maxangvel;
	uint8 minr, ming, minb;
	uint8 maxr, maxg, maxb;
	bool affectColor, affectVelAng, affectVelX, affectVelY;
};

#endif
