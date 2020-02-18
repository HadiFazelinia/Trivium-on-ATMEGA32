#ifndef UART_H_
#define UART_H_

#ifndef F_CPU
#define F_CPU 8000000UL // 16MHz clock speed
#endif

#include <avr/io.h>

#define  util_GetBitMask(bit)          (1<<(bit))
#define util_IsBitCleared(x,bit)      (((x)&(util_GetBitMask(bit)))==0u)
#define util_ExtractByte0to8(x)    (uint8_t) ((x) & 0xFFu)
#define util_ExtractByte8to16(x)   (uint8_t) (((x)>>8) & 0xFFu)
#define C_MinBaudRate_U32 2400
#define C_MaxBaudRate_U32 115200UL
#define M_GetBaudRateGeneratorValue(baudrate)  (((F_CPU -((baudrate) * 8L)) / ((baudrate) * 16UL)))

void UART_SetBaudRate(uint32_t v_baudRate_u32);
void UART_Init(uint32_t v_baudRate_u32);
char UART_RxChar(void);
void UART_TxChar(char v_uartData_u8);

#endif /* UART_H_ */