#include "..\include\font.h"
#include "..\include\string.h"
#include "..\include\image.h"
#include "..\include\array.h"
#include "..\include\glyph.h"
#include "..\include\renderer.h"

#include <math.h> 

bool IsYellow(uint32 pixel) { // ABGR
	uint32 yellow = 0xFF00FFFF;
	return (pixel == yellow);
}

bool IsRed(uint32 pixel) { // ABGR
	uint32 red = 0xFF0000FF;
	return (pixel == red);
}

bool IsBlack(uint32 pixel) { // ABGR
	uint32 black = 0xFF000000;
	return (pixel == black);
}

Font::Font(const String & filename) : Image(filename, 16, 16) {
	uint32 row;
	uint32 colum;
	uint32 * pPixel = NULL;
	uint32 * pFrame = NULL;
	uint32 offsetx;
	uint32 offsety;
	uint32 endx;
	uint32 endy;

	uint8 * buffer = (uint8 *)malloc(this->GetBufferHeight() * this->GetBufferWidth() * 4);
	Renderer::Instance().GetTextImage(buffer); 
	uint32 * intBuffer = reinterpret_cast<uint32 *>(buffer);
	glyphs = Array<Glyph>(256); 

	const uint16 FRAME_W = this->GetWidth(); 
	const uint16 FRAME_H = this->GetHeight(); 

	const uint16 H_FRAMES = this->GetHFrames();
	const uint16 V_FRAMES = this->GetVFrames();
	const uint16 TOTAL_FRAMES = this->GetNumFrames();

	const uint32 IMAGE_FULL_W = this->GetBufferWidth();
	const uint32 IMAGE_FULL_H = this->GetBufferHeight();

	for (uint32 frame = 0; frame < TOTAL_FRAMES; frame++) { // Para cada uno de los 256 ints, que son el número total de frames 

		row = frame / H_FRAMES; 
		colum = frame % H_FRAMES; 

		offsetx = offsety = 0; 
		endx = FRAME_W;
		endy = FRAME_H;

		for (uint32 y = 0; y < FRAME_H; y++) {
			for (uint32 x = 0; x < FRAME_W; x++) {
				// CALCULAR EL INDICE DEL PIXEL 
				pPixel = intBuffer + (y * IMAGE_FULL_W) + x + (colum * FRAME_W) + (row * FRAME_H * IMAGE_FULL_W);
				// si es amarillo, lo cambio a negro y asigno a initx e inity las coordenadas. 
				if (IsYellow(*pPixel)) {
					offsetx = x;
					offsety = y;
					*pPixel = 0x00000000; // con esto ademas pongo todo transparente.
				}// si encuentro el rojo, lo cambio a negro y asigno a endx y endy las coordenadas.
				else if (IsRed(*pPixel)) {
					endx = x;
					endy = y;
					*pPixel = 0x00000000;
				}
				else if (IsBlack(*pPixel))
					*pPixel = 0x00000000;
			}
		}
		glyphs.Add(Glyph(offsetx, offsety, endx - offsetx, endy - offsety));
	}
	Renderer::Instance().UpdateImage(buffer, IMAGE_FULL_W, IMAGE_FULL_H);
	free(buffer);
}

uint16 Font::GetSize() const {
	return this->GetHeight();
}

uint32 Font::GetTextWidth(const String & text) const {
	uint32 ret = 0; 
	for (uint32 i = 0; i < text.Length(); i++) {
		ret += glyphs[text[i]].GetWidth();
	}
	return ret;
}

uint32 Font::GetTextHeight(const String & text) const {
	uint32 ret = 0;
	for (uint32 i = 0; i < text.Length(); i++) {
		ret = fmax(ret, glyphs[text[i]].GetHeight());
	}
	return ret;
}

void Font::Render(const String & text, double x, double y) const {
	int length = text.Length(); 
	uint32 ret = x;
	for (int i = 0; i < length; i++) {
		Renderer::Instance().DrawImage(this, ret, y, text[i]);
		ret += glyphs[text[i]].GetWidth();
	}
}
