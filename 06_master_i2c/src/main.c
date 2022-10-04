/* 
 * File:   main.c
 * Author: philippe SIMIER Lycée touchard Le Mans
 * 
 * Programme pour tester la laison I2C avec une eeprom I2C
 * Atmel 24C256 
 *
 * Created on 26 septembre 2022, 14:55
 */


#include <stm8s_conf.h>
#include <Serial.h>

typedef enum {
    I2C_MEMORY_ADDRESS_SIZE_8BIT = 0x00,
    I2C_MEMORY_ADDRESS_SIZE_16BIT = 0x01
} i2c_memory_address_size;



#define I2C_PORT  (GPIOB)
#define SDA_pin   (GPIO_PIN_5)
#define SCL_pin   (GPIO_PIN_4)

#define AT24C256_ADD  0x50


void i2c_master_init(void);
uint8_t i2c_mem_read_arr(uint16_t device_address, uint16_t mem_address_start,
        i2c_memory_address_size I2C_MEMORY_ADDRESS_SIZE_X,
        uint8_t* data_array,
        uint16_t NumByteToRead);

uint8_t receive_data[200];

void main(void) {
    
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
    

    begin(115200);
    i2c_master_init();

    printf("\r\n Programme test I2C");
    printf("\r\n%u\r\n", CLK_GetClockFreq());
    uint8_t ret;

    while (1) {
        delay_ms(1000);
        ret = i2c_mem_read_arr(AT24C256_ADD << 1, 0x00, I2C_MEMORY_ADDRESS_SIZE_8BIT, receive_data, 7);
        printf("\r\nret : %d", ret);
    }

}

/* @Brief	:   Initialize I2C Module of MCU STM8S, mode master (100Khz)
 * @Para	:   None
 * @Return	:   None
 * @Note	:   SDA,SCL Pin see in the datasheet
 */
void i2c_master_init(void) {

    I2C_DeInit();

    CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, ENABLE); /* I2C Peripheral clock enable */



    //define SDA, SCL outputs, HiZ, Open drain, Fast
    GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_OUT_OD_HIZ_FAST); //SCL
    GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_OD_HIZ_FAST); //SDA

    
    /* I2C configuration after enabling it */
    I2C_Init(50000, // SCL 100 Khz
            0xA0, // OwnAddress, egal
            I2C_DUTYCYCLE_2,
            I2C_ACK_CURR,
            I2C_ADDMODE_7BIT,
            16 // InputClockFreqencyMhz
            );
    I2C_Cmd(ENABLE); /* Enable I2C Module */

}

uint8_t i2c_mem_read_arr(uint16_t device_address, uint16_t mem_address_start, i2c_memory_address_size I2C_MEMORY_ADDRESS_SIZE_X, uint8_t* data_array, uint16_t NumByteToRead) {

    uint16_t time_out = 50;

    /* If I2C bus is busy wait until it is free */

    while (I2C_GetFlagStatus(I2C_FLAG_BUSBUSY)&& (--time_out));
    if (!time_out) return 22;

    /* Send Start Condition then wait event EV5 */
    I2C_GenerateSTART(ENABLE);
    while ((!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT))&& (--time_out));
    if (!time_out) return 2;

    /* Send device address to write data then wait event EV6 */
    I2C_Send7bitAddress(device_address, I2C_DIRECTION_TX);
    while ((!I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))&& (--time_out));
    if (!time_out) return 3;

    /* Send memory address pointer then wait event EV8_2 */

    switch (I2C_MEMORY_ADDRESS_SIZE_X) {
        case I2C_MEMORY_ADDRESS_SIZE_8BIT:
            I2C_SendData((uint8_t) mem_address_start);
            break;
        case I2C_MEMORY_ADDRESS_SIZE_16BIT:

            //Send MSB
            I2C_SendData((uint8_t) (mem_address_start >> 8));
            while ((!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))&& (--time_out));
            if (!time_out) return 4;

            //Send LSB
            I2C_SendData((uint8_t) (mem_address_start & 0x00ff));
            break;
    }

    while ((!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))&& (--time_out));
    if (!time_out) return 5;

    /* Send Repeat Start Condition then wait event EV5 */
    I2C_GenerateSTART(ENABLE);
    while ((!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT))&& (--time_out));
    if (!time_out) return 6;

    /* Send device address to read data then wait event EV6 */
    I2C_Send7bitAddress(device_address, I2C_DIRECTION_RX);
    while ((!I2C_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))&& (--time_out));
    if (!time_out) return 7;

    if (NumByteToRead == 1) {
        /* Disable Acknowledgement */
        I2C_AcknowledgeConfig(I2C_ACK_NONE);

        /* Send STOP Condition */
        I2C_GenerateSTOP(ENABLE);

        /* Poll on RxNE Flag */
        while ((I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == RESET) && (--time_out));
        if (!time_out) return 8;

        /* Read a byte from the Slave */
        *data_array = I2C_ReceiveData();
    } else if (NumByteToRead == 2) {
        disableInterrupts();

        /* Poll on RxNE Flag */
        while ((I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == RESET)&& (--time_out));
        if (!time_out) return 9;

        *data_array = I2C_ReceiveData();

        data_array++;

        /* Disable Acknowledgement */
        I2C_AcknowledgeConfig(I2C_ACK_NONE);

        /* Send STOP Condition */
        I2C_GenerateSTOP(ENABLE);

        /* Poll on RxNE Flag */
        while ((I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == RESET)&& (--time_out));
        if (!time_out) return 10;

        enableInterrupts();
        /* Read a byte from the Slave */
        *data_array = I2C_ReceiveData();
    } else {
        while (NumByteToRead) {
            if (NumByteToRead != 3) /* Receive bytes from first byte until byte N-3 */ {
                while ((I2C_GetFlagStatus(I2C_FLAG_TRANSFERFINISHED) == RESET)&& (--time_out));
                if (!time_out) return 11;

                /* Read a byte from the Slave */
                *data_array = I2C_ReceiveData();

                /* Point to the next location where the byte read will be saved */
                data_array++;

                /* Decrement the read bytes counter */
                NumByteToRead--;
            }
            if (NumByteToRead == 3) /* it remains to read three data: data N-2, data N-1, Data N */ {
                /* Data N-2 in DR and data N -1 in shift register */

                /* Poll on BTF */
                while ((I2C_GetFlagStatus(I2C_FLAG_TRANSFERFINISHED) == RESET)&& (--time_out));
                if (!time_out) return 12;

                /* Clear ACK */
                I2C_AcknowledgeConfig(I2C_ACK_NONE);

                /* Disable general interrupts */
                disableInterrupts();

                /* Read Data N-2 */
                *data_array = I2C_ReceiveData();

                /* Point to the next location where the byte read will be saved */
                data_array++;

                /* Program the STOP */
                I2C_GenerateSTOP(ENABLE);

                /* Read DataN-1 */
                *data_array = I2C_ReceiveData();

                /* Enable General interrupts */
                enableInterrupts();

                /* Point to the next location where the byte read will be saved */
                data_array++;

                while ((I2C_GetFlagStatus(I2C_FLAG_RXNOTEMPTY) == RESET)&& (--time_out)); /* Poll on RxNE */
                if (!time_out) return 13;

                /* Read DataN */
                *data_array = I2C_ReceiveData();

                /* Reset the number of bytes to be read by master */
                NumByteToRead = 0;
            }
        }
    }
    I2C_AcknowledgeConfig(I2C_ACK_CURR);
    return 0;
}





