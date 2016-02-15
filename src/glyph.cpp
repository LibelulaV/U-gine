#include "..\include\glyph.h"

Glyph::Glyph() {

}

Glyph::Glyph(double offsetX, double offsetY, double width, double height) {
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->width = width;
	this->height = height;
}

double Glyph::GetOffsetX() const {
	return this->offsetX;
}

double Glyph::GetOffsetY() const {
	return this->offsetY;
}

double Glyph::GetHeight() const {
	return this->height;
}

double Glyph::GetWidth() const {
	return this->width;
}

void Glyph::SetOffset(double offsetX, double offsetY) {
	this->offsetX = offsetX;
	this->offsetY = offsetY;
}

void Glyph::SetHeight(double height) {
	this->height = height;
}

void Glyph::SetWidth(double width) {
	this->width = width;
}