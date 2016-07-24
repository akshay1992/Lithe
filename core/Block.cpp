#include "Block.h"

Block::Block() 
{
	mValue = 1;
}

int Block::increment(int number) 
{
	mValue += number;
	return value();
}

int Block::value (void) 
{
	return mValue;
}

int Block::setValue(int number) 
{
	mValue = number;
	return value();
}

