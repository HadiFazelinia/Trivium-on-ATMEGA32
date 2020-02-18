#ifndef TRIVIUM_H_
#define TRIVIUM_H_

#include <stdbool.h>
#include <string.h>

unsigned char regA[12]; //93,96
unsigned char regB[11]; //84,88
unsigned char regC[14]; //111,112

bool shift_func(unsigned char reg[], int size);
void feed_func(unsigned char reg[], bool bit);
bool clock_func();
void init_func(unsigned char key[]);
void warmup_func();
char encrypt(char input);

#endif /* TRIVIUM_H_ */