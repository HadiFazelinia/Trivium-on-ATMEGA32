#include "trivium.h"

bool shift_func(unsigned char reg[], int size)
{
	int i = 0;
	bool bit = false;
	
	for(i = size - 1; i > 0; i--)
	{
		bit = reg[i - 1] & 0x80;
		reg[i] <<= 1;

		if(bit)
		reg[i] |= 0x01;
		else
		reg[i] &= 0xfe;
	}
	reg[0] <<= 1;
	
	bool result = false;

	if (size == 12)
	{
		result = reg[11] & 0x20;
		result ^= (reg[11] & 0x10) & (reg[11] & 0x08);
		result ^= reg[8] & 0x02;
	}

	else if (size == 11)
	{
		result = reg[10] & 0x10;
		result ^= (reg[10] & 0x08) & (reg[10] & 0x04);
		result ^= reg[8] & 0x10;
	}

	else if (size == 14)
	{
		result = reg[13] & 0x80;
		result ^= (reg[13] & 0x40) & (reg[13] & 0x02);
		result ^= reg[8] & 0x02;
	}

	return result;
}

void feed_func(unsigned char reg[], bool bit)
{
	if(bit)
	reg[0] |= 0x01;

	else
	reg[0] &= 0xFE;
}

bool clock_func()
{
	bool feedbackA = regA[8] & 0x10;
	bool feedbackB = regB[9] & 0x20;
	bool feedbackC = regC[10] & 0x40;

	bool outA = shift_func(regA, 12);
	bool outB = shift_func(regB, 11);
	bool outC = shift_func(regC, 14);

	feed_func(regA, feedbackA ^ outC);
	feed_func(regB, feedbackB ^ outA);
	feed_func(regC, feedbackC ^ outB);

	return outA ^ outB ^ outC;
}

void init_func(unsigned char key[])
{
	int i = 0;

	for (i = 0; i < 10; i++)
	regA[i] = key[i];
	
	for (i = 10; i < 20; i++)
	regB[i - 10] = key[i];

	for (i = 0; i < 14; i++)
	regC[i] = 0;

	regA[10] = 0;
	regA[11] = 0;
	regB[10] = 0;
	regC[13] = 0x07;
}

void warmup_func()
{
	int i = 0;
	for (i = 0; i < 1152; i++)
	clock_func();
}

char encrypt(char input)
{
	char output = 0;
	int i = 0;
	bool bit;

	for (i = 0; i < 8; i++)
	{
		bit = clock_func();
		if (bit)
		output |= (0x80>>i);
	}

	output ^= input;
	return output;
}