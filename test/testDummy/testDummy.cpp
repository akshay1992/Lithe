#include "testDummy.h"
#include "Dummy.h"
TEST_F(DummyTest, setValueTest)
{
	int value = 23;
	Dummy dummy;
	dummy.setValue(value);

	EXPECT_EQ(value, dummy.value());
}

TEST_F(DummyTest, timesTwoPositiveNumberTest)
{
    int value =12;
    Dummy dummy ;
    dummy.setValue(value);
    dummy.timesTwo();
    EXPECT_EQ (dummy.value(), value*2);
}

TEST_F(DummyTest, timesTwoNegativeNumberTest)
{
    int value = -13;
    Dummy dummy ;
    dummy.setValue(value);
    dummy.timesTwo();
    EXPECT_EQ (dummy.value(), value*2);
}
