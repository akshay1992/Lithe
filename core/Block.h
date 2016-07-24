#ifndef BLOCK_H
#define BLOCK_H

class Block 
{
public:
	Block();

	int increment(int number=1);

	int value (void);
	int setValue(int number);

private:
	int mValue;
};

#endif