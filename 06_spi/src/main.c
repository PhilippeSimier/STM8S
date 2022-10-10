/*
 * Test du bus  SPI
 * 
 */
#include <stm8s_conf.h>
#include <Serial.h>
#include <stdbool.h>

#define CS_pin   GPIO_PIN_4
#define CS_port  GPIOC

void GPIO_setup();
void clock_setup();

void SPI_setup();
void spi_write(unsigned char address, unsigned char value);


void main(void) {
    
    uint16_t i = 0;

    clock_setup();
    GPIO_setup();
    
    begin(115200);

    printf("\r\n Programme test SPI\r\n");   
    SPI_setup();
    
    while (1) {
        //test du spi
        spi_write(0xa0, 0x36);
        delay_ms(10);
        printf("\r\n send %d\r\n", i++);
    }
}

void GPIO_setup()
 {
 
    GPIO_DeInit(GPIOA);
    GPIO_DeInit(GPIOB);
    GPIO_DeInit(GPIOC);
    GPIO_DeInit(GPIOD);
    
    GPIO_Init(GPIOC, ((GPIO_Pin_TypeDef)GPIO_PIN_5 | GPIO_PIN_6),GPIO_MODE_OUT_PP_HIGH_FAST);  //Sorties  PC5 -> CLK et PC6 -> MOSI
    GPIO_Init(CS_port, CS_pin, GPIO_MODE_OUT_PP_HIGH_FAST); // Sortie CS  -> PC4 
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);    // Entrée PC7 -> MISO 
}

void clock_setup() 
{ 
      CLK_DeInit(); 
  
      CLK_HSECmd(DISABLE); 
      CLK_LSICmd(DISABLE); 
      CLK_HSICmd(ENABLE); 
      while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == FALSE); 
  
      CLK_ClockSwitchCmd(ENABLE); 
      CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
      CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); //soit 16Mhz
  
 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, ENABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, DISABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, DISABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART3, ENABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, DISABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, DISABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, DISABLE); 
}

void SPI_setup() {
    
    // plantage via la SPL
    
    SPI_DeInit();
    /**
    SPI_Init(SPI_FIRSTBIT_MSB,            envoie d'abord MSB
            SPI_BAUDRATEPRESCALER_64,
            SPI_MODE_MASTER,              SPI fonctionne en mode master
            SPI_CLOCKPOLARITY_LOW,
            SPI_CLOCKPHASE_1EDGE,
            SPI_DATADIRECTION_1LINE_TX,    // Transmit only in 1 line bi-directional data mode 
            SPI_NSS_HARD,                  ou SPI_NSS_SOFT
            0x00);
    printf("->ok2\n");
    SPI_Cmd(ENABLE);
    */
    //donc init manuelle
    SPI->CR1 = (SPI_FIRSTBIT_MSB | SPI_BAUDRATEPRESCALER_128 | SPI_MODE_MASTER | SPI_CLOCKPOLARITY_LOW | SPI_CLOCKPHASE_1EDGE);
    SPI->CR2 = (SPI_DATADIRECTION_2LINES_FULLDUPLEX | SPI_NSS_HARD);
    
    SPI->ICR=0;
    SPI_Cmd(ENABLE);
    
    printf("SPI-> CR1:%x CR2:%x\n\r",SPI->CR1,SPI->CR2); //vérification des deux registres de config
}

void spi_write(unsigned char address, unsigned char value) {
     
    while (SPI_GetFlagStatus(SPI_FLAG_BSY)); //attends que le bus soit pret
    GPIO_WriteLow(CS_port, CS_pin);     //chip select
    
    SPI_SendData(address);              //envoi l'adresse
    while (!SPI_GetFlagStatus(SPI_FLAG_TXE)); //attends que le registre d'envoi prenne en compte l'octet d'adresse  
    
    SPI_SendData(value);                      //envoi la donnée
    while (!SPI_GetFlagStatus(SPI_FLAG_TXE)); //attends que le registre d'envoi prenne en compte l'octet de donnée
        
    while (SPI_GetFlagStatus(SPI_FLAG_BSY)); //attends que le bus soit libéré
    GPIO_WriteHigh(CS_port, CS_pin); //relache le CS
    
}


