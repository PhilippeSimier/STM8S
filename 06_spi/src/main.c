/* 
 * File:   spi.h
 * Author: Anthony & philippe Lycée Touchard Washington Le Mans
 * @brief  * This library allows you to communicate with SPI devices
 * 
 * To test the library spi
 *  * 
 * Created on 11 octobre 2022, 10:43
 */

#include <stm8s_conf.h>
#include <Serial.h>
#include <spi.h>
#include <stdbool.h>
#include <string.h>

void GPIO_setup();
void clock_setup();
void printBuffer(void *data, uint16_t len);
void printAddress(void *ptr);

void main(void) {

    uint16_t i = 0;

    char messageTX[100] = "TSM8S";
    char messageRX[100];

    clock_setup();
    GPIO_setup();

    serial_setup(115200);
    delay_ms(10);

    printf("\r\n Programme test SPI\r\n");
    printf("len : %d", strlen(messageTX));
    SPI_setup();

    while (1) {

        delay_ms(5);
        SPI_transfer(messageTX, messageRX, strlen(messageTX) + 1);
        printf("\r\n send n° %d\r\n", i++);
        printBuffer(messageRX, strlen(messageRX) + 1);
        
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

void printBuffer(void *data, uint16_t len) {

    uint8_t i;
    uint8_t *buffer = (uint8_t*) data;
    
    
    
    printAddress(data);

    for (i = 0; i < len; i++) {
        if (buffer[i] < 16) {
            printf("0%x ", buffer[i]);
        } else {
            printf("%x ", buffer[i]);
        }
        if (!((i+1) % 16)){
                printf("\r\n");
            }

        }
    printf("\r\n");
    for (i = 0; i < len; i++) {
        printf("%c", buffer[i]);
    }

    printf("\r\n");
}

void printAddress(void *ptr){
    
    uint8_t *_ptr = (uint8_t*) ptr;
    
    if (_ptr < 0x17ff){
        printf("In RAM : ", _ptr);
    }
    printf(" 0x%06X\r\n", _ptr);
}




