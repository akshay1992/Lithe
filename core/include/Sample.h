#ifndef SAMPLE_H
#define SAMPLE_H

#define BUFFER_SIZE 128

typedef float sample_t;

class Sample
{
public:
	Sample(sample_t audio=0, sample_t az=0, sample_t el=0, sample_t d=0) :
		audio(audio), 
		az(az), 
		el(el),
		d(d)
	{	}

	Sample to_spherical(void)
	{
		return Sample();
	}

	sample_t audio;
	sample_t az;
	sample_t el;
	sample_t d;
};


#endif //SAMPLE_H