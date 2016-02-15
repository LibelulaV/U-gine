#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include "../include/renderer.h"
#include <math.h>
#include <stdlib.h>

// Declarar funciones de stb_image.c
extern "C" {
	uint8 * stbi_load(const char*, int *, int *, int *, int); // uint8 * stbi_load(const char* filename, int * x, int * y, int * comp, int req_comp);
	void stbi_image_free(void *); // void stbi_image_free(void * buffer);
}

Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	this->filename = filename;
	this->hframes = hframes;
	this->vframes = vframes;
	width = 0;
	height = 0;
	handlex = 0;
	handley = 0;
	gltex = 0; // identificador de textura. 
	lastU = 1.0;
	lastV = 1.0;

	// Cargar el buffer de la imagen
	int w, h; 
	uint8 * buffer = stbi_load(filename.ToCString(), &w, &h, NULL, 4); // RGBA --> 4

	// Generamos la textura
	if (buffer) {

		width = static_cast<uint16>(w);
		height = static_cast<uint16>(h);

		uint16 nWidth, nHeight;

		nWidth = pow(2, ceil(Log2(w)));
		nHeight = pow(2, ceil(Log2(h)));

		if (nWidth != w || nHeight != h) {

			uint8 * newBuffer = (uint8 *)malloc(nWidth * nHeight * 4); // Reservamos. 
			memset(newBuffer, 0, nWidth * nHeight * 4); // Rellenamos el buffer 

			uint8 * bufferAux = buffer;
			uint8 * newBufferAux = newBuffer;

			// Copiamos la imagen línea a línea
			for (uint16 i = 0; i < h; i++) {
				memcpy(newBuffer, buffer, w*4);
				buffer = buffer + (w * 4); 
				newBuffer = newBuffer + (nWidth * 4); 
			}

			buffer = bufferAux;
			newBuffer = newBufferAux;

			lastU = static_cast<double>(w) / static_cast<double>(nWidth);
			lastV = static_cast<double>(h) / static_cast<double>(nHeight);

			buffer_width = static_cast<uint16>(nWidth);
			buffer_height = static_cast<uint16>(nHeight);

			stbi_image_free(buffer);
			gltex = Renderer::Instance().GenImage(newBuffer, nWidth, nHeight);
			stbi_image_free(newBuffer);
		}
		else {
			// Generar la textura de OpenGL
			buffer_width = static_cast<uint16>(w);
			buffer_height = static_cast<uint16>(h);

			gltex = Renderer::Instance().GenImage(buffer, width, height);
			stbi_image_free(buffer); // equivale a un: free(buffer); 
		}
	}
}

Image::~Image() {
	Renderer::Instance().DeleteImage(gltex); // glDeleteTextures(1, &gltex);
}

void Image::Bind() const {
	// Establecer la textura actual
	Renderer::Instance().BindImage(gltex); // glBindTexture(GL_TEXTURE_2D, gltex); 
}
