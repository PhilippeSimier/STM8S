/**
 * @file    main.c
 * @author  Philippe SIMIER Lycée Touchard Le Mans
 * @date    30 Septembre 2022
 * @brief   Projet pour tester le fonctionnement du convertisseur ADC
 */

#include "stm8s.h"
#include <Serial.h>

#define LED_BUILTIN    GPIO_PIN_5

void GPIO_setup();
void clock_setup();

void ADC2_setup();
uint16_t ADC2_read();



void main(void) {

    clock_setup();
    GPIO_setup();
    ADC2_setup();

    begin(115200);
    printf("Programme test ADC\r\n");

    while (1) {
              
        GPIO_WriteReverse(GPIOC, LED_BUILTIN);
        printf("adc A0=%hu\n\r", ADC2_read());  // uint16_t -> %hu   Lecture et affichage de l'entrée analogique
        delay_ms(1000);

    }
}

void GPIO_setup() {
    GPIO_DeInit(GPIOA);
    GPIO_DeInit(GPIOB);
    GPIO_DeInit(GPIOD);
    GPIO_Init(GPIOC, LED_BUILTIN, GPIO_MODE_OUT_PP_LOW_FAST); // Output push-pull, low level, 10MHz
}

void clock_setup() {
    CLK_DeInit();

    CLK_HSECmd(DISABLE);
    CLK_LSICmd(DISABLE);
    CLK_HSICmd(ENABLE);
    while (CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == FALSE);

    CLK_ClockSwitchCmd(ENABLE);

    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);


    CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, 
                          CLK_SOURCE_HSI,
                          DISABLE, 
                          CLK_CURRENTCLOCKSTATE_ENABLE);

    CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE);   
}

void ADC2_setup() {
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, ENABLE);
    
    ADC2_DeInit();
    ADC2_Init(ADC2_CONVERSIONMODE_CONTINUOUS,
              ADC2_CHANNEL_0,
              ADC2_PRESSEL_FCPU_D18,
              ADC2_EXTTRIG_GPIO,
              DISABLE,
              ADC2_ALIGN_RIGHT,
              ADC2_SCHMITTTRIG_CHANNEL0,
              DISABLE);

    ADC2_Cmd(ENABLE);
}


uint16_t ADC2_read() {
    uint16_t A0;
    ADC2_StartConversion();
    while (ADC2_GetFlagStatus() == FALSE);
    A0 = ADC2_GetConversionValue();
    ADC2_ClearFlag();
    return A0;
}





