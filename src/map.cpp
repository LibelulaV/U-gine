#include "../include/map.h"
#include "../include/rectcollision.h"
#include "../include/collision.h"
#include "../include/image.h"
#include "../include/renderer.h"
#include "../include/resourcemanager.h"
#include "../include/string.h"
#include "../lib/rapidxml.hpp"
#include <limits.h>

using namespace rapidxml;

Map::Map(const String &filename, uint16 firstColId) {
	this->filename = filename; 
	this->firstColId = firstColId; 
	this->valid = false; 
	String content = String::Read(filename);
	xml_document<> doc; 
	doc.parse<0>(const_cast<char*>(content.ToCString()));
	xml_node<> * node = doc.first_node("map");
	width = String(node->first_attribute("width")->value()).ToInt(); 
	height = String(node->first_attribute("height")->value()).ToInt();
	tileWidth = String(node->first_attribute("tilewidth")->value()).ToInt();
	tileHeight = String(node->first_attribute("tileheight")->value()).ToInt();
	xml_node<> * tileset = node->first_node("tileset");
	int firstgid = String(tileset->first_attribute("firstgid")->value()).ToInt();
	int tilewidth = String(tileset->first_attribute("tilewidth")->value()).ToInt();
	int tileheight = String(tileset->first_attribute("tileheight")->value()).ToInt();

	imageFile = String(tileset->first_node("image")->first_attribute("source")->value()).StripDir(); 
	int widthT = String(tileset->first_node("image")->first_attribute("width")->value()).ToInt();
	int heightT = String(tileset->first_node("image")->first_attribute("height")->value()).ToInt();
	xml_node<>* data = node->first_node("layer")->first_node("data");
	if (data->first_attribute("encoding") || data->first_attribute("compression")) {
		return; 
	}
	xml_node<>* tile = data->first_node("tile");
	while (tile) {
		tileIds.Add(String(tile->first_attribute("gid")->value()).ToInt() - firstgid);
		tile = tile->next_sibling("tile"); 
	}
	image = ResourceManager::Instance().LoadImage(filename.ExtractDir() + "/" + imageFile, widthT / tilewidth, heightT / tileheight); 
	if (tileset->first_node("tileoffset")) {
		int x = String(tileset->first_node("tileoffset")->first_attribute("x")->value()).ToInt();
		int y = String(tileset->first_node("tileoffset")->first_attribute("y")->value()).ToInt();
		image->SetHandle(x, y);
	}
	this->valid = true; 
}

void Map::Render() const {
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= 0 ) {
				Renderer::Instance().DrawImage(image, x*GetTileWidth(), y*GetTileHeight(), GetTileId(x, y));
			}
		}
	}
}

bool Map::CheckCollision(const Collision* collision) const {
	// Creamos caja de colisiones
	double boxX = 0, boxY = 0, boxWidth = GetTileWidth(), boxHeight = GetTileHeight();
	RectCollision boxCol(&boxX, &boxY, &boxWidth, &boxHeight);
	
	// Comprobamos colision con cada tile
	for ( uint16 y = 0; y < GetRows(); y++ ) {
		for ( uint16 x = 0; x < GetColumns(); x++ ) {
			if ( GetTileId(x, y) >= firstColId ) {
				boxX = x * GetTileWidth();
				boxY = y * GetTileHeight();

				if ( collision->DoesCollide(&boxCol) )
					return true;
			}
		}
	}

	return false;
}

double Map::GetGroundY(double x, double y) const {
	double groundY = UINT_MAX;

	if ( x < 0  ||  x >= width*tileWidth  ||  y >= height*tileHeight ) return groundY;
	if ( y < 0 ) y = 0;

	// Buscamos el primer tile en esa columna
	for ( int tiley = int(y/tileHeight); tiley < height; tiley++ ) {
		if ( tileIds[tiley*width + int(x/tileWidth)] >= 0 ) {
			groundY = tiley*tileHeight;
			break;
		}
	}
	return groundY;
}
