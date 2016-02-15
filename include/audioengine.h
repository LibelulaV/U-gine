#ifndef UGINE_AUDIO_ENGINE_H
#define UGINE_AUDIO_ENGINE_H

class AudioEngine {
public:
	static AudioEngine& Instance();
	void Init();
	void Finish();
	void SetDopplerFactor(float factor);
protected:
	AudioEngine(void) : device(nullptr), context(nullptr) {}
	~AudioEngine(void);
private:
	static AudioEngine* engine;
	void* device;
	void* context;
};

#endif