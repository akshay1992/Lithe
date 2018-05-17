#include "testSphericalAtlas.h"

SphericalAtlasTest::SphericalAtlasTest(void) {}

SphericalAtlasTest::~SphericalAtlasTest(void) {}

void SphericalAtlasTest::SetUp(void) {}

void SphericalAtlasTest::TearDown(void) {}

TEST_F(SphericalAtlasTest, SphericalAtlas_init)
{
	/// Tests if atlas is initialized properly
	EXPECT_FLOAT_EQ(default_atlas._radius, 1);

	EXPECT_FLOAT_EQ(default_atlas.u_range.minVal, -1);
	EXPECT_FLOAT_EQ(default_atlas.u_range.maxVal, 1);
	EXPECT_FLOAT_EQ(default_atlas.v_range.minVal, -1);
	EXPECT_FLOAT_EQ(default_atlas.v_range.maxVal, 1);

	EXPECT_FLOAT_EQ(default_atlas.u_range.mid, 0);
	EXPECT_FLOAT_EQ(default_atlas.v_range.mid, 0);
	EXPECT_FLOAT_EQ(default_atlas.u_range.range, 2);
	EXPECT_FLOAT_EQ(default_atlas.v_range.range, 2);
	EXPECT_FLOAT_EQ(default_atlas.u_range.half_range, 1);
	EXPECT_FLOAT_EQ(default_atlas.v_range.half_range, 1);

	EXPECT_TRUE(default_atlas.getType() == AtlasType::SPHERICAL);

	SphericalTestAtlas atlas_init_test(-2, 1, 0, 10, 3.5);
	EXPECT_FLOAT_EQ(atlas_init_test._radius, 3.5);

	EXPECT_FLOAT_EQ(atlas_init_test.u_range.minVal, -2);
	EXPECT_FLOAT_EQ(atlas_init_test.u_range.maxVal, 1);
	EXPECT_FLOAT_EQ(atlas_init_test.v_range.minVal, 0);
	EXPECT_FLOAT_EQ(atlas_init_test.v_range.maxVal, 10);

	EXPECT_FLOAT_EQ(atlas_init_test.u_range.mid, -0.5);
	EXPECT_FLOAT_EQ(atlas_init_test.v_range.mid, 5);
	EXPECT_FLOAT_EQ(atlas_init_test.u_range.range, 3);
	EXPECT_FLOAT_EQ(atlas_init_test.v_range.range, 10);
	EXPECT_FLOAT_EQ(atlas_init_test.u_range.half_range, 1.5);
	EXPECT_FLOAT_EQ(atlas_init_test.v_range.half_range, 5);

	EXPECT_TRUE(atlas_init_test.getType() == AtlasType::SPHERICAL);

	EXPECT_THROW( SphericalAtlas at(-12), std::range_error) ;
	EXPECT_THROW( SphericalAtlas at(0), std::range_error) ;
}

TEST_F(SphericalAtlasTest, SphericalAtlas_radius)
{
	EXPECT_FLOAT_EQ(default_atlas.radius(1,1,1), sqrt(1+1+1));
	EXPECT_FLOAT_EQ(custom_atlas.radius(2, 1, 4), sqrt(2*2+1*1+4*4));
	EXPECT_FLOAT_EQ(SphericalAtlas::radius(2, 1, 4), sqrt(2*2+1*1+4*4));
}

TEST_F(SphericalAtlasTest, SphericalAtlas_u_sph)
{
	EXPECT_FLOAT_EQ(default_atlas.u_sph(-M_PI, 0, 1),-1 );
	EXPECT_FLOAT_EQ(default_atlas.u_sph(-M_PI_2, 0, 1), -0.5);
	EXPECT_FLOAT_EQ(default_atlas.u_sph(-M_PI_4, 0, 1), -0.25);
	EXPECT_FLOAT_EQ(default_atlas.u_sph(0, 0, 1), 0 );
	EXPECT_FLOAT_EQ(default_atlas.u_sph(0.25* M_PI, 0, 1), 0.25 );
	EXPECT_FLOAT_EQ(default_atlas.u_sph(0.5* M_PI, 0, 1), 0.5 );
	EXPECT_FLOAT_EQ(default_atlas.u_sph(1*M_PI, 0, 1), 1 );

	custom_atlas = SphericalTestAtlas(-5, 5, -10, 10);
	EXPECT_FLOAT_EQ(custom_atlas.u_sph(-M_PI, 0, 1), -5);
	EXPECT_FLOAT_EQ(custom_atlas.u_sph(-M_PI_2, 0, 1), -2.5);
	EXPECT_FLOAT_EQ(custom_atlas.u_sph(-M_PI_4, 0, 1), -1.25);
	EXPECT_FLOAT_EQ(custom_atlas.u_sph(0, 0, 1), 0 );
	EXPECT_FLOAT_EQ(custom_atlas.u_sph(0.25* M_PI, 0, 1), 1.25 );
	EXPECT_FLOAT_EQ(custom_atlas.u_sph(0.5* M_PI, 0, 1), 2.5 );
	EXPECT_FLOAT_EQ(custom_atlas.u_sph(1*M_PI, 0, 1), 5 );
}

TEST_F(SphericalAtlasTest, SphericalAtlas_v_sph)
{
	EXPECT_FLOAT_EQ(default_atlas.v_sph(0, -M_PI_2, 1), -1);
	EXPECT_FLOAT_EQ(default_atlas.v_sph(0, -M_PI_4, 1), -0.5);
	EXPECT_FLOAT_EQ(default_atlas.v_sph(0, -M_PI / 8, 1), -0.25);
	EXPECT_FLOAT_EQ(default_atlas.v_sph(0, 0, 1), 0 );
	EXPECT_FLOAT_EQ(default_atlas.v_sph(0, 0.25* M_PI_2, 1), 0.25 );
	EXPECT_FLOAT_EQ(default_atlas.v_sph(0, 0.5* M_PI_2, 1), 0.5 );
	EXPECT_FLOAT_EQ(default_atlas.v_sph(0, 1*M_PI_2, 1), 1 );

	custom_atlas = SphericalTestAtlas(-5, 5, -10, 10);
	EXPECT_FLOAT_EQ(custom_atlas.v_sph(0, -M_PI_2, 1), -10);
	EXPECT_FLOAT_EQ(custom_atlas.v_sph(0, -M_PI_4, 1), -5);
	EXPECT_FLOAT_EQ(custom_atlas.v_sph(0, -M_PI / 8, 1), -2.5);
	EXPECT_FLOAT_EQ(custom_atlas.v_sph(0, 0, 1), 0 );
	EXPECT_FLOAT_EQ(custom_atlas.v_sph(0, 0.25* M_PI_2, 1), 2.5 );
	EXPECT_FLOAT_EQ(custom_atlas.v_sph(0, 0.5* M_PI_2, 1), 5 );
	EXPECT_FLOAT_EQ(custom_atlas.v_sph(0, 1*M_PI_2, 1), 10 );
}

TEST_F(SphericalAtlasTest, SphericalAtlas_theta)
{
	EXPECT_FLOAT_EQ(default_atlas.theta(0, 0), 0);
	EXPECT_FLOAT_EQ(default_atlas.theta(+0.5, 0), M_PI_2);
	EXPECT_FLOAT_EQ(default_atlas.theta(-0.125, 0), -0.125*M_PI);
	EXPECT_FLOAT_EQ(default_atlas.theta(+0.75, 0), 3*M_PI_4);
	EXPECT_THROW(default_atlas.theta(+1.1, 0), std::range_error);
	EXPECT_THROW(default_atlas.theta(0, -1.2), std::range_error);
	EXPECT_THROW(default_atlas.theta(-1.1, 0), std::range_error);
	EXPECT_THROW(default_atlas.theta(0, +1.2), std::range_error);

	custom_atlas = SphericalTestAtlas(-5, 5, -10, 10);
	EXPECT_FLOAT_EQ(custom_atlas.theta(0, 0), 0);
	EXPECT_FLOAT_EQ(custom_atlas.theta(+2.5, 0), M_PI_2);
	EXPECT_FLOAT_EQ(custom_atlas.theta(-1, 0), -1.0/5*M_PI);
	EXPECT_FLOAT_EQ(custom_atlas.theta(4, 0), 4.0/5*M_PI);
	EXPECT_THROW(custom_atlas.theta(+5.1, 0), std::range_error);
	EXPECT_THROW(custom_atlas.theta(0, -10.2), std::range_error);
	EXPECT_THROW(custom_atlas.theta(-5.1, 0), std::range_error);
	EXPECT_THROW(custom_atlas.theta(0, +10.2), std::range_error);
}

TEST_F(SphericalAtlasTest, SphericalAtlas_phi)
{
	EXPECT_FLOAT_EQ(default_atlas.phi(0, 0), 0);
	EXPECT_FLOAT_EQ(default_atlas.phi(0, +0.5), M_PI_4);
	EXPECT_FLOAT_EQ(default_atlas.phi(0, -0.125), -0.125*M_PI_2);
	EXPECT_FLOAT_EQ(default_atlas.phi(0, +0.75), 3*M_PI / 8);
	EXPECT_THROW(default_atlas.phi(+1.1, 0), std::range_error);
	EXPECT_THROW(default_atlas.phi(0, -1.2), std::range_error);
	EXPECT_THROW(default_atlas.phi(-1.1, 0), std::range_error);
	EXPECT_THROW(default_atlas.phi(0, +1.2), std::range_error);

	custom_atlas = SphericalTestAtlas(-5, 5, -10, 10);
	EXPECT_FLOAT_EQ(custom_atlas.phi(0, 0), 0);
	EXPECT_FLOAT_EQ(custom_atlas.phi(0, 0.3), 0.3/10 * M_PI_2);
	EXPECT_FLOAT_EQ(custom_atlas.phi(0, -9.23), -9.23/10 * M_PI_2);
	EXPECT_FLOAT_EQ(custom_atlas.phi(0, +7.2), 7.2/10 * M_PI_2);
	EXPECT_THROW(custom_atlas.phi(+5.1, 0), std::range_error);
	EXPECT_THROW(custom_atlas.phi(0, -10.2), std::range_error);
	EXPECT_THROW(custom_atlas.phi(-5.1, 0), std::range_error);
	EXPECT_THROW(custom_atlas.phi(0, +10.2), std::range_error);
}


TEST_F(SphericalAtlasTest, SphericalAtlas_x_y_z)
{
	for(int i=0; i<uv.size(); i++)
	{
		float u = uv[i][0];
		float v = uv[i][1];
		EXPECT_FLOAT_EQ(default_atlas.x(u, v), xyz[i][0]);
		EXPECT_FLOAT_EQ(default_atlas.y(u, v), xyz[i][1]);
		EXPECT_FLOAT_EQ(default_atlas.z(u, v), xyz[i][2]);
	}
}

TEST_F(SphericalAtlasTest, SphericalAtlas_DistanceFunction)
{
	///TODO 
}

TEST_F(SphericalAtlasTest, SphericalAtlas_reflect)
{
	for( int i=0; i< uv_antipodal.size(); i++)
	{
		float u_in = uv_antipodal[i][0];
		float v_in = uv_antipodal[i][1];
		float u_out, v_out;
		float u_expected = uv_antipodal_reflected[i][0];
		float v_expected = uv_antipodal_reflected[i][1];
		default_atlas.reflect(u_in, v_in, u_out, v_out);
		EXPECT_FLOAT_EQ(u_out, u_expected);
		EXPECT_FLOAT_EQ(v_out, v_expected);

		// Double reflection should yield same point
		float u_out_2, v_out_2;
		default_atlas.reflect(u_out, v_out, u_out_2, v_out_2);
		EXPECT_FLOAT_EQ(u_out_2, u_in);
		EXPECT_FLOAT_EQ(v_out_2, v_in);
	}

}

TEST_F(SphericalAtlasTest, SphericalAtlas_check_range)
{
	custom_atlas = SphericalTestAtlas(-2, 1, -3, 2, 5);
	EXPECT_THROW(custom_atlas.check_uv_range(-3, 1), std::range_error);
	EXPECT_THROW(custom_atlas.check_uv_range(+1.2, 1), std::range_error);
	EXPECT_THROW(custom_atlas.check_uv_range(0, 4), std::range_error);
	EXPECT_THROW(custom_atlas.check_uv_range(0, -3.1), std::range_error);
	
	EXPECT_NO_THROW(custom_atlas.check_uv_range(-2, 0));
	EXPECT_NO_THROW(custom_atlas.check_uv_range(1, 0));
	EXPECT_NO_THROW(custom_atlas.check_uv_range(0, -3));
	EXPECT_NO_THROW(custom_atlas.check_uv_range(0, 2));

	// FYI radius value doesn't matter. It isn't checked
	EXPECT_THROW(custom_atlas.check_sph_range(-M_PI-0.3, 0, 1), std::range_error);
	EXPECT_THROW(custom_atlas.check_sph_range(+M_PI+1.93, 0, 1), std::range_error);
	EXPECT_THROW(custom_atlas.check_sph_range(0, (+M_PI_2)+1.93, 1), std::range_error);
	EXPECT_THROW(custom_atlas.check_sph_range(0, (+M_PI_2)+1.93, 1), std::range_error);

	EXPECT_NO_THROW(custom_atlas.check_sph_range( 0, M_PI_2, 1));
	EXPECT_NO_THROW(custom_atlas.check_sph_range( 0, -M_PI_2, 1));
	EXPECT_NO_THROW(custom_atlas.check_sph_range( M_PI, 0, 1));
	EXPECT_NO_THROW(custom_atlas.check_sph_range( -M_PI, 0, 1));
}

TEST_F(SphericalAtlasTest, isRiemannian)
{
	SphericalTestAtlas atlas(1, 40);
	EXPECT_TRUE( atlas.isRiemannian() );
}

TEST_F(SphericalAtlasTest, getRadius) 
{
	SphericalTestAtlas atlas;
	EXPECT_FLOAT_EQ( atlas.getRadius(), atlas.radius(atlas.x(0,0), atlas.y(0,0), atlas.z(0,0)));
	EXPECT_FLOAT_EQ( atlas.getRadius(), 1);

	atlas.setRadius(32);
	EXPECT_FLOAT_EQ( atlas.getRadius(), atlas.radius(atlas.x(0,0), atlas.y(0,0), atlas.z(0,0)));
	EXPECT_FLOAT_EQ( atlas.getRadius(), 32);
}