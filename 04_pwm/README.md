# STM8 Timer PWM

## Timer 2
Le timer 2 possède trois comparateurs dont les sorties sont associées aux broches GPIO suivantes :

![timer 2](/04_pwm/Timer2.png)
 

##  Génération de signaux PWM

TIM2 compte de 0 à la valeur du registre de rechargement automatique (TIM2_ARR) selon la fréquence des impulsions d'horloge du compteur TIM2.

![pwm_generation](/04_pwm/pwm_generation.png)


 - Lorsque la valeur du compteur est égale à la valeur du registre de comparaison/capture (TIM2_CCRxx), le signal de la voie x est défini sur la valeur 0.
 - Lorsque la valeur du compteur atteint la valeur TIM2_ARR, le compteur
   est réinitialisé et le signal de la voie x est défini sur 1.

En configurant les registres TIM2_CCRxx et TIM2_ARR, on peut  modifier le rapport cyclique et la fréquence des signaux PWM générés.
Le timer peut fournir  3 signaux PWM de rapports cycliques différents.




## Programme
```c
/**
 * @brief Active l'horloge du timer 2
 *      Configure le pré-diviseur, sur 2048
 *      Configure le retour à zero du compteur sur la valeur nb
 *      la periode d'une seconde correspond à 7812
 * @param nb la valeur maxi du compteur
 */
void TIM2_setup(void) {
	CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE);
    TIM2_DeInit();
    TIM2_TimeBaseInit(TIM2_PRESCALER_2048, 7812); 
    TIM2_Cmd(ENABLE);
}
```


