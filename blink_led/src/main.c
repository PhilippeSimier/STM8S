/**
 * @file    main.c
 * @author  Philippe SIMIER Lycée Touchard Le Mans
 * @date    13 Septembre 2022
 * @brief   Blink led builtin.
 */


#include <stm8s.h>

#define LED_GPIO_PORT  (GPIOC)
#define LED_GPIO_PINS  (GPIO_PIN_5)

// Prototypes
void Delay(uint16_t nCount);

void main() {

    /* Setup  Initialize GPIO */
    GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef) LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);

    /* Loop */
    while (1) {

        GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef) LED_GPIO_PINS); // Toggles Led builtin
        Delay(0xFFFF);

    }

}

void Delay(uint16_t nCount) {
    while (nCount != 0) {
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
    

    // Infinite loop 
    while (1) {
    }
}


