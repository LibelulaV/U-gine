#include "..\include\audiostream.h"
#include "..\openal\AL\al.h"
#include "..\openal\AL\alc.h"

#define STB_VORBIS_HEADER_ONLY
#include "..\lib\stb_vorbis.c"

Array<AudioStream*> AudioStream::streams;

AudioStream::AudioStream(const String & filename, AudioSource * source) {
	this->source = source; 
	stream = stb_vorbis_open_filename(filename.ToCString(), NULL, NULL);
	info = stb_vorbis_get_info(stream);
	samplesLeft = stb_vorbis_stream_length_in_samples(stream) * info.channels;
	alGenBuffers(2, buffers);
	Stream(buffers[0]);
	Stream(buffers[1]);
	alSourceQueueBuffers(this->source->GetSourceId(), 2, buffers);
	streams.Add(this);
}

AudioStream::~AudioStream()
{	
	alDeleteBuffers(2, buffers);
	AudioStream * aux = this; 
	streams.Remove(aux);
}

void AudioStream::UpdateAll() {
	for (int i = 0; i < streams.Size(); i++) {
		streams[i]->Update();
	}
}

void AudioStream::Update()
{
	int value; 
	unsigned int unqueuId; 
	bool state1, state2; 
	alGetSourcei(source->GetSourceId(), AL_BUFFERS_PROCESSED, &value);
	for (int i = 0; i < value; i++)
	{
		alSourceUnqueueBuffers(source->GetSourceId(), 1, &unqueuId);
		state1 = Stream(unqueuId);
		if (state1)
			alSourceQueueBuffers(this->source->GetSourceId(), 1, &unqueuId);
		else {
			if (shouldLoop) {
				stb_vorbis_seek_start(stream);
				samplesLeft = stb_vorbis_stream_length_in_samples(stream) * info.channels;
				state2 = Stream(unqueuId);
				if (state2)
					alSourceQueueBuffers(this->source->GetSourceId(), 1, &unqueuId);
			}
		}
	}
}

bool AudioStream::Stream(unsigned int buffer)
{
	short pcm[32768];
	ALenum format; 
	int size = stb_vorbis_get_samples_short_interleaved(stream, info.channels, pcm, 32768);
	if (size) {
		if (info.channels == 1)
			format = AL_FORMAT_MONO16;
		else
			format = AL_FORMAT_STEREO16;
		alBufferData(buffer, format, pcm, size * info.channels *sizeof(short), info.sample_rate);
		samplesLeft -= size; 
		return true; 
	}
	else 
		return false;
}
