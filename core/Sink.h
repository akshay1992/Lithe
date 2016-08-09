#ifndef SINK_H
#define SINK_H

#include "Block.h"

#include "allocore/sound/al_AudioScene.hpp"
#include "allocore/sound/al_StereoPanner.hpp"

/** \brief A type of Block that has no outlets

	A sink is also the ending point for the directed graph from which the
	processing order is determined. 

*/
class Sink : public Block
{
public:
	Sink(int nInputs, int block_size = 512) 
		: 
		Block(nInputs, 0) //,
		audio_block_size(512)
	{
		speaker_layout = al::HeadsetSpeakerLayout();
		panner = new al::StereoPanner(speaker_layout);
		scene = new al::AudioScene(audio_block_size);

		for(int i=0; i<nInputs; i++)
		{
			sources.push_back( new al::SoundSource() );
			scene->addSource( *sources[i] );
		}

		listener = scene->createListener(panner);
		listener->compile();
	}

    ~Sink()
    {
        delete panner;
        delete scene;
        for(int i=0; i<sources.size(); i++)
        {
            delete sources[i];
        }
    }

private:
	using Block::getNumOutputs;
	using Block::getOutput;

	int audio_block_size;
	al::StereoPanner *panner;
	al::AudioScene* scene;
	al::Listener* listener;
	al::SpeakerLayout speaker_layout;
	std::vector<al::SoundSource* > sources;
};

#endif
