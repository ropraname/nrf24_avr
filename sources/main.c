#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"

#define NRF_CE PB4
#define NRF_CSN PB6
#define nRF_CSN_LOW() PORTB &=~ (1<<NRF_CSN) //Начало обмена
#define nRF_CSN_HIGH() PORTB |= (1<<NRF_CSN) //Завершение обмена
#define nRF_CE_LOW() PORTB &=~ (1<<NRF_CE)
#define nRF_CE_HIGH() PORTB &=~ (1<<NRF_CE)

void nRF_writeReg(unsigned char reg, unsigned char * data, unsigned int count);
void nRF_readReg(unsigned char reg, unsigned char * data, unsigned int count);

unsigned char nRF_data;
unsigned char nRF_txAddr[5] = { 0xD1, 0xD2, 0xD1, 0xD2, 0xD1 };
unsigned char message[] = "It is a first message on NRFdededededede";
unsigned char counter = 0;


int main(void) {
	SPI_MasterInit();

	//Initialize NRF

	//CONFIG
	nRF_data = 0b01011000;
	nRF_writeReg(0x00, &nRF_data, 1);

	//EN_AA
	nRF_data = 0;
	nRF_writeReg(0x01, &nRF_data, 1);

	//RF_CH
	nRF_data = 16;
	nRF_writeReg(0x05, &nRF_data, 1);

	//RF_SETUP
	nRF_data = 0b00100010; //Low power for test -12dbm
	//nRF_data = 0b00100000; //250kbps, 0dBm
	nRF_writeReg(0x06, &nRF_data, 1);

	//TX_ADDR
	nRF_writeReg(0x10, &nRF_txAddr, 5); //Transmit address

	//Lower the flags in STATUS
	SPI_SlaveInit();
	nRF_CSN_LOW();
	nRF_data = SPI_SlaveReceive();
	nRF_CSN_HIGH();
	SPI_MasterInit();
	nRF_writeReg(0x07, &nRF_data, 1);

	while(1){
		//Clear buffer transmit
		nRF_writeReg(0b1110001, 0, 1); //FLUSH_TX
		//Lower the flag TX_DS
		nRF_data = 0b00100000;
		nRF_writeReg(0x07, &nRF_data, 1);

		//Load message into TX_PAYLOAD
		nRF_CSN_LOW();
		SPI_MasterTransmit(0b10100000);
		for(unsigned char i = 0; i < 32; i++){
			SPI_MasterTransmit(message[i]);
		}
		nRF_CSN_HIGH();

		//Transmit mode
		nRF_readReg(0x00, &nRF_data, 1);
		nRF_data |= 0b00000010;
		nRF_writeReg(0x00, &nRF_data, 1);
		_delay_ms(2);

		//Sending a message
		nRF_CE_LOW();
		_delay_us(15);
		nRF_CE_HIGH();
		_delay_us(100);

		//Waiting the sending
		_delay_ms(1500);
		SPI_SlaveInit();
		do {
			nRF_CSN_LOW();
			nRF_data = SPI_SlaveReceive();
			nRF_CSN_HIGH();
			_delay_us(100);

		} while(!(nRF_data & 0b00100000));
		SPI_MasterInit();

		//Lower the flags in STATUS
		SPI_SlaveInit();
		nRF_CSN_LOW();
		nRF_data = SPI_SlaveReceive();
		nRF_CSN_HIGH();
		SPI_MasterInit();
		nRF_writeReg(0x07, &nRF_data, 1);


		_delay_ms(1000);
	}
}


void nRF_writeReg(unsigned char reg, unsigned char * data, unsigned int count)
{
	nRF_CSN_LOW();
	SPI_MasterTransmit(0b00100000 | reg);
	for(unsigned char i = 0; i < count; i++){
		SPI_MasterTransmit(((unsigned char *) data)[i]);
	}
	nRF_CSN_HIGH();
}

void nRF_readReg(unsigned char reg, unsigned char * data, unsigned int count)
{
	nRF_CSN_LOW();
	SPI_MasterTransmit(reg);
	SPI_SlaveInit();
	for(unsigned char i = 0; i < count; i++){
		((unsigned char *) data)[i] = SPI_SlaveReceive();
	}
	nRF_CSN_HIGH();
	SPI_MasterInit();
}
