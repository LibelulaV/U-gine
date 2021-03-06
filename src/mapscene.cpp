#include "..\include\mapscene.h"

MapScene::MapScene(Map * map, Image * imageBack, Image * imageFront) : ParallaxScene(imageBack, imageFront), map(map) {
}

const Map * MapScene::GetMap() const {
	return map;
}

void MapScene::Update(double elapsed) {
	ParallaxScene::Update(elapsed, map);
}

void MapScene::RenderAfterBackground() const {
	map->Render(); 
}
