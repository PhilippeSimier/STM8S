/**
 * @file    main.c
 * @author  Philippe SIMIER Lycée Touchard Le Mans
 * @date    23 Septembre 2022
 * @brief   Projet liaison série STM8S207 avec platformIO
 *          Principalement pour tester la liaison série avec le câble USB
 */

#include <stm8s_conf.h>
#include "stdio.h"


void main(void) {
    
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

    UART3_DeInit();
    UART3_Init((uint32_t) 115200, 
                UART3_WORDLENGTH_8D,
                UART3_STOPBITS_1, 
                UART3_PARITY_NO,
                UART3_MODE_TXRX_ENABLE);

    /* Output a message on Hyperterminal using printf function */
    printf("\n UART3  Example :retarget the C library printf()/getchar() functions to the UART3\r\n");
    
    int i = 0;
    
    while (1) {
        i++;
        printf("%3d", i);
        printf(" Message de STM8S07!\r\n");

        // simple wait ~1000ms @ 16MHz
        for (uint32_t i = 0; i < 1600000L; i++)
            __asm__("nop");

        /* you may also use blocking getchar() to get input */
        char ans = getchar();
        printf("%c", ans);
    }
}



/**
 * @brief Retargets the C library printf function to the UART3.
 * @param c Character to send
 * @retval char Character sent
 */
int putchar (int c)
{
    /* Write a character to the UART3 */
    UART3_SendData8(c);
    /* Loop until the end of transmission */
    while (UART3_GetFlagStatus(UART3_FLAG_TXE) == RESET);

    return (c);
}


/**
 * @brief Retargets the C library scanf function to the USART3.
 * @param None
 * @retval char Character to Read
 */
int getchar (void)
{
    int c = 0;

    /* Loop until the Read data register flag is SET */
    while (UART3_GetFlagStatus(UART3_FLAG_RXNE) == RESET); /* wait until data arrived */
    c = UART3_ReceiveData8();
    return (c);
}





#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *   where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line) {
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    (void) file;
    (void) line;
    /* Infinite loop */
    while (1) {
    }
}
#endif


