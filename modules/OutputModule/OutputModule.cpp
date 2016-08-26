#include "OutputModule.h"

OutputModule::OutputModule(int numInlets) :	
	Sink(numInlets),  
	io(al::AudioIOData::DUMMY)
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
				Sample sample = getInlet(i).getSample();
			// Write sample into respective audio scene object
		}
		scene->render(io); // Need an equivalent for this			
	}
}