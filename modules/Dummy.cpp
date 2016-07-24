#include "Dummy.h"

Dummy::Dummy() 
{
    val = 10;
}

void Dummy::timesTwo(void)
{
    val*= 2;
}

int Dummy::value(void)
{
    return val;
}

void Dummy::setValue(int number)
{
    val = number;
}

