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
    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);       // soit CPU à 16Mhz

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

void GPIO_setup(void) {
    GPIO_DeInit(GPIOB);
    GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_OUT_OD_HIZ_FAST);
    GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_OD_HIZ_FAST);
    GPIO_WriteHigh(GPIOB, GPIO_PIN_4);
    GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
}

void I2C_setup(void) {
    I2C_DeInit();
    I2C_Init(10000,
            BH1750_addr,
            I2C_DUTYCYCLE_2,
            I2C_ACK_CURR,
            I2C_ADDMODE_7BIT,
            16);
    
    I2C_Cmd(ENABLE);
}






