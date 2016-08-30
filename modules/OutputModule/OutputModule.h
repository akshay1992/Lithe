#ifndef OUTPUT_MODULE_H
#define OUTPUT_MODULE_H

#include "Lithe/core/LitheCore.h"
#include "allocore/io/al_AudioIO.hpp"
#include "allocore/sound/al_AudioScene.hpp"
#include "allocore/sound/al_StereoPanner.hpp"

class OutputModule : public Sink
{
public:
	OutputModule(int numInlets, int AUDIO_BLOCK_SIZE);
	~OutputModule();

	/// Pull from connnected audiograph and pan it
	virtual void DSP(void) override ;

	/// Fills outframe with appropriate number of samples (depending on speaker layout)
	void getFrame(float outframe[]);	///< DEPRECEATED

	void startProcessing(void);
	void haltProcessing(void) { mRun = false; }
	bool isProcessing() { return mRun; } 

	al::AudioIO io;
	
private:
	bool mRun;

	int audio_block_size;
	al::StereoPanner *panner;
	al::AudioScene* scene;
	al::Listener* listener;
	al::SpeakerLayout speaker_layout;
	std::vector<al::SoundSource* > sources;
};

#endif //OUTPUT_MODULE_H