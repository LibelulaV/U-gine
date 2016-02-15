#include "math.h"
#include <math.h>

#define DEG2RAD 0.0174532925
#define RAD2DEG 57.2957795

double Log2(double x) {
	return log(x) / log(2.0);
}

double DegSin(double degrees) {
	return sin(DEG2RAD * degrees);
}

double DegCos(double degrees) {
	return cos(DEG2RAD * degrees);
}

double DegTan(double degrees) {
	return tan(DEG2RAD * degrees);
}

double DegASin(double sin) {
	return asin(sin) * RAD2DEG;
}

double DegACos(double cos) {
	return acos(cos) * RAD2DEG;
}

double DegATan(double tan) {
	return atan(tan) * RAD2DEG;
}

double DegATan2(double y, double x) {
	return atan2(y, x) * RAD2DEG;
}

double WrapValue(double val, double mod) {
    if (mod == 0) return val;
    return val - mod*floor(val/mod);
}

double Angle(double x1, double y1, double x2, double y2) {
	double dAtan = DegATan2(y1 - y2, x2 - x1);
	double resul = WrapValue(dAtan, 360); 
	return resul;
}

double Distance(double x1, double y1, double x2, double y2) {
	double x = x2 - x1; // calculo x
	double y = y2 - y1; // calculo y
	double c2 = (x*x) + (y*y); // o pow(x,2) + pow(y,2) --> cuadrado de los catetos. Pero es más eficiente hacer la multiplicación. 
	double h = sqrt(c2); // hipotenusa
	return h;
}

bool ValueInRange(double value, double min, double max) {
	return (value >= min) && (value <= max);
}

bool PointInRect(double x, double y, double rectx, double recty, double width, double height) {
	bool xInRect = ValueInRange(x, rectx, rectx + width);
	bool yInRect = ValueInRange(y, recty, recty + height);
	return xInRect && yInRect;
}

void ClosestPointToRect(double x, double y, double rectx, double recty, double width, double height, double* outx, double* outy) {
	*outx = (x < rectx) ? rectx : (x > rectx+width) ? rectx+width : x;
	*outy = (y < recty) ? recty : (y > recty+height) ? recty+height : y;
}

bool RectsOverlap(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2) {
	bool xOverlap = ValueInRange(x1, x2, x2 + width2) || ValueInRange(x2, x1, x1 + width1);
	bool yOverlap = ValueInRange(y1, y2, y2 + height2) || ValueInRange(y2, y1, y1 + height1);
	return xOverlap && yOverlap;
}

void OverlappingRect(double x1, double y1, double width1, double height1, double x2, double y2, double width2, double height2, double* outx, double* outy, double* outwidth, double* outheight) {
	// izquierda: x
	*outx = ValueInRange(x1, x2, x2 + width2) ? x1 : x2 ; 
	// arriba: y
	*outy = ValueInRange(y1, y2, y2 + height2) ? y1 : y2;
	// derecha: x + w
	*outwidth = ValueInRange(x1 + width1, x2, x2 + width2) ? (x1 +  width1) - *outx : (x2 + width2) - *outx;
	// abajo: y + h
	*outheight = ValueInRange(y1 + height1, y2, y2 + height2) ? (y1 + height1) - *outy : (y2 + height2) - *outy;
}

void TransformIsoCoords(double isoX, double isoY, double isoZ, double* screenX, double* screenY) {
	*screenX = (isoX - isoY) * DegCos(26.6);
	*screenY = isoZ + (isoX + isoY) * DegSin(26.6);
}
