#include "Delay.h"

volatile uint32_t time_keeper = 0;

/* @Brief  : Initialize timer4, run in mode timer basic for delay function
 * @Para   : None
 * @Return : None
 * @Note   : User must be implement function delay_isr() at
 * 		INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23) vector.
 * 		Then call delay_ms() to start delay.
 */
void delay_setup(void) {
    
    TIM4_DeInit();
    TIM4_TimeBaseInit(TIM4_PRESCALER_64, 249); //1ms if fMaster=16Mhz
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);
    TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);

    enableInterrupts();
    TIM4_Cmd(DISABLE);
}



/* @Brief	: Timer 4 Interrupt Service Runtime for Delay function
 * @Para	: None
 * @Return	: None
 * @Note	: User must be implement function delay_isr()
 * 		  at INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23) vector
 */
void delay_isr(void) {

    if (time_keeper != 0) {
        time_keeper--;
    } else {
        /* Disable Timer to reduce power consumption */
        TIM4_Cmd(DISABLE);
    }
    TIM4_ClearITPendingBit(TIM4_IT_UPDATE);

}


/* @Brief   : Delay function
 * @Para    : Time to delay (millis seconds)
 * @Return  : None
 * @Note    : None
 */
void delay_ms(uint32_t time) {

    time_keeper = time;
    TIM4_SetCounter(0);  // Reset Counter Register value
    TIM4_Cmd(ENABLE);    // Enable Timer 
 
    while (time_keeper);
}

