#ifndef UGINE_PIXELCOLLISION_H
#define UGINE_PIXELCOLLISION_H

#include "collision.h"
#include "../include/collisionmanager.h"
#include "resourcemanager.h"

class PixelCollision : public Collision {
public:
	PixelCollision(CollisionPixelData* pixels, double* px, double* py) : m_pixels(pixels), m_px(px), m_py(py) { }

	virtual bool DoesCollide(const Collision* other) const { return other->DoesCollide(m_pixels, *m_px, *m_py); }
	virtual bool DoesCollide(double cx, double cy, double cradius) const { return CollisionManager::Instance().CircleToPixels(cx, cy, cradius, m_pixels, *m_px, *m_py); }
	virtual bool DoesCollide(double rx, double ry, double rwidth, double rheight) const { return CollisionManager::Instance().PixelsToRect(m_pixels, *m_px, *m_py, rx, ry, rwidth, rheight); }
	virtual bool DoesCollide(const CollisionPixelData* pixels, double px, double py) const { return CollisionManager::Instance().PixelsToPixels(m_pixels, *m_px, *m_py, pixels, px, py); }
private:
	CollisionPixelData* m_pixels;
	double* m_px; 
	double* m_py;
};

#endif
