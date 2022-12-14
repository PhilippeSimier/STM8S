/**
 * @file    main.c
 * @author  Philippe SIMIER Lycée Touchard Le Mans
 * @date    29 Septembre 2022
 * @brief   Projet pour tester le fonctionnement du timer2
 */

#include "stm8s.h"
#include "stdio.h"
#include <stdbool.h>
#include <Serial.h>


#define ENABLE true
#define DISABLE false


#define LED_BUILTIN          GPIO_PIN_5
#define GPIO_PWM_TIM2_CH1    GPIO_PIN_4    // PD4
#define GPIO_PWM_TIM2_CH2    GPIO_PIN_3    // PD3
#define GPIO_PWM_TIM2_CH3    GPIO_PIN_3    // PA3

void GPIO_setup();
void clock_setup();
void TIM2_setup(void);

void main(void) {


    clock_setup();
    GPIO_setup();
    TIM2_setup();

    begin(115200);
    printf("Programme PWM Timer2\r\n");

    

    while (1) {
        GPIO_WriteReverse(GPIOC, LED_BUILTIN);

        //test pwm sur sortie PD3
        for (int pwm_duty = 0; pwm_duty < 1000; pwm_duty += 5) {
            TIM2_SetCompare1(pwm_duty);
            TIM2_SetCompare2(pwm_duty);
            TIM2_SetCompare3(pwm_duty);
            delay_ms(10);
        }
    }
}

/**
 * @brief Initialise la led Builtin et les trois sorties du timer2
 */
void GPIO_setup() {

    GPIO_Init(GPIOC, LED_BUILTIN, GPIO_MODE_OUT_PP_LOW_FAST);        // PC5  Output push-pull, low level, 10MHz
    
    GPIO_Init(GPIOD, GPIO_PWM_TIM2_CH1, GPIO_MODE_OUT_PP_HIGH_FAST); // PD4  Output push-pull, low level, 10MHz
    GPIO_Init(GPIOD, GPIO_PWM_TIM2_CH2, GPIO_MODE_OUT_PP_HIGH_FAST); // PD3  Output push-pull, low level, 10MHz
    GPIO_Init(GPIOA, GPIO_PWM_TIM2_CH3, GPIO_MODE_OUT_PP_HIGH_FAST); // PA3  Output push-pull, low level, 10MHz
}


void clock_setup() {

    CLK_DeInit();
    CLK_HSECmd(DISABLE);
    CLK_LSICmd(DISABLE);
    CLK_HSICmd(ENABLE);

    while (CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == false);

    CLK_ClockSwitchCmd(ENABLE);
    //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8); //un peu lent

    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); //soit 16Mhz
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE);

}

/*
 l'horloge qui rentre dans le timer = fmaster = 16Mhz
 préscaler = 32 donc la fréquence d'entrée du timer est 16Mhz/32 soit 500Khz
 la valeur max de comptage est 1000, après le compteur se réinitialse à zéro et recommence.
 donc la fréquence de rechargement est 500 000/1000 = 500hz soit 2ms sur l'oscillo
 */


void TIM2_setup(void) {

    TIM2_DeInit();
    TIM2_TimeBaseInit(TIM2_PRESCALER_32, 1000);
    
    TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 1000, TIM2_OCPOLARITY_LOW);
    TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 1000, TIM2_OCPOLARITY_HIGH);
    TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 1000, TIM2_OCPOLARITY_HIGH);

    TIM2_Cmd(ENABLE);
}