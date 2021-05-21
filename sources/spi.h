#ifndef SPI_H_
#define SPI_H_

#define SPI_DDR DDRB

#define SPI_SS PB0 // ��������� �� ����������
#define SPI_SCK PB1
#define SPI_MOSI PB2
#define SPI_MISO PB3

void SPI_MasterInit();
void SPI_MasterTransmit(unsigned char cData);
void SPI_SlaveInit();
unsigned char SPI_SlaveReceive();
#endif /* SPI_H_ */
