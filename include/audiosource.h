#ifndef UGINE_AUDIO_SOURCE_H
#define UGINE_AUDIO_SOURCE_H

#include "audiobuffer.h"	

class AudioStream;

class AudioSource {
public:
	AudioSource(AudioBuffer* buffer);
	AudioSource(const String& filename);
	~AudioSource();
	void SetPitch(float pitch);
	void SetGain(float gain);
	void SetLooping(bool loop);
	void SetPosition(float x, float y, float z);
	void SetVelocity(float x, float y, float z);
	void Play();
	void Stop();
	int GetSourceId() { return source; };
	void Pause();
	bool IsPlaying() const;
private:
	unsigned int source;
	AudioBuffer* buffer;
	AudioStream* stream;
};

#endif
