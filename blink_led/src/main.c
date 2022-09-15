/**
 * @file    main.c
 * @author  Philippe SIMIER Lycée Touchard Le Mans
 * @date    13 Septembre 2022
 * @brief   Blink led builtin.
 */

#include <stm8s_conf.h>

#define LED_GPIO_PORT  GPIOC
#define LED_GPIO_PIN   (GPIO_Pin_TypeDef)GPIO_PIN_5

// Prototypes
void Delay(uint16_t nCount);

void main() {

    /* Setup  Initialize GPIO */
    GPIO_Init(LED_GPIO_PORT,  LED_GPIO_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
 
    /* Loop */
    while (1) {

        GPIO_WriteHigh(LED_GPIO_PORT,  LED_GPIO_PIN);
        Delay(2);
        GPIO_WriteLow(LED_GPIO_PORT,   LED_GPIO_PIN);
        Delay(10);
    }
}

void Delay(uint16_t nCount) {
    uint16_t n = 0xFFFF;
    while (nCount) {
        n = 0xFFFF;
        while (n){
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
    
    uint32_t l = line;
    uint8_t* f = file;
    // Infinite loop 
    while (1) {
    }
}


