#include "../include/isometricmap.h"
#include "../include/isometricscene.h"
#include "../include/isometricsprite.h"
#include "../include/image.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/string.h"
#include "../lib/rapidxml.hpp"
#include "../include/math.h"
#include <limits.h>

using namespace rapidxml;

IsometricMap::IsometricMap(const String & filename, uint16 firstColId) : Map(filename, firstColId) {
	String content = String::Read(filename);
	xml_document<> doc;
	doc.parse<0>(const_cast<char*>(content.ToCString()));
	xml_node<> * node = doc.first_node("map");

	xml_node<> * tileset = node->first_node("tileset");
	int firstgid = String(tileset->first_attribute("firstgid")->value()).ToInt();
	int tilewidth = String(tileset->first_attribute("tilewidth")->value()).ToInt();
	int tileheight = String(tileset->first_attribute("tileheight")->value()).ToInt();

	xml_node<>* data = node->first_node("layer")->next_sibling("layer")->first_node("data");
	if (data->first_attribute("encoding") || data->first_attribute("compression")) {
		return;
	}
	xml_node<>* tile = data->first_node("tile");
	while (tile) {
		topLayerIds.Add(String(tile->first_attribute("gid")->value()).ToInt() - firstgid);
		tile = tile->next_sibling("tile");
	}
	
	GetImage()->SetHandle(GetImage()->GetHandleX() + tilewidth / 2, GetImage()->GetHeight() - GetImage()->GetHandleY() - tileheight);
}

void IsometricMap::GenerateLayerSprites(IsometricScene * scene) {
	int32 id;
	IsometricSprite * sprite;
	for (uint32 colum = 0; colum < GetColumns(); colum++) {
		for (uint32 row = 0; row < GetRows(); row++) {
			id = topLayerIds[colum * GetColumns() + row];
			if (id > -1) {
				sprite = scene->CreateSprite(GetImage()); 
				sprite->SetCurrentFrame(id); 
				sprite->SetPosition(row * GetTileWidth(), colum * GetTileHeight(), 0);
				if (id >= GetFirstColId()) {
					sprite->SetCollision(Sprite::COLLISION_RECT); 
				}
			}
		}
	}
}

uint16 IsometricMap::GetTileWidth() const {
	return Map::GetTileWidth() / 2;
}

void IsometricMap::Render() const {
	double screenX, screenY; 
	for (uint16 y = 0; y < GetRows(); y++) {
		for (uint16 x = 0; x < GetColumns(); x++) {
			if (GetTileId(x, y) >= 0) {
				TransformIsoCoords(x * GetTileWidth(), y * GetTileHeight(), 0, &screenX, &screenY); // todo a z = 0
				Renderer::Instance().DrawImage(GetImage(), screenX, screenY, GetTileId(x, y));
			}
		}
	}
}

int32 IsometricMap::GetLayerId(uint16 column, uint16 row) {
	return topLayerIds[column * GetColumns() + row];
}
