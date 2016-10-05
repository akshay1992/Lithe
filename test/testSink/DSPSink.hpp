#ifndef DSPSINK
#define DSPSINK

class DSPSink : public Sink
{
public:
	DSPSink(void) : Sink(1)
	{
		value = 1;
	}

	virtual void DSP(void) override
	{
		value += 1;
	}

	int value;

};

class RawSink : public Sink
{
public:
	RawSink(void) : Sink(1)
	{
		value = 1; 
	}
	int value;
};

class StorageSink : public Sink
{
public:
	StorageSink(int numInlets) : Sink(numInlets)
	{
		for(int i=0; i< numInlets; i++)	
			inletSamples.push_back(Sample());
	}

	std::vector<Sample> inletSamples;

	virtual void DSP() override
	{
		for(int i=0; i<numInlets(); i++)
			inletSamples[i] = getInlet(i).getSample();
	}
};

#endif // DSPSINK

