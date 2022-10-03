/*
 test du timer 4 avec interruption
 * 
 */
#include "stm8s.h"
#include "stm8s_it.h"
#include "stdio.h"
#include <stdbool.h>
#include <Serial.h>
#include <Delay.h>

#define ENABLE true
#define DISABLE false


void GPIO_setup(void);
void clock_setup(void);


void main(void) {

    clock_setup();
    GPIO_setup();
    delay_setup();

    int i = 0;

    begin(115200);

    printf("\r\nProgramme Exemple Timer 4 interuption\r\n");

    //la led s'allume et s'éteint toutes les secondes
    while (1) {

        //test du timer
        delay_ms(1000);
        printf("%d\r\n", i++);
        GPIO_WriteReverse(GPIOC, GPIO_PIN_5);
    }
}

/**
 * fonction pour définir la broche PC5 comme sortie.
 * Output push-pull, low level, 10MHz
 */
void GPIO_setup(void) {
    GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
}

/**
 * Fonction pour configurer l'oscillateur interne (16Mhz)
 */
void clock_setup(void) {
    CLK_DeInit();

    CLK_HSECmd(DISABLE);
    CLK_LSICmd(DISABLE);
    CLK_HSICmd(ENABLE);
    while (CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == false);

    CLK_ClockSwitchCmd(ENABLE);


    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // HSI à 16 MHz
    //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8); // HSI à  2 MHz

    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); // soit CPU à 16Mhz
}






