/*
 test du timer 4 avec interruption
 * 
 */
#include "stm8s.h"
#include "stm8s_it.h"
#include "stdio.h"
#include <stdbool.h>
#include <Serial.h>


#define PORTC  GPIOC
#define LED_BUILTIN    GPIO_PIN_5

#define ENABLE true
#define DISABLE false


volatile uint32_t time_keeper=0;


void GPIO_setup(void);
void clock_setup(void);
void delay_using_timer4_init(void);
void delay_isr(void);
void delay_ms(uint32_t time);

void main(void) {

    clock_setup();
    GPIO_setup();
    delay_using_timer4_init();

    int i = 0;

    begin(115200);

    printf("\r\nProgramme Exemple Timer 4 interuption\r\n");

    //la led s'allume et s'éteint toutes les secondes
    while (1) {

        //test du timer
        delay_ms(1000);
        printf("%d\r\n", i++);
        GPIO_WriteReverse(GPIOC, LED_BUILTIN);
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


    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // HSI à 16 MHz
    //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8); // HSI à  2 MHz

    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); // soit CPU à 16Mhz
}

/* @Brief  : 	Initialize timer4, run in mode timer basic for delay function
 * @Para   :	None
 * @Return :	None
 * @Note   :   User must be implement function delay_isr() at
 * 				INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23) vector.
 * 				Then call delay_ms() to start delay.
 */
void delay_using_timer4_init(void) {
    
    TIM4_TimeBaseInit(TIM4_PRESCALER_128, 124); //1ms if fMaster=16Mhz
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);
    TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);

    enableInterrupts();
    TIM4_Cmd(DISABLE);
}

/* @Brief	: 	Timer 4 Interrupt Service Rountie for Delay function
 * @Para	:	None
 * @Return	:	None
 * @Note	:   User must be implement function delay_isr()
 * 				at INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23) vector
 */
void delay_isr(void) {
    if (TIM4_GetITStatus(TIM4_IT_UPDATE) == SET) {
        if (time_keeper != 0) {
            time_keeper--;
        } else {
            /* Disable Timer to reduce power consumption */
            TIM4->CR1 &= (uint8_t) (~TIM4_CR1_CEN);
        }
        TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
    }
}

/* @Brief   : Delay function
 * @Para    : Time to delay (millis seconds)
 * @Return  : None
 * @Note    : None
 */
void delay_ms(uint32_t time) {
    
    time_keeper = time;

    /* Reset Counter Register value */
    TIM4->CNTR = (uint8_t) (0);

    /* Enable Timer */
    TIM4->CR1 |= TIM4_CR1_CEN;

    while (time_keeper);
}

