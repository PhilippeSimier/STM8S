/* 
 * File:   Delay.h
 * Author: philippe SIMIER Lycée Touchard Le Mans
 *
 * Created on 3 octobre 2022, 22:14
 */

#ifndef DELAY_H
#define DELAY_H

#include <stm8s_conf.h>
#include "stm8s_it.h"
#include <stdbool.h>

#define ENABLE true
#define DISABLE false



void delay_setup(void);
void delay_isr(void);
void delay_ms(uint32_t time);

#endif /* DELAY_H */

