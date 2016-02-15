#include "../include/collisionpixeldata.h"

// Declarar funciones de stb_image.c
extern "C" {
	uint8 * stbi_load(const char*, int *, int *, int *, int); // uint8 * stbi_load(const char* filename, int * x, int * y, int * comp, int req_comp);
	void stbi_image_free(void *); // void stbi_image_free(void * buffer);
}

CollisionPixelData::CollisionPixelData(const String & filename) {
	this->filename = filename; 

	// Cargar el buffer de la imagen
	int w, h;
	uint8 * buffer = stbi_load(filename.ToCString(), &w, &h, NULL, 4); // RGBA --> 4

	if (buffer) {
		width = static_cast<uint16>(w);
		height = static_cast<uint16>(h);
		data = static_cast<bool *>(malloc(w*h*sizeof(bool)));

		for (uint32 i = 3; i < w * h * 4; i += 4) {
			if (buffer[i]) 
				data[i / 4] = true; 
			else 
				data[i / 4] = false;
		}
		stbi_image_free(buffer);
	}
}

CollisionPixelData::~CollisionPixelData() {
	//eliminar data
	free(data);
}

bool CollisionPixelData::IsValid() const {
	return (data != NULL); 
}

const String & CollisionPixelData::GetFilename() const {
	return filename; 
}

uint16 CollisionPixelData::GetWidth() const {
	return width;
}

uint16 CollisionPixelData::GetHeight() const {
	return height;
}

bool CollisionPixelData::GetData(uint32 x, uint32 y) const {
	return data[y * width + x];
}
