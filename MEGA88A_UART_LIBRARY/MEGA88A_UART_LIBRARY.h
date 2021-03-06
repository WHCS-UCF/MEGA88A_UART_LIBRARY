/*
 * MEGA88A_UART_LIBRARY.h
 *
 * Created: 4/30/2015 2:41:37 PM
 *  Author: Jimmy
 */ 


#ifndef MEGA88A_UART_LIBRARY_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#pragma message("UART Library did not find CPU speed set, setting to default.")
#endif

#define USART_BAUDRATE 9600

#ifdef DOUBLE_SPEED_MODE_ENABLE
#define SPEED_MODE_DIV 8UL
#else
#define SPEED_MODE_DIV 16UL
#endif

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * SPEED_MODE_DIV))) - 1)

#define MEGA88A_UART_LIBRARY_H_


void initUart();

void enableRXInterrupts();

void setBaudPrescaler(int prescaler);

char readFromUartRXReg();

void USART_SendByte(uint8_t u8Data);

uint8_t USART_ReceiveByte();

//Turns a hexidecimal character into the actual number it represents
uint8_t hexLetterToNumber(uint8_t c);

//This is a blocking call.
//Waits for two bytes in hexadecimal fomrat to come in through the UART and
//Returns the byte represented by the hexadecimal received.
//Example:
//"EA" received through UART,
//The function returns 0x11101010
uint8_t USART_ReceiveHexi();

void USART_SendHexByte(uint8_t byte);

void USART_sendHexArray(uint8_t *bytes, int length);

void USART_sendString(const char *str);

#endif /* MEGA88A_UART_LIBRARY_H_ */