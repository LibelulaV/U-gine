#ifndef UGINE_ISOMETRIC_SCENE_H
#define UGINE_ISOMETRIC_SCENE_H

#include "isometricsprite.h"
#include "mapscene.h"
class IsometricMap;

class IsometricScene : public MapScene {
public:
	IsometricScene(IsometricMap* map, Image* imageBack = NULL, Image* imageFront = NULL);
	virtual IsometricSprite* CreateSprite(Image* image, Layer layer = LAYER_BACK);
	virtual void Update(double elapsed);
protected:
	static bool CompareSprites(Sprite*& first, Sprite*& second);
};

#endif