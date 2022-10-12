#include "spi.h"

void SPI_setup() {

    GPIO_Init(GPIOC, ((GPIO_Pin_TypeDef) GPIO_PIN_5 | GPIO_PIN_6), GPIO_MODE_OUT_PP_HIGH_FAST); //Sorties  PC5 -> CLK et PC6 -> MOSI
    GPIO_Init(CS_port, CS_pin, GPIO_MODE_OUT_PP_HIGH_FAST); // Sortie CS  -> PC4 
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT); // Entrée PC7 -> MISO 

    CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, ENABLE);

    SPI_DeInit();

    SPI->CR1 = (SPI_FIRSTBIT_MSB | SPI_BAUDRATEPRESCALER_64 | SPI_MODE_MASTER | SPI_CLOCKPOLARITY_LOW | SPI_CLOCKPHASE_1EDGE);
    SPI->CR2 = (SPI_DATADIRECTION_2LINES_FULLDUPLEX | SPI_NSS_HARD);

    SPI->ICR = 0;
    SPI_Cmd(ENABLE);

    // printf("SPI-> CR1:%x CR2:%x\n\r",SPI->CR1,SPI->CR2); //vérification des deux registres de config
}

void SPI_write(unsigned char address, unsigned char value) {

    while (SPI_GetFlagStatus(SPI_FLAG_BSY)); //attends que le bus soit pret
    GPIO_WriteLow(CS_port, CS_pin); //chip select

    SPI_SendData(address); //envoi l'adresse
    while (!SPI_GetFlagStatus(SPI_FLAG_TXE)); //attends que le registre d'envoi prenne en compte l'octet d'adresse  

    SPI_SendData(value); //envoi la donnée
    while (!SPI_GetFlagStatus(SPI_FLAG_TXE)); //attends que le registre d'envoi prenne en compte l'octet de donnée

    while (SPI_GetFlagStatus(SPI_FLAG_BSY)); //attends que le bus soit libéré
    GPIO_WriteHigh(CS_port, CS_pin); //relache le CS

}

/**
 * @brief This function  send data over SPI interface
 * @param  Data : data to be sent
 * @param  len : length in bytes of the data to be sent
 * @retval none
 */

void SPI_send(uint8_t *data, uint16_t len) {

    uint16_t tx_len = len;
    int i = 0;

    while (SPI_GetFlagStatus(SPI_FLAG_BSY)); //attends que le bus soit pret
    GPIO_WriteLow(CS_port, CS_pin); //chip select

    while (tx_len > 0) {
        while (!SPI_GetFlagStatus(SPI_FLAG_TXE));
        SPI_SendData(data[i++]);
        tx_len--;
    }

    while (SPI_GetFlagStatus(SPI_FLAG_BSY)); //attends que le bus soit libéré
    GPIO_WriteHigh(CS_port, CS_pin); //relache le CS

}

/**
 * @brief SPI transfer is based on a simultaneous send and receive: the received data is returned in data_rx 
 * @param data
 * @param len
 */
void SPI_transfer(uint8_t *data_tx, uint8_t *data_rx, uint16_t len) {

    uint16_t tx_len = len;
    int i = 0;

    while (tx_len > 0) {
        while (!SPI_GetFlagStatus(SPI_FLAG_TXE));
        SPI_SendData(data_tx[i]);

        while (!SPI_GetFlagStatus(SPI_FLAG_RXNE));
        data_rx[i] = SPI_ReceiveData();

        i++;
        tx_len--;
    }

}

