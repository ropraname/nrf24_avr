#include <avr/io.h>
#include "SPI.h"


#define SPI_DDR DDRB

#define SPI_SS PB0 // ФИЗИЧЕСКИ НЕ ПОДКЛЮЧАЕМ
#define SPI_SCK PB1
#define SPI_MOSI PB2
#define SPI_MISO PB3


void SPI_MasterInit(void)
{
	/* Установка MOSI и SCK на вывод, все остальные на ввод */
	SPI_DDR = (1<<SPI_MOSI)|(1<<SPI_SCK);
	/* Разрешение SPI в режиме мастера, установка скорости связи fck/16
	*/SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(unsigned char cData)
{
	/* Запуск передачи данных */
	SPDR = cData;
	/* Ожидание завершения передачи данных */
	while(!(SPSR & (1<<SPIF)));
}

void SPI_SlaveInit(void)
{
	/* Установка MISO на вывод и всех ост. на ввод */
	SPI_DDR = (1<<SPI_MISO);
	/* Разрешение SPI */
	SPCR = (1<<SPE);
}
unsigned char SPI_SlaveReceive(void)
{
	/* Ожидание завершения передачи */
	while(!(SPSR & (1<<SPIF)));
	/* Чтение принятых данных и выход из процедуры */
	return SPDR;
}

