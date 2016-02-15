#ifndef UGINE_GLYPH_H
#define UGINE_GLYPH_H

#include "types.h"
#include "image.h"

class Glyph {
public:
	Glyph(double offsetX, double offsetY, double width, double height);
	Glyph(); 

	double GetOffsetX() const;
	double GetOffsetY() const;

	double GetHeight() const;
	double GetWidth() const;

	void SetOffset(double offsetX, double offsetY);
	void SetHeight(double height);
	void SetWidth(double width);


private: 
	int offsetX;
	int offsetY;

	int height; 
	int width;
};

#endif