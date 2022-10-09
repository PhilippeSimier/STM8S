/* 
 * File:   BH1750.h
 * Author: philippe
 *
 * Created on 4 octobre 2022, 22:15
 */

#ifndef BH1750_H
#define BH1750_H

#include "stm8s_conf.h"
#include <Serial.h>
 
#define   BH1750_addr                             0x46
         
#define  power_down                               0x00
#define  power_up                                 0x01
#define  reset                                    0x07 
#define  cont_H_res_mode1                         0x10 
#define  cont_H_res_mode2                         0x11  
#define  cont_L_res_mode                          0x13    
#define  one_time_H_res_mode1                     0x20 
#define  one_time_H_res_mode2                     0x21
#define  one_time_L_res_mode                      0x23                       
 
void BH1750_init(void);
void BH1750_write(unsigned char cmd);      
unsigned int BH1750_read_word(void);
unsigned int get_lux_value(unsigned char mode, unsigned int delay_time);

#endif