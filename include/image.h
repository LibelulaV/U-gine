#ifndef UGINE_IMAGE_H
#define UGINE_IMAGE_H

#include "string.h"
#include "types.h"

class Image {
public:
    Image(const String& filename, uint16 hframes = 1, uint16 vframes = 1);
	virtual ~Image();

    virtual bool IsValid() const { return gltex != 0; }
    virtual const String& GetFilename() const { return filename; }
    virtual uint32 GetNumFrames() const { return hframes * vframes; }
    virtual uint16 GetHFrames() const { return hframes; }
    virtual uint16 GetVFrames() const { return vframes; }
    virtual uint16 GetWidth() const { return width / hframes; } // tamaño original
    virtual uint16 GetHeight() const { return height / vframes; } // tamaño original
    virtual void SetHandle(int32 handlex, int32 handley) { this->handlex = handlex; this->handley = handley; } // handle --> punto de la imagen en (0,0)
    virtual void SetMidHandle() { SetHandle(GetWidth()/2, GetHeight()/2); } // punto de anclaje en el centro. Lo más común --> centro (círculos) o en los "pies". 
    virtual int32 GetHandleX() const { return handlex; }
    virtual int32 GetHandleY() const { return handley; }
    virtual void Bind() const;
    virtual double GetLastU() const { return lastU; }
    virtual double GetLastV() const { return lastV; }
	virtual double GetBufferWidth() const { return buffer_width; }
	virtual double GetBufferHeight() const { return buffer_height; }
protected:
    virtual uint32 GetTexId() const { return gltex; }
private:
    String filename;
    uint16 hframes, vframes;
    uint16 width, height; // valores originales imagen
    int32 handlex, handley;
    uint32 gltex;
    double lastU, lastV; // ancho img / ancho buffer y alto img / alto buffer
	uint16 buffer_width, buffer_height; // valores originales imagen
};

#endif
