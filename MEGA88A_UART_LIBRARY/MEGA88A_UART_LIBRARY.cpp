/*
 * MEGA88A_UART_LIBRARY.cpp
 *
 * Created: 4/30/2015 2:36:49 PM
 *  Author: Jimmy
 */ 

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)

#include <avr/io.h>

void initUart(){
	
	//Asynchronous Double Speed Mode
	/*
	BAUD = (fosc/(8(UBRR+1)))
	*/
	UCSR0A |= (1 << U2X0);

	/* Turn on the transmission and reception circuitry. */
	/*
	RXCIE: RX Complete Interrupt Enable
	TXCIE: TX Complete Interrupt Enable
	UDRIE: USART Data Register Empty Interrupt Enable
	RXEN: Receiver Enable
	TXEN: Transmitter Enable
	UCSZ2: Character Size
	RXB8: Receive Data Bit 8
	TXB8: Transmit Data Bit 8
	*/
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

	/* BAUD prescale */
	//For use in calculating the baud rate, this is not the actual BAUD rate.
	UBRR0 = 12;	
}

void enableRXInterrupts(){
	UCSR0B |= (1 << RXCIE0);	
}

void setBaudPrescaler(int prescaler){
	/* BAUD prescale */
	//For use in calculating the baud rate, this is not the actual BAUD rate.
	UBRR0 = prescaler;	
}

char readFromUartRXReg(){
	char retChar = UDR0;
	return retChar;
}

void USART_SendByte(uint8_t u8Data) {

	// Wait until last byte has been transmitted
	while((UCSR0A &(1<<UDRE0)) == 0);

	// Transmit data
	UDR0 = u8Data;
}

// not being used but here for completeness
// Wait until a byte has been received and return received data
uint8_t USART_ReceiveByte() {
	while((UCSR0A &(1<<RXC0)) == 0);
	return UDR0;
}

//Turns a hexidecimal character into the actual number it represents
uint8_t hexLetterToNumber(uint8_t c) {
	if(c >= 0x30 && c <= 0x39){
		c-= 0x30;
	}
	else{
		c = (c - 0x41) + 10;
	}
	return c;
}

uint8_t USART_ReceiveHexi() {
	uint8_t upper = hexLetterToNumber(USART_ReceiveByte());
	uint8_t lower = hexLetterToNumber(USART_ReceiveByte());
	upper = upper << 4;
	return upper | lower;
}

void USART_SendHexByte(uint8_t byte) {
	char upper = (byte & 0b11110000 );
	char lower = (byte & 0b00001111 );
	
	upper = ((upper >> 4) & 0b00001111);
	
	if(upper <10) {
		USART_SendByte(upper+'0');
	}
	else {
		USART_SendByte((upper-10) + 'A');
	}
	if(lower <10) {
		USART_SendByte(lower+'0');
	}
	else {
		USART_SendByte((lower-10) + 'A');
	}
}

void USART_sendHexArray(uint8_t *bytes, int length) {
	int i = 0;
	for(i=0;i<length;i++) {
		USART_SendHexByte(bytes[i]);
	}
}

void USART_sendString(const char *str) {
	int i=0;
	while(str[i] != 0x00) {
		USART_SendByte(str[i]);
		i++;
	}
}