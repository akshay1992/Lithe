#ifndef DSPSINK
#define DSPSINK

class DSPSink : public Sink
{
public:
	DSPSink(void) : Sink(1)
	{
		value = 1;
		set_DSP_method((DSP_Method)& DSPSink::myDSP);
	}

	void myDSP(void)
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

#endif // DSPSINK

