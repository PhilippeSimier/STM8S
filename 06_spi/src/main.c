/*
 * Test du bus  SPI
 * 
 */
#include <stm8s_conf.h>
#include <Serial.h>
#include <spi.h>
#include <stdbool.h>


void GPIO_setup();
void clock_setup();

void main(void) {

    uint16_t i = 0;

    uint8_t data_tx[10] = {0x81, 0x83, 0x87, 0x8f, 0x9f, 0xbf, 0xef, 0x81, 0x83, 0x87};
    uint8_t data_rx[10];
    
    clock_setup();
    GPIO_setup();

    serial_setup(115200);

    printf("\r\n Programme test SPI\r\n");
    SPI_setup();

    while (1) {
        //test du spi
        SPI_write(0xa0, 0x36);
        delay_ms(10);
        SPI_transfer(data_tx, data_rx, 10);
        printf("\r\n send %d\r\n", i++);
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




