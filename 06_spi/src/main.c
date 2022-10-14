/* 
 * File:   main.h
 * Author: Anthony Le CREN & philippe SIMIER 
 *         Lycée Touchard Washington Le Mans
 * @brief  spi library allows you to communicate with SPI devices
 * 
 * program to test the library spi
 *  
 * Created on 11 octobre 2022, 10:43
 */

#include <stm8s_conf.h>
#include <Serial.h>
#include <spi.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


void GPIO_setup();
void clock_setup();


void main(void) {

    uint16_t i = 0;

    const char* messageTX = "Touchard Section SNIR Programme Test Bus SPI"; // Stored in flash program memory
    char messageRX[100]; // Stored in Ram memory

    clock_setup();
    GPIO_setup();

    serial_setup(115200);
    delay_ms(10);

    printf("\r\n Programme test SPI\r\n");
    SPI_setup();

    while (1) {

        delay_ms(250);
        SPI_transfer(messageTX, messageRX, strlen(messageTX) + 1);
        
        effacer();
        printf("\r\nSend n° %u\r\n", i++); 
        
        printf("Buffer TX\r\n");
        hex_dump(messageTX, strlen(messageTX) + 1);
        
        printf("Buffer RX\r\n");
        hex_dump(messageRX, strlen(messageRX) + 1);

    }
}

void GPIO_setup() {

    GPIO_DeInit(GPIOA);
    GPIO_DeInit(GPIOB);
    GPIO_DeInit(GPIOC);
    GPIO_DeInit(GPIOD);
}

void clock_setup() {
    CLK_DeInit();

    CLK_HSECmd(DISABLE);
    CLK_LSICmd(DISABLE);
    CLK_HSICmd(ENABLE);
    while (CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == FALSE);

    CLK_ClockSwitchCmd(ENABLE);
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); //soit 16Mhz

}









