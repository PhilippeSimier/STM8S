# STM8 Interuptions

## Présentation 
le programme propose une fonction delay basée sur les interruptions. 
Ce programme utilise le timer 4, une minuterie de base qui a un prescaler sélectionnable de 1 à 128 avec un compteur 8 bits. L'objectif est d'obtenir une interruption toute les 1 ms. 

Pour la fréquence  de 16Mhz  il est nécessaire de configurer le prescaler à 128  et  la période à 124.
```c
    TIM4_TimeBaseInit(TIM4_PRESCALER_128, 124) 
```

Veuillez noter que les codes qui utilisent les interruptions périphériques ont besoin des fichiers `stm8s_it.h` et  `stm8s_it.c`. 

le fichier  **_stm8s_it.c_** contient le prototype de la fonction qui exécutera la routine de service d'interruption (ISR).

```c
extern void delay_isr(void);
```
le fichier  **_stm8s_it.c_** contient aussi l'appel de cette fonction dans la macro INTERRUPT_HANDLER. 
```c

/**
 * @brief  Timer4 Update/Overflow Interrupt routine
 * @param None
 * @retval
 * None
 */
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23) {
     delay_isr();
}
```
Ainsi la fonction `delay_isr` est appelée toute les ms.
Elle décrémente une variable globale time_keeper, puis réinitialise l'interruption.
```c
void delay_isr(void) {
    if (TIM4_GetITStatus(TIM4_IT_UPDATE) == SET) {
        if (time_keeper != 0) {
            time_keeper--;
        } else {
            /* Disable Timer to reduce power consumption */
            TIM4->CR1 &= (uint8_t) (~TIM4_CR1_CEN);
        }
        TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
    }
}
```
## La fonction `delay_ms(time)`

La fonction réinitialise la variable time_keeper, remet le compteur du timer à zéro, puis réactive le timer.
enfin elle attend le retour à zéro de la variable time_keeper.

```c
void delay_ms(uint32_t time) {
    
    time_keeper = time;
    TIM4->CNTR = (uint8_t) (0); /* Reset Counter Register value */    
    TIM4->CR1 |= TIM4_CR1_CEN; /* Enable Timer */

    while (time_keeper);
}
```
