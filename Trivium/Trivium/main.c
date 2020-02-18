#ifndef F_CPU
#define F_CPU 8000000UL // 16MHz clock speed
#endif

#include <avr/io.h>
#include "uart.h"
#include "trivium.h"

void print_str(char* input)
{
	int i = 0, l = strlen(input);
	for (i = 0; i < l; i++)
		UART_TxChar(input[i]);
}

unsigned char key[20] = "We did it. :) And we";

int main(void)
{
	UART_Init(9600);

	//Initialization
	init_func(key);

	//Warm-up Phase
	warmup_func();

	//Encryption Phase
	char plain_character, cipher_character;
    while (1) 
    {
		plain_character = UART_RxChar();
		cipher_character = encrypt(plain_character);
		UART_TxChar(cipher_character);
    }
}

