/*
 test du timer 2 tim2 16 bits
 * 
 */
#include "stm8s.h"
#include "stdio.h"
#include <stdbool.h>
#include <Serial.h>


#define PORTC  GPIOC
#define LED_BUILTIN    GPIO_PIN_5

#define ENABLE true
#define DISABLE false

int state = 0;

void GPIO_setup(void);
void clock_setup(void);
void TIM2_setup(uint16_t nb);


void main(void) {

    clock_setup();
    GPIO_setup();
    TIM2_setup(7812); 

    begin(115200);
  
    printf("\r\nProgramme Exemple Timer 2 \r\n");
    bool flag = false;

   
    //la led s'allume et s'éteint toutes les 0.5 s  7812/2=3906
    while (1) {
        
        //test du timer
        if (TIM2_GetCounter() > 3906) { 
            if (flag == false) {
                GPIO_WriteHigh(PORTC, LED_BUILTIN);
                printf(" Led on !\r\n");
                flag = true;
            }
        } else {
            if (flag == true) {
                GPIO_WriteLow(PORTC, LED_BUILTIN);
                printf(" Led off !\r\n");
                flag = false;
            }
        }
    }
}


/**
 * fonction pour définir la broche PB5 comme sortie.
 * Output push-pull, low level, 10MHz
 */
void GPIO_setup(void) {
    GPIO_Init(PORTC, LED_BUILTIN, GPIO_MODE_OUT_PP_LOW_FAST); 
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
    

    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);   // HSI à 16 MHz
    //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8); // HSI à  2 MHz

    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); // soit CPU à 16Mhz
}



/**
 * @brief Active l'horloge du timer 2
 *      Configure le pré-diviseur, sur 2048
 *      Configure la valeur d'Autoreload
 *      la periode d'une seconde correspond à 7812
 * @param PrescalerValue
 */
void TIM2_setup(uint16_t PrescalerValue) {
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE);
    TIM2_DeInit();    
    TIM2_TimeBaseInit(TIM2_PRESCALER_2048, PrescalerValue); 
    TIM2_Cmd(ENABLE);
}







