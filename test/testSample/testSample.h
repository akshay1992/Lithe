#include "gtest/gtest.h"
#include "Lithe/LitheCore.h"

using namespace lithe;

// The fixture for testing class Block.
class SampleTest : public ::testing::Test {

protected:
    SphericalAtlas atlas;

    // You can do set-up work for each test here.
    SampleTest();
    
    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~SampleTest();

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();

    void test_toSpherical_Az(float az, float expected);
    void test_toSpherical_El(float el, float expected);
    void toCartExpected(float az, float el, float r, float& x, float& y, float& z);
};
