#include "../include/collisionmanager.h"
#include "../include/math.h"

CollisionManager* CollisionManager::manager = nullptr;

const CollisionManager & CollisionManager::Instance() {
	if (!manager)
		manager = new CollisionManager();
	return *manager;
}

bool CollisionManager::CircleToCircle(double x1, double y1, double r1, double x2, double y2, double r2) const {
	return Distance(x1 + r1, y1 + r1, x2 + r2, y2 + r2) > (r1 + r2) ? false : true;
}

bool CollisionManager::CircleToPixels(double cx, double cy, double cr, const CollisionPixelData * pixels, double px, double py) const {
	bool collided = false; 
	double ox, oy, ow, oh;
	double pY, pX;
	if (RectsOverlap(px, py, pixels->GetWidth(), pixels->GetHeight(), cx, cy, cr *2, cr * 2)) {
		OverlappingRect(px, py, pixels->GetWidth(), pixels->GetHeight(), cx, cy, cr * 2, cr * 2, &ox, &oy, &ow, &oh);
		pY = oy - py;
		while (!collided && pY < oh + oy - py) {
			pX = ox - px;
			while (!collided && pX < ow + ox - px) {
				if (pixels->GetData(pX, pY) && (Distance(cx + cr, cy + cr, pX + px, pY + py) <= cr))
					collided = true;
				else
					pX++;
			}
			pY++;
		}
	}
	return collided; 
}

bool CollisionManager::CircleToRect(double cx, double cy, double cr, double rx, double ry, double rw, double rh) const {
	double nearestX;
	double nearestY;
	ClosestPointToRect(cx + cr, cy + cr, rx, ry, rw, rh, &nearestX, &nearestY);
	if (Distance(cx + cr, cy + cr, nearestX, nearestY) <= cr)
		return true;
	else
		return false;
}

bool CollisionManager::PixelsToPixels(const CollisionPixelData * p1, double x1, double y1, const CollisionPixelData * p2, double x2, double y2) const {
	bool collided = false;
	double px1, px2;
	double py1, py2;
	double ox, oy, ow, oh;
	bool col1, col2; 
	if(RectsOverlap(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight())){
		OverlappingRect(x1, y1, p1->GetWidth(), p1->GetHeight(), x2, y2, p2->GetWidth(), p2->GetHeight(), &ox, &oy, &ow, &oh);
		py1 = oy - y1; 
		py2 = oy - y2; 
		while(!collided && py1 < oh + oy - y1 && py2 <= oh + oy - y2) {
			px1 = ox - x1; 
			px2 = ox - x2; 
			while (!collided && px1 < ow + ox - x1 && px2 <= ow + ox - x2) {
				col1 = p1->GetData(px1, py1);
				col2 = p2->GetData(px2, py2);
				if (col1 && col2)
					collided = true;
				else {
					px1++; 
					px2++;
				}
			}
			py1++;
			py2++;
		}
	}
	return collided;
}

bool CollisionManager::PixelsToRect(const CollisionPixelData * pixels, double px, double py, double rx, double ry, double rw, double rh) const {
	bool collided = false;
	double ox, oy, ow, oh;
	double pY, pX;
	if (RectsOverlap(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry, rw, rh)) {
		OverlappingRect(px, py, pixels->GetWidth(), pixels->GetHeight(), rx, ry, rw, rh, &ox, &oy, &ow, &oh);
		pY = oy - py;
		while (!collided && pY < oh + oy - py) {
			pX = ox - px;
			while (!collided && pX < ow + ox - px){
				if (pixels->GetData(pX, pY))
					collided = true;
				else
					pX++;
			}
			pY++;
		}
	}
	return collided; 
}

bool CollisionManager::RectToRect(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2) const {
	if (PointInRect(x1, y1, x2, y2, w2, h2) || PointInRect(x2, y2, x1, y1, w1, h1) ||
		PointInRect(x1 + w1, y1, x2, y2, w2, h2) || PointInRect(x2 + w2, y2, x1, y1, w1, h1) ||
		PointInRect(x1 + w1, y1 + h1, x2, y2, w2, h2) || PointInRect(x2 + w2, y2 + h2, x1, y1, w1, h1) ||
		PointInRect(x1, y1 + h1, x2, y2, w2, h2) || PointInRect(x2, y2 + h2, x1, y1, w1, h1)) {
		return true;
	}
	else
		return false; 
}
