# STM8 Interuptions

## Présentation 
Dans notre projet initial **01_blink_led**, nous avons utilisé une simple boucle de retard. Cela a l'avantage d'être rapide à mettre en place mais cela présente quelques inconvénients.

-   Le code est sensible au temps, si nous effectuons d'autres tâches, la LED clignotera à des rythmes différents.
-   On ne peut rien faire d'autre en attendant.

Ce projet propose une fonction delay basée sur les interruptions. 
Le programme utilise le timer 4, une minuterie de base qui a un prescaler sélectionnable de 1 à 128 avec un compteur 8 bits. L'objectif est d'obtenir une interruption toute les 1 ms. 

## Configuration du timer
Pour la fréquence  de 16Mhz  il est nécessaire de configurer le prescaler à 128  et  la période à 124.
```c
    TIM4_TimeBaseInit(TIM4_PRESCALER_128, 124) 
```
Nous configurons aussi le temporisateur pour générer une interruption à chaque fois que le temporisateur est rechargé.
```c
    TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
    enableInterrupts();
```
Notez l'appel à `enableInterrupts` qui active les interruptions dans le CPU, sans elle notre interruption ne se produira pas.
Veuillez noter que les codes qui utilisent les interruptions périphériques ont besoin des fichiers `stm8s_it.h` et  `stm8s_it.c`. 

le fichier  **_stm8s_it.c_** contient le prototype de la fonction qui exécutera la routine de service d'interruption (ISR).

```c
extern void delay_isr(void);
```
le fichier  **_stm8s_it.c_** contient aussi  la configuration  du vecteur d'interruption. le temporisateur 4 est sur l'irq 23.
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
Ainsi configuré, la fonction `delay_isr` est appelée toute les ms pour décrémenter la variable `time_keeper`.

Lorsque time_keeper est revenu à zéro, le temporisateur  est désactivé pour économiser la consommation.
```c
void delay_isr(void) {
    if (TIM4_GetITStatus(TIM4_IT_UPDATE) == SET) {
        if (time_keeper != 0) {
            time_keeper--;
        } else {
            /* Disable Timer to reduce power consumption */
            TIM4_Cmd(DISABLE);
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
    TIM4_SetCounter(0);  // Reset Counter Register value
    TIM4_Cmd(ENABLE);    // Enable Timer
    while (time_keeper);
}
```
