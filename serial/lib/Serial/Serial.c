#include "Serial.h"

/**
 * @brief initialise l'uart3 
 * @param baudrate Le taux de transmission
 */
void begin(uint32_t baudrate) {

    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

    UART3_DeInit();
    UART3_Init(baudrate,
            UART3_WORDLENGTH_8D,
            UART3_STOPBITS_1,
            UART3_PARITY_NO,
            UART3_MODE_TXRX_ENABLE);
}

/**
 * @brief Retargets the C library printf function to the UART3.
 * @param c Character to send
 * @retval char Character sent
 */
int putchar(int c) {
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
int getchar(void) {
    int c = 0;

    /* Loop until the Read data register flag is SET */
    while (UART3_GetFlagStatus(UART3_FLAG_RXNE) == RESET); /* wait until data arrived */
    c = UART3_ReceiveData8();
    return (c);
}


/* @Brief  :   Delay function
 * @Param  :   Time to delay (millis seconds)
 * @Return :   None
 * @Note   :   None
 */
void delay_ms(uint32_t nb) {

    for (uint32_t i = 0; i < nb; i++) {
        // simple wait ~1ms @ 16MHz
        for (uint32_t j = 0; j < 1600L; j++)
            __asm__("nop");
    }
}


/**
 * 
 * @param data decimal value
 * @return data hexa value
 */
uint8_t Bcd_2_Dec(uint8_t data)
{
	return (data>>4)*10+(data&0x0f);
}


/**
 * @brief  Reports the name of the source file and the source line number
 *   where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
#ifdef USE_FULL_ASSERT
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

