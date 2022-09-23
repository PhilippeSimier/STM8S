
#include "stm8s.h"
#include "stm8s_it.h"    /* SDCC patch: required by SDCC for interrupts */
#include "stdio.h"
/**
 * @addtogroup UART1_Printf
 * @{
 */
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#ifdef _RAISONANCE_
#define PUTCHAR_PROTOTYPE int putchar (char c)
#define GETCHAR_PROTOTYPE int getchar (void)
#elif defined (_COSMIC_)
#define PUTCHAR_PROTOTYPE char putchar (char c)
#define GETCHAR_PROTOTYPE char getchar (void)
#elif defined (_SDCC_)         /* SDCC patch: ensure same types as stdio.h */
#if SDCC_VERSION >= 30605      // declaration changed in sdcc 3.6.5 (officially with 3.7.0)
#define PUTCHAR_PROTOTYPE int putchar(int c)
#define GETCHAR_PROTOTYPE int getchar(void)
#else
#define PUTCHAR_PROTOTYPE void putchar(char c)
#define GETCHAR_PROTOTYPE char getchar(void)
#endif 
#else /* _IAR_ */
#define PUTCHAR_PROTOTYPE int putchar (int c)
#define GETCHAR_PROTOTYPE int getchar (void)
#endif /* _RAISONANCE_ */
/* Private macro -------------------------------------------------------------*/
/* Some chips have UART1, but other chips only have UART2 and not UART1. 
 * We want this example to work on both types of chips, so we 
 * macro-define all the correct SPL functions to the default UART of the device. 
 * 
 * UART3 devices: STM8S207
 * 
 */

#define UART_NAME "UART 3"

#define UART_SENDDATA8 UART3_SendData8
#define UART_RECEIVEDATA8 UART3_ReceiveData8
#define UART_GETFLAGSTATUS UART3_GetFlagStatus
#define UART_FLAG_RXNE UART3_FLAG_RXNE
#define UART_FLAG_TXE UART3_FLAG_TXE


void main(void) {
    
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

    UART3_DeInit();
    UART3_Init((uint32_t) 115200, 
            UART3_WORDLENGTH_8D,
            UART3_STOPBITS_1, 
            UART3_PARITY_NO,
            UART3_MODE_TXRX_ENABLE);

    /* Output a message on Hyperterminal using printf function */
    printf("\n" UART_NAME " Example :retarget the C library printf()/getchar() functions to the UART\r\n");
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
 * @brief Retargets the C library printf function to the UART.
 * @param c Character to send
 * @retval char Character sent
 */
PUTCHAR_PROTOTYPE
{
    /* Write a character to the UART1 */
    UART_SENDDATA8(c);
    /* Loop until the end of transmission */
    while (UART_GETFLAGSTATUS(UART_FLAG_TXE) == RESET);

    return (c);}

/**
 * @brief Retargets the C library scanf function to the USART.
 * @param None
 * @retval char Character to Read
 */
GETCHAR_PROTOTYPE
{
#ifdef _COSMIC_
    char c = 0;
#else
    int c = 0;
#endif
    /* Loop until the Read data register flag is SET */
    while (UART_GETFLAGSTATUS(UART_FLAG_TXE) == RESET);
    c = UART_RECEIVEDATA8();
    return (c);}

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


