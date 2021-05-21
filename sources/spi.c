#include <avr/io.h>
#include "SPI.h"


#define SPI_DDR DDRB

#define SPI_SS PB0 // ��������� �� ����������
#define SPI_SCK PB1
#define SPI_MOSI PB2
#define SPI_MISO PB3


void SPI_MasterInit(void)
{
	/* ��������� MOSI � SCK �� �����, ��� ��������� �� ���� */
	SPI_DDR = (1<<SPI_MOSI)|(1<<SPI_SCK);
	/* ���������� SPI � ������ �������, ��������� �������� ����� fck/16
	*/SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(unsigned char cData)
{
	/* ������ �������� ������ */
	SPDR = cData;
	/* �������� ���������� �������� ������ */
	while(!(SPSR & (1<<SPIF)));
}

void SPI_SlaveInit(void)
{
	/* ��������� MISO �� ����� � ���� ���. �� ���� */
	SPI_DDR = (1<<SPI_MISO);
	/* ���������� SPI */
	SPCR = (1<<SPE);
}
unsigned char SPI_SlaveReceive(void)
{
	/* �������� ���������� �������� */
	while(!(SPSR & (1<<SPIF)));
	/* ������ �������� ������ � ����� �� ��������� */
	return SPDR;
}

