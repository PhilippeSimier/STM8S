/* 
 * File:   spi.h
 * Author: Anthony & philippe Lycée Touchard Washington Le Mans
 * @brief  * This library allows you to communicate with SPI devices
 * 
 * To use this library
 * #include <spi.h>
 * 
 * Created on 11 octobre 2022, 10:43
 */

#ifndef SPI_H
#define SPI_H

#define CS_pin   GPIO_PIN_4
#define CS_port  GPIOC

#include <stm8s_conf.h>


void SPI_setup();
void SPI_write(unsigned char address, unsigned char value);
void SPI_send(uint8_t *data, uint16_t len);
void SPI_transfer(uint8_t *data_tx, uint8_t *data_rx, uint16_t len);

#endif /* SPI_H */

