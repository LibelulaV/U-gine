#include "..\include\audiobuffer.h"
#include "..\include\file.h"
#include "..\openal\AL\al.h"
#include "..\openal\AL\alc.h"

#define STB_VORBIS_HEADER_ONLY
#include "..\lib\stb_vorbis.c"

AudioBuffer::AudioBuffer(const String & filename) {
	void * buffer; 
	ALenum format; 
	uint32 RiffChunkSize, FmtChunkSize, SampleRate, ByteRate, BufferSize; 
	uint16 AudioFormat, Channels, BlockAlign, BitsPerSample, ExtraParamsSize;
	char text[5];
	text[4] = 0; 
	alBuffer = 0;
	if (filename.ExtractExt() == "wav") {
		File * wav = new File(filename, 0);
		// empezamos a leer
		wav->ReadInt(); // "RIFF"
		RiffChunkSize = wav->ReadInt();
		wav->ReadInt(); // "WAVE"
		wav->ReadInt(); // "fmt " --> atención al espacio
		FmtChunkSize = wav->ReadInt(); 
		AudioFormat = wav->ReadInt16();
		Channels = wav->ReadInt16();
		SampleRate = wav->ReadInt();
		ByteRate = wav->ReadInt();
		BlockAlign = wav->ReadInt16();
		BitsPerSample = wav->ReadInt16();
		if (FmtChunkSize > 16) {
			ExtraParamsSize = wav->ReadInt16();
			wav->Seek(wav->Pos() + ExtraParamsSize);
		}
		// buscando "data"
		do {
			wav->ReadBytes(text, 4);
		} while (String(text) != "data");
		// seguimos leyendo
		BufferSize = wav->ReadInt();
		buffer = malloc(BufferSize);
		wav->ReadBytes(buffer, BufferSize);
		// buscamos el format
		if (BitsPerSample == 8) {
			if (Channels == 1)
				format = AL_FORMAT_MONO8;
			else
				format = AL_FORMAT_STEREO8;
		}
		else if (BitsPerSample == 16) {
			if (Channels == 1)
				format = AL_FORMAT_MONO16;
			else
				format = AL_FORMAT_STEREO16;
		}
		alGenBuffers(1, &alBuffer);
		alBufferData(alBuffer, format, buffer, BufferSize, SampleRate);
		free(buffer);
	}
	else if (filename.ExtractExt() == "ogg") {
		stb_vorbis  * pointer =  stb_vorbis_open_filename(filename.ToCString(), nullptr, nullptr);
		stb_vorbis_info info = stb_vorbis_get_info(pointer);
		int longitude = stb_vorbis_stream_length_in_samples(pointer) * info.channels;
		short * oggfile = static_cast<short *>(malloc(longitude* sizeof(short)));
		stb_vorbis_get_samples_short_interleaved(pointer, info.channels, oggfile, longitude);
		if (info.channels == 1)
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_STEREO16;
		alGenBuffers(1, &alBuffer);
		alBufferData(alBuffer, format, oggfile, longitude * sizeof(short), info.sample_rate);
		stb_vorbis_close(pointer);
		free(oggfile);
	}
}

AudioBuffer::~AudioBuffer() {
	alDeleteBuffers(1, &alBuffer);
}
