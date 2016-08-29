#include "testSample.h"
#include "Sample.h"
#include <vector>
SampleTest::SampleTest(void) {}

SampleTest::~SampleTest(void) {}

void SampleTest::SetUp(void) {}

void SampleTest::TearDown(void) {}

void SampleTest::test_toSpherical_Az(float az, float expected)
{
	Sample s;
	s.az = az;
	Sample sph = s.to_spherical();
	EXPECT_FLOAT_EQ(sph.az, expected);
}

void SampleTest::test_toSpherical_El(float el, float expected)
{
	Sample s;
	s.el = el;
	Sample sph = s.to_spherical();
	EXPECT_FLOAT_EQ(sph.el, expected);
}

void SampleTest::toCartExpected(float az, float el, float r, float& x, float& y, float& z)
{
	// x - front
	// y - left
	// z - up
	x = r * cos(az) * sin(el);
	y = r * -sin(az) * sin(el);
	z = r * cos(el);
}

TEST_F(SampleTest, constructorTest)
{
	Sample s;
	EXPECT_FLOAT_EQ(s.audio , 0.0);
	EXPECT_FLOAT_EQ(s.az , 0.0);
	EXPECT_FLOAT_EQ(s.el , 0.0);
	EXPECT_FLOAT_EQ(s.d , 0.0);

	s = Sample(1, 2, -4.4, -0.2);
	EXPECT_FLOAT_EQ(s.audio , 1.0);
	EXPECT_FLOAT_EQ(s.az , 2.0);
	EXPECT_FLOAT_EQ(s.el , -4.4);
	EXPECT_FLOAT_EQ(s.d , -0.2);
}

TEST_F(SampleTest, az_toSphericalTest)
{
	std::vector<float> az = {0.5, -0.5, -0.75, +0.75, -0.25, +0.25, -1, +1};
	for(int i=0; i<az.size(); i++)
	{
		float expected = az[i]*M_PI;
		test_toSpherical_Az(az[i], expected);
	}

	std::vector<float> az_outofrange = {-1.1, -180.02, +1.034};
	for(int i=0; i<az_outofrange.size(); i++)
	{
		float expected = az_outofrange[i]*M_PI;
		EXPECT_THROW(test_toSpherical_Az(az_outofrange[i], expected), std::range_error);
	}
}

TEST_F(SampleTest, el_toSphericalTest)
{
	std::vector<float> el = {0, 0.25, 0.5, 0.66, 0.88, 1.0, -0.25, -0.5, -0.66, -0.88, -1.0 };
	for(int i=0; i<el.size(); i++)
	{
		float expected = el[i]*M_PI/2;
		test_toSpherical_El(el[i], expected);
	}
	std::vector<float> el_outofrange = {-1.1, -13.02, +1.034};
	for(int i=0; i<el_outofrange.size(); i++)
	{
		float expected = el_outofrange[i]*M_PI;
		EXPECT_THROW(test_toSpherical_El(el_outofrange[i], expected), std::range_error);
	}
}

TEST_F(SampleTest, az_toCartesianTest)
{
	// TODO: A more thorough test
	std::vector<Sample> samples = 
	{
		Sample(-0.2, 1, -0.9),
		Sample(+0.2, +0.2, -1),
		Sample(-0.9, -0.45, +0.5), 
		Sample(+0.9, -0.05, 0)
	};
	for(int i=0; i< samples.size(); ++i)
	{
		float x, y, z;
		float _x, _y, _z; //expected values
		toCartExpected(samples[i].az * M_PI, samples[i].el * M_PI/2.0, Sample::getGlobalRadius() * ( 1 - samples[i].d), _x, _y, _z);
		samples[i].to_cartesian(x, y, z);
		EXPECT_FLOAT_EQ(x, _x);
		EXPECT_FLOAT_EQ(y, _y);
		EXPECT_FLOAT_EQ(z, _z);
	}

	// Out of range
	samples.clear();
	samples = 
	{
		Sample(-1.2, 1, -9.9),
		Sample(+3.2, +1.2, -1),
		Sample(-0.9, -89.45, +12.5), 
		Sample(+0.9, -88.05, 0)
	};
	for(int i=0; i< samples.size(); ++i)
	{
		float x, y, z;
		EXPECT_THROW(samples[i].to_cartesian(x, y, z), std::range_error);
	}
}