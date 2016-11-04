#include "gtest/gtest.h"
#include "Lithe/LitheCore.h"
#include "SphericalTestAtlas.hpp"

#include <vector>
using namespace std;
using namespace lithe;

// The fixture for testing class Block.
class AtlasTest : public ::testing::Test {

protected:

    // You can do set-up work for each test here.
    AtlasTest();
    
    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~AtlasTest();

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();

    SphericalTestAtlas default_atlas;
    SphericalTestAtlas custom_atlas;

    // for testing conversion from XYZ to UV in default_atlas
    // Used in SphericalAtlas_x_y_z
    vector<vector<float>> uv = {
        { 1.0/3, 0.61 },
        { 1.0/6, 0.61 },
        { -1.0/3, 0.61 },
        { -1.0/6, 0.61 },
        { 1.0/3, -0.61 },
        { 1.0/6, -0.61 },
        { -1.0/3, -0.61 },
        { -1.0/6, -0.61 },
    };

    vector<vector<float>> xyz = {
        {0.28750262602163934, 0.4979691555789532, 0.8181497174250234},
        {0.49796915557895327, 0.28750262602163923, 0.8181497174250234},
        {0.28750262602163934, -0.4979691555789532, 0.8181497174250234},
        {0.49796915557895327, -0.28750262602163923, 0.8181497174250234},
        {0.28750262602163934, 0.4979691555789532, -0.8181497174250234},
        {0.49796915557895327, 0.28750262602163923, -0.8181497174250234},
        {0.28750262602163934, -0.4979691555789532, -0.8181497174250234},
        {0.49796915557895327, -0.28750262602163923, -0.8181497174250234}
    };

    vector<vector<float>> uv_antipodal = 
    {
        {0, 0.9},
        {0.23, 0.4},
        {-0.54, -0.2},
        {-0.2, 0.9}
    };

    vector<vector<float>> uv_antipodal_reflected = 
    {
        {-1, -0.9},
        {-0.77, -0.4},
        {+0.46, +0.2},
        {0.8, -0.9}
    };


};
