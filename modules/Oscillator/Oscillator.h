#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "Node.h"
#include "Gamma/Oscillator.h"
#include "allocore/ui/al_Parameter.hpp"

/**
	@brief An oscillator that outputs Sine, Square, Saw, and Triangle waves. 



*/
class Oscillator : public Node
{
public:
	Oscillator(void);
	~Oscillator() {}

	gam::Sine<> sine;
	gam::Square<> square;
	gam::Saw<> saw;
	gam::DWO<> dwo; /// For triangle wave

	/// Sets the frequency of the oscillator
	void freq(float freq);

	virtual void DSP(void) override;

private:
	float frequency = 440;
	float az = 0;
	float el = 0;
	float d = 0;
};


#endif // OSCILLATOR_H