/* 
 * File:   Serial.h
 * Author: philippe
 *
 * Created on 25 septembre 2022, 17:33
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <stm8s_conf.h>
#include "stdio.h"

void serial_setup   (uint32_t baudrate);
int  putchar (int c);
int  getchar (void);



#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line);
#endif

#endif /* SERIAL_H */

