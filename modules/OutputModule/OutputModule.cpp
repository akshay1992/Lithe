#include "OutputModule.h"
#include "Node.h"

#include <iostream>
using namespace std;

OutputModule::OutputModule(int numInlets, int AUDIO_BLOCK_SIZE) :	
	Sink(numInlets),  
	io(al::AudioIOData::DUMMY), 
	audio_block_size(AUDIO_BLOCK_SIZE)
{
	al::AudioDevice outdevice = al::AudioDevice::defaultOutput();
	io.deviceOut(outdevice);

	speaker_layout = al::HeadsetSpeakerLayout();
	panner = new al::StereoPanner(speaker_layout);
	scene = new al::AudioScene(audio_block_size);

	for(int i=0; i< Sink::numInlets(); i++)
	{
		sources.push_back( new al::SoundSource() );
		scene->addSource( *sources[i] );
	}

	listener = scene->createListener(panner);
	listener->compile();

	set_DSP_method((DSP_Method)& OutputModule::DSP);
}

OutputModule::~OutputModule()
{
    delete panner;
    delete scene;
    for(int i=0; i<sources.size(); i++)
    {
        delete sources[i];
    }
}

// void OutputModule::getFrame(float outframe[])
// {
// }

void OutputModule::startProcessing()
{ 
	refreshProcessOrder();	// Recompile and reset all sample delays
	listener->compile();  // Recompile the panner.

	mRun = true; 
}

void OutputModule::DSP(void)
{
	if (mRun)
	{
		for(int i=0; i<numInlets(); ++i)
		{
			if( getInlet(i).isConnected() )
			{
				cout << "HERE" << endl;
				Sample sample = getInlet(i).getSample();
				float x, y, z;
				sample.to_cartesian(x, y, z);
				sources[i]->pos(x, y, z);
				sources[i]->writeSample(sample.audio);
			}
			else
			{
				sources[i]->writeSample( 0.0 );
			}
		}
		// Write audioscene to io channels
		scene->render(io);
		Node::resetAll_ProcessState();
	}
	else
	{
		// Write zeros to the individual io channels
		for(int i=0; i<= io.channelsOut(); ++i)
		{
			io.out(i, 0.0);
		}
	}
}