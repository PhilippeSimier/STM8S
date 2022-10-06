/* 
 * File:   main.c
 * Author: philippe SIMIER Lycée touchard Le Mans
 * 
 * Programme pour tester la laison I2C avec une eeprom I2C
 * Atmel 24C256 
 *
 * Created on 26 septembre 2022, 14:55
 */


#include <stm8s_conf.h>
#include <stm8s_i2c.h>
#include <Serial.h>
#include "BH1750.h"

void clock_setup(void);
void GPIO_setup(void);
void I2C_setup(void);

#define   BH1750_addr    0x46

void main(void) {

    unsigned int tmp = 0x0000;

    clock_setup();
    GPIO_setup();
    I2C_setup();

    begin(115200);

    printf("\r\n Programme test I2C\r\n");
    
  
    printf("%d\n", (uint16_t)(CLK_GetClockFreq() / 10000)); // for positive values
    
    BH1750_init();


    while (1) {
        printf("loop");
        tmp = get_lux_value(cont_L_res_mode, 20);
        printf("tmp %d", tmp);
        delay_ms(1000);
    }

}

void clock_setup(void) {

    CLK_DeInit();

    CLK_HSECmd(DISABLE);
    CLK_LSICmd(DISABLE);
    CLK_HSICmd(ENABLE);
    while (CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == FALSE);


    CLK_ClockSwitchCmd(ENABLE);
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // HSI à 16 MHz
    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); // soit CPU à 16Mhz

    CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI,
            DISABLE, CLK_CURRENTCLOCKSTATE_ENABLE);

    CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, ENABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, DISABLE);
}

//define SDA, SCL outputs, HiZ, Open drain, Fast
void GPIO_setup(void) {
    GPIO_DeInit(GPIOB);
   
   GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_OUT_OD_HIZ_FAST);
   GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_OD_HIZ_FAST);
   GPIO_WriteHigh(GPIOB, GPIO_PIN_4);
   GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
}

void I2C_setup(void) {
/**
    I2C_SoftwareResetCmd(ENABLE);
    I2C_SoftwareResetCmd(DISABLE);
    I2C_Cmd(DISABLE);
    I2C_DeInit();
    I2C_Cmd(ENABLE);
    I2C_Init(I2C_MAX_STANDARD_FREQ,
            0x00,
            I2C_DUTYCYCLE_2,
            I2C_ACK_CURR,
            I2C_ADDMODE_7BIT,
            20
            );
    I2C_AcknowledgeConfig(I2C_ACK_CURR);
 */
 
  I2C->FREQR = 8;                // input clock to I2C - 8MHz
  I2C->CCRL = 40;                // CCR= 40 - (SCLhi must be at least 4000+1000=5000ns!)
  I2C->CCRH = 0;                 // standard mode, duty 1/1 bus speed 100kHz
  I2C->TRISER = 9;               // 1000ns/(125ns) + 1  (maximum 1000ns)
  I2C->OARL = 0xA0;              // own address A0;
  I2C->OARH |= 0x40;
  I2C->ITR = 1;                  // enable error interrupts
  I2C->CR2 |= 0x04;              // ACK=1, Ack enable
  I2C->CR1 |= 0x01;              // PE=1 
    
    
    
}






