#include "testToricAtlas.h"
#include "TestAtlas.h"

ToricAtlasTest::ToricAtlasTest(void) {}

ToricAtlasTest::~ToricAtlasTest(void) {}

void ToricAtlasTest::SetUp(void) {}

void ToricAtlasTest::TearDown(void) {}

TEST_F(ToricAtlasTest, constructorTest)
{
	float R = 5, r = 1;
	ToricTestAtlas default_torus(R, r);

	EXPECT_FLOAT_EQ(default_torus.getURange().minVal, -1);
	EXPECT_FLOAT_EQ(default_torus.getVRange().minVal, -1);
	EXPECT_FLOAT_EQ(default_torus.getURange().maxVal, 1);
	EXPECT_FLOAT_EQ(default_torus.getVRange().maxVal, 1);
	EXPECT_FLOAT_EQ(default_torus.getURange().range, 2);
	EXPECT_FLOAT_EQ(default_torus.getVRange().range, 2);
	EXPECT_FLOAT_EQ(default_torus.getURange().half_range, 1);
	EXPECT_FLOAT_EQ(default_torus.getVRange().half_range, 1);
	EXPECT_FLOAT_EQ(default_torus.getURange().mid, 0);
	EXPECT_FLOAT_EQ(default_torus.getVRange().mid, 0);
	EXPECT_FLOAT_EQ(default_torus.getr(), r);
	EXPECT_FLOAT_EQ(default_torus.getR(), R);

	lithe::Range u(-10, 1), v(-1,2);
	ToricTestAtlas custom_torus(R, r, u, v);

	EXPECT_FLOAT_EQ(custom_torus.getURange().minVal, -10);
	EXPECT_FLOAT_EQ(custom_torus.getVRange().minVal, -1);
	EXPECT_FLOAT_EQ(custom_torus.getURange().maxVal, 1);
	EXPECT_FLOAT_EQ(custom_torus.getVRange().maxVal, 2);
	EXPECT_FLOAT_EQ(custom_torus.getURange().range, 11);
	EXPECT_FLOAT_EQ(custom_torus.getVRange().range, 3);
	EXPECT_FLOAT_EQ(custom_torus.getURange().half_range, 5.5);
	EXPECT_FLOAT_EQ(custom_torus.getVRange().half_range, 1.5);
	EXPECT_FLOAT_EQ(custom_torus.getURange().mid, -4.5);
	EXPECT_FLOAT_EQ(custom_torus.getVRange().mid, 0.5);
	EXPECT_FLOAT_EQ(custom_torus.getr(), r);
	EXPECT_FLOAT_EQ(custom_torus.getR(), R);

	r = -1; R = 4;
	EXPECT_THROW( lithe::ToricAtlas bad_torus(R, r), std::range_error);
	r = 1; R = -1;
	EXPECT_THROW( lithe::ToricAtlas bad_torus(R, r), std::range_error);
	r = -121; R = -1;
	EXPECT_THROW( lithe::ToricAtlas bad_torus(R, r), std::range_error);
}

TEST_F(ToricAtlasTest, isRiemannian)
{
	ToricAtlas tor(1, 40);
	EXPECT_TRUE( tor.isRiemannian() );
}

TEST_F(ToricAtlasTest, u_cart)
{
	float R = 5, r = 1;
	ToricTestAtlas utorus(R, r);

	std::vector<float> expected_u = 
			#include "expected_u.h"

	for(int i=0; i<xyz_inputs.size(); ++i)
	{
		float x = xyz_inputs[i][0];
		float y = xyz_inputs[i][1];
		float z = xyz_inputs[i][2];
		EXPECT_FLOAT_EQ( utorus.u_cart(x, y, z), expected_u[i]);
	}
}

TEST_F(ToricAtlasTest, v_cart)
{
	float R = 5, r = 1;
	ToricTestAtlas vtorus(R, r);

	std::vector<float> expected_v =
			#include "expected_v.h"

	for(int i=0; i<xyz_inputs.size(); ++i)
	{
		float x = xyz_inputs[i][0];
		float y = xyz_inputs[i][1];
		float z = xyz_inputs[i][2];
		EXPECT_FLOAT_EQ( vtorus.v_cart(x, y, z), expected_v[i]);
	}
}

TEST_F(ToricAtlasTest, x)
{
	float R = 5, r = 1;
	ToricTestAtlas xtorus(R, r);

 	// Pre-computed results in python. 
	// Used equation:  x =  ( R + r cos( v * M_PI) ) cos( u * M_PI)
	std::vector<float> expected_x = 
	{6.0,
 	4.0397063143230572,
	 4.0397063143230572,
	 -3.850774084288294,
	 -3.850774084288294,
	 -3.850774084288294,
	 -3.850774084288294,
	 0.78217232520115465,
	 0.78217232520115465,
	 0.78217232520115465,
	 0.78217232520115465,
	 -1.854101966249684,
	 -1.854101966249684,
	 -1.854101966249684};

	for(int i=0; i< uv_inputs.size(); ++i)
	{
		float u = uv_inputs[i][0]; 
		float v = uv_inputs[i][1];
		EXPECT_FLOAT_EQ( xtorus.x(u, v) , expected_x[i] );
	}

	EXPECT_THROW( xtorus.x(0.5, -1.4), std::range_error);
	EXPECT_THROW( xtorus.x(-1.5, -1.4), std::range_error);
	EXPECT_THROW( xtorus.x(-1.5, -0.4), std::range_error);
	EXPECT_NO_THROW( xtorus.x(0.99, 0.1));
}

TEST_F(ToricAtlasTest, y)
{
	float R = 5, r = 1;
	ToricTestAtlas ytorus(R, r);

	// Pre-computed results in python. 
	// Used equation:  y =  ( R + r cos( v * M_PI) ) sin( u * M_PI);
	std::vector<float> expected_y =
	{ 	0.0,
		0.0,
		0.0,
		1.2511923457285008,
		1.2511923457285008,
		-1.2511923457285008,
		-1.2511923457285008,
		4.9384417029756893,
		4.9384417029756893,
		-4.9384417029756893,
		-4.9384417029756893,
		5.7063390977709219,
		-5.7063390977709219,
		-5.7063390977709219};


	 for(int i=0 ; i< uv_inputs.size() ; ++i)
	{
		float u = uv_inputs[i][0]; 
		float v = uv_inputs[i][1];
		EXPECT_FLOAT_EQ( ytorus.y(u, v) , expected_y[i] );
	}

	EXPECT_THROW( ytorus.y(0.5, -1.4), std::range_error);
	EXPECT_THROW( ytorus.y(-1.5, -1.4), std::range_error);
	EXPECT_THROW( ytorus.y(-1.5, -0.4), std::range_error);
	EXPECT_NO_THROW( ytorus.y(0.99, 0.1));

}

TEST_F(ToricAtlasTest, z)
{
	float R = 5, r = 1;
	ToricTestAtlas ztorus(R, r);

 	// Pre-computed results in python. 
	// Used equation:  z = r * sin(v) 
	std::vector<float> expected_z =
	{	0.0,
		 0.27899110603922911,
		 -0.27899110603922911,
		 0.30901699437494751,
		 -0.30901699437494751,
		 -0.30901699437494751,
		 0.30901699437494751,
		 1.0,
		 -1.0,
		 -1.0,
		 1.0,
		 0.0,
		 0.0,
		 0.0};

 	for(int i=0 ; i< uv_inputs.size() ; ++i)
	{
		float u = uv_inputs[i][0]; 
		float v = uv_inputs[i][1];
		EXPECT_FLOAT_EQ( ztorus.z(u, v) , expected_z[i] );
	}

	EXPECT_THROW( ztorus.z(0.5, -1.4), std::range_error);
	EXPECT_THROW( ztorus.z(-1.5, -1.4), std::range_error);
	EXPECT_THROW( ztorus.z(-1.5, -0.4), std::range_error);
	EXPECT_NO_THROW( ztorus.z(0.99, 0.1));
}

TEST_F(ToricAtlasTest, distanceFunction)
{
	// TODO
}