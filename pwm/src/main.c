/*
 test du timer 2 tim2 16 bits
 * 
 */
#include "stm8s.h"
#include "stm8s_it.h"    /* SDCC patch: required by SDCC for interrupts */
#include "stdio.h"
#include <stdbool.h>
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

#define PORTC  GPIOC
#define PORTD  GPIOD
#define LED_BUILTIN    GPIO_PIN_5
#define GPIO_PWM_TIM2_CH2    GPIO_PIN_3


int state=0;

void GPIO_setup()
 {
    //GPIO_PinRemapConfig();
//    GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE) ; 
    GPIO_DeInit(GPIOA);
    GPIO_DeInit(GPIOB);
    GPIO_DeInit(GPIOD);
    GPIO_Init(PORTC, LED_BUILTIN, GPIO_MODE_OUT_PP_LOW_FAST); // Output push-pull, low level, 10MHz
    GPIO_Init(PORTD, GPIO_PWM_TIM2_CH2 , GPIO_MODE_OUT_PP_HIGH_FAST); // Output push-pull, low level, 10MHz

}



void clock_setup() 
{ 
      CLK_DeInit(); 
  
      CLK_HSECmd(DISABLE); 
      CLK_LSICmd(DISABLE); 
      CLK_HSICmd(ENABLE); 
      while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY) == FALSE); 
  
      CLK_ClockSwitchCmd(ENABLE); 
      //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8); //un peu lent
       
      CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    
      CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1); //soit 16Mhz
  
      //CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI,  
      //DISABLE, CLK_CURRENTCLOCKSTATE_ENABLE); 
  
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_SPI, DISABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, DISABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, DISABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_AWU, DISABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART3, ENABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER1, DISABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE); 
      CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, DISABLE); 
}

/*
 l'horloge qui rentre dans le timer = fmaster = 16Mhz
 préscaler = 32 donc la fréquence d'entrée du timer est 16Mhz/32 soit 500Khz
 la valeur max de comptage est 1000, après le compteur se réinitialse à zéro et recommence.
 donc la fréquence de rechargement est 500 000/1000 = 500hz soit 2ms sur l'oscillo
  */


void TIM2_setup(void) {
    TIM2_DeInit();
    TIM2_TimeBaseInit(TIM2_PRESCALER_32, 1000);
    //TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 1000,TIM2_OCPOLARITY_HIGH);
    TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 1000, TIM2_OCPOLARITY_HIGH);
    //TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 1000,TIM2_OCPOLARITY_HIGH);
    TIM2_Cmd(ENABLE);
}

void main(void) {


    clock_setup();
    GPIO_setup();
    TIM2_setup();


    UART3_DeInit();
    UART3_Init((uint32_t) 115200,
            UART3_WORDLENGTH_8D,
            UART3_STOPBITS_1,
            UART3_PARITY_NO,
            UART3_MODE_TXRX_ENABLE);

    /* Output a message on Hyperterminal using printf function */
    //printf("\n" UART_NAME " Example :retarget the C library printf()/getchar() functions to the UART\r\n");
    int pwm_duty;

    while (1) {
        GPIO_WriteReverse(PORTC, LED_BUILTIN);
        //test du pwm
        for (pwm_duty = 0; pwm_duty < 1000; pwm_duty += 10) {
            TIM2_SetCompare2(pwm_duty);
            // simple wait ~1ms @ 16MHz
            for (uint32_t i = 0; i < 16000L; i++)
            __asm__("nop");
        }

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


