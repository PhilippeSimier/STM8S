/**
 * @file    main.c
 * @author  Philippe SIMIER Lycée Touchard Le Mans
 * @date    13 Septembre 2022
 * @brief   Projet de clignotement simple sans interruptions
 *          Principalement pour tester la chaîne d'outils
 */

#include <stm8s_conf.h>

#define PORTC  GPIOC
#define LED_BUILTIN    GPIO_PIN_5
#define LED_ROUGE      GPIO_PIN_7

// Prototypes
void Delay(uint16_t nCount);

void main() {

    // Setup  Initialize broches PC5 & PC7 
    GPIO_Init(PORTC, LED_BUILTIN, GPIO_MODE_OUT_PP_LOW_FAST); // Output push-pull, low level, 10MHz
    GPIO_Init(PORTC, LED_ROUGE,   GPIO_MODE_OUT_PP_LOW_SLOW); // Output push-pull, low level, 2MHz
    
    // Loop 
    while (1) {

        GPIO_WriteHigh(PORTC, LED_BUILTIN);
        GPIO_WriteLow(PORTC,  LED_ROUGE);
        Delay(2);
        GPIO_WriteLow(PORTC,  LED_BUILTIN);
        GPIO_WriteHigh(PORTC, LED_ROUGE);
        Delay(10);
    }
}

void Delay(uint16_t nCount) {
    uint16_t n = 0xFFFF;
    while (nCount) {
        n = 0xFFFF;
        while (n) {
            n--;
        }
        nCount--;
    }
}

/**
 * @brief  Reports the name of the source file and the source line number
 *   where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */

void assert_failed(uint8_t* file, uint32_t line) {

    (void) file;
    (void) line;
    // Infinite loop 
    while (1) {
    }
}


