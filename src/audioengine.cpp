#include "..\include\audioengine.h"
#include "..\openal\AL\al.h"
#include "..\openal\AL\alc.h"

AudioEngine* AudioEngine::engine = nullptr;

AudioEngine & AudioEngine::Instance() {
	if (!engine)
		engine = new AudioEngine();
	return *engine;
}

void AudioEngine::Init() {
	device = alcOpenDevice(nullptr);
	context = alcCreateContext(reinterpret_cast<ALCdevice *>(device), nullptr); 
	alcMakeContextCurrent(reinterpret_cast<ALCcontext *>(context));
}

void AudioEngine::Finish() {
	alcDestroyContext(reinterpret_cast<ALCcontext *>(context));
	alcCloseDevice(reinterpret_cast<ALCdevice *>(device));
}

void AudioEngine::SetDopplerFactor(float factor) {
	alDopplerFactor(factor);
}

AudioEngine::~AudioEngine(void) {
}
