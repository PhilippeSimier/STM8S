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
void TIM2_setup(void);


void main(void) {

    clock_setup();
    GPIO_setup();
    TIM2_setup();

    begin(115200);
  
    printf("\r\nProgramme Exemple Timer 2 \r\n");
    bool flag = false;

   
    //la led s'allume et s'éteint toutes les 125ms  1952/2=976
    while (1) {
        
        //test du timer
        if (TIM2_GetCounter() > 976) { 
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



void GPIO_setup(void) {

//    GPIO_DeInit(GPIOA);
//    GPIO_DeInit(GPIOB);
//    GPIO_DeInit(GPIOD);
    GPIO_Init(PORTC, LED_BUILTIN, GPIO_MODE_OUT_PP_LOW_FAST); // Output push-pull, low level, 10MHz
}


void clock_setup(void) {
    CLK_DeInit();

    CLK_HSECmd(DISABLE);
    CLK_LSICmd(DISABLE);
    CLK_HSICmd(ENABLE);
    while (CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == false);

    CLK_ClockSwitchCmd(ENABLE);
    

    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8); //un peu lent

    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); //soit 16Mhz

    //CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI,  
    //DISABLE, CLK_CURRENTCLOCKSTATE_ENABLE); 

    CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART3, ENABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, DISABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE);
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, DISABLE);
}


/*
 l'horloge qui rentre dans le timer = fmaster = 16Mhz
 préscaler = 2048 donc la fréquence d'entrée du timer est 16Mhz/2048 soit 7812,5Hz
 la valeur max de comptage est 1952, après le compteur se réinitialse à zéro et recommence.
 donc la fréquence de rechargement est 7812,5/1952=4,002305328 HZ
 soit une période de 1/4=250ms
 
 */
void TIM2_setup(void) {
    TIM2_DeInit();
    TIM2_TimeBaseInit(TIM2_PRESCALER_2048, 1952); //soit 16Mhz/2048=
    TIM2_Cmd(ENABLE);
}







