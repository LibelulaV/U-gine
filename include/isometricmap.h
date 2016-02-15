#ifndef UGINE_ISOMETRIC_MAP_H
#define UGINE_ISOMETRIC_MAP_H

#include "isometricscene.h"
#include "map.h"

class IsometricMap : public Map {
public:
	IsometricMap(const String& filename, uint16 firstColId = 0);
	virtual void GenerateLayerSprites(IsometricScene* scene);
	virtual uint16 GetTileWidth() const;
	virtual void Render() const;
	virtual int32 GetLayerId(uint16 column, uint16 row);
private:
	Array<int32> topLayerIds;
};

#endif
