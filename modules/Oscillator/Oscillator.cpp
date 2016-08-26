#include "Oscillator.h"

#include "Sample.h"

Oscillator::Oscillator(void) : 
	Node(0, 4)
{
	freq(440.0);
}

void Oscillator::freq(float freq)
{
	frequency = freq;
	sine.freq(frequency);
	square.freq(frequency);
	dwo.freq(frequency);
	saw.freq(frequency);
}

void Oscillator::DSP(void)
{
	getOutlet(0).setSample( Sample( sine(), az, el, d) );
	getOutlet(1).setSample( Sample( square(), az, el, d) );
	getOutlet(2).setSample( Sample( dwo.tri(), az, el, d) );
	getOutlet(3).setSample( Sample( saw(), az, el, d) );
}