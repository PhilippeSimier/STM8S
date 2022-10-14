#include "Serial.h"

/**
 * @brief initialise l'uart3 
 * @param baudrate Le taux de transmission
 */
void serial_setup(uint32_t baudrate) {

    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8);

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

/* @Brief  :   Delay function
 * @Param  :   Time to delay (micro seconds)
 * @Return :   None
 * @Note   :   None
 */
void delay_us(uint32_t nb) {

    for (uint32_t i = 0; i < nb; i++) {
        // simple wait ~1us @ 16MHz  //pas sur à la louche
            __asm__("nop");
    }
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

    printf("assert_failed file %s", file);
    printf("assert_failed line %d", line);
    while (1) {
    }
}
#endif

/**
 * Affiche l'adresse du pointeur
 * et la zone mémoire utilisée
 * @param ptr
 */
void printAddress(void *ptr){
    
    uint8_t *_ptr = (uint8_t*) ptr;
    
    if (_ptr >=  0x8000 && _ptr < 0xFFFF ){
        printf("In Flash programm : ");
    }
    
    if (_ptr <= 0x17ff){
        printf("In RAM : ");
    }
    printf(" 0x%06X\r\n", _ptr);
}
/**
 * 
 * @param data un pointeur générique sur le premier octet à afficher
 * @param len la taille en octets de la zone mémoire 
 */
void hex_dump(void *data, int len) {
    
    uint8_t *p = (uint8_t*) data;
    int n, i, offset;

    offset = 0;
    while (len > 0) {
        n = len < 16 ? len : 16;
        printf("  %03x: ", offset);
        for (i = 0; i < n; i++) {
            printf(" %02x", p[i]);
        }
        for (i = n; i < 16; i++) {
            printf("   ");
        }
        printf("  ");
        for (i = 0; i < n; i++) {
            printf("%c", isprint(p[i]) ? p[i] : '.');
        }
        printf("\n\r");
        p += 16;
        offset += 16;
        len -= 16;
    }
}

void effacer(){
    printf("\x1b[H\x1b[2J");
}