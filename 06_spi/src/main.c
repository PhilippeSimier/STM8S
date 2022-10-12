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


void GPIO_setup();
void clock_setup();
void printBuffer(uint8_t *data, uint16_t len);

void main(void) {

    uint16_t i = 0;

    uint8_t data_tx[10] = {0x81, 0x83, 0x87, 0x8f, 0x9f, 0xbf, 0xef, 0x81, 0x83, 0x87};
    uint8_t data_rx[10];
    
    clock_setup();
    GPIO_setup();

    serial_setup(115200);
    delay_ms(10);

    printf("\r\n Programme test SPI\r\n");
    SPI_setup();

    while (1) {
        
        //SPI_write(0xa0, 0x36);
        delay_ms(10);
        SPI_transfer(data_tx, data_rx, 10);
        printf("\r\n send %d\r\n", i++);
        printBuffer(data_rx, 10);
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

void printBuffer(uint8_t *data, uint16_t len){
    uint8_t i;
    for (i = 0; i < len; i++){
        printf("%x ", data[i]);
    }
    printf("\r\n");
}




