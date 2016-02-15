#ifndef UGINE_ISOMETRIC_SPRITE_H
#define UGINE_ISOMETRIC_SPRITE_H

#include "sprite.h"

class IsometricSprite : public Sprite {
public:
	IsometricSprite(Image* image);
	virtual void SetPosition(double x, double y, double z);
	virtual void SetZ(double z);
	virtual double GetZ() const;
	virtual double GetScreenX() const;
	virtual double GetScreenY() const;
	virtual void SetCollision(CollisionMode mode);
	virtual void Update(double elapsed, const Map* map = NULL);
protected:
	virtual void UpdateCollisionBox();
private:
	double z;
	double screenX, screenY;
};

#endif