#include "..\include\audiosource.h"
#include "..\include\audiostream.h"
#include "..\openal\AL\al.h"
#include "..\openal\AL\alc.h"

#define STB_VORBIS_HEADER_ONLY
#include "..\lib\stb_vorbis.c"

AudioSource::AudioSource(AudioBuffer * buffer) {
	this->buffer = buffer; 
	this->stream = nullptr;
	alGenSources(1, &source);
	alSourcef(source, AL_LOOPING, false);
	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_BUFFER, buffer->GetBuffer());
}

AudioSource::AudioSource(const String & filename) {
	this->buffer = NULL;
	alGenSources(1, &source);	
	this->stream = new AudioStream(filename, this);
	alSourcef(source, AL_LOOPING, false);
	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	/*alSourcei(source, AL_BUFFER, NULL);*/
}

AudioSource::~AudioSource() {
	if (source)
		alDeleteSources(1, &source);
}

void AudioSource::SetPitch(float pitch) {
	alSourcef(source, AL_PITCH, pitch);
}

void AudioSource::SetGain(float gain) {
	alSourcef(source, AL_GAIN, gain);
}

void AudioSource::SetLooping(bool loop) {
	if (stream)
		stream->SetLooping(loop);
	else 
		alSourcef(source, AL_LOOPING, loop);
}

void AudioSource::SetPosition(float x, float y, float z) {
	alSource3f(source, AL_POSITION, x, y, z);
}

void AudioSource::SetVelocity(float x, float y, float z) {
	alSource3f(source, AL_VELOCITY, x, y, z);
}

void AudioSource::Play() {
	alSourcePlay(source);
}

void AudioSource::Stop() {
	alSourceStop(source);
}

void AudioSource::Pause() {
	alSourcePause(source);
}

bool AudioSource::IsPlaying() const {
	ALint state; 
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	if (state == AL_PLAYING)
		return true;
	else
		return false; 
}
