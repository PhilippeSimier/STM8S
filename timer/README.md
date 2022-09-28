# STM8 Timer

Les temporisateurs du microcontrôleurs STM8S20 sont des périphériques très utiles et essentiels pour les applications de temporisation.
les microcontrôleurs de la famille STM8S20 possédent 4 timers.

 - TIM1 - 16-bit advanced control timer
 - TIM2, TIM3 - 16-bit general purpose timers
 - TIM4 - 8-bit basic timer

![Les timer](/timer/TIM_timer.png)

##  Génération de durée

La génération d'une durée repose sur le comptage d'un nombre requis de périodes élémentaires. 
Ce nombre est fourni au temporisateur avant le démarrage du comptage. Lorsque le contenu du compteur a atteint cette valeur le temporisateur signale que la durée est écoulée.  Lorsque la valeur du compteur dépasse celle du registre de référence, le contenu du compteur est remis à 0.
La fréquence d'un STM8S207 est de 16MHz, avec un compteur de 16 bits cadencé par l'horloge principale, on pourrait compter jusqu'à 65536/16MHz soit une durée maximale de 4ms. Dans de nombreux cas cela est inadapté, on active alors dans le temporisateur un diviseur de fréquence ("prescaler") en entrée qui va permettre de diviser par une puissance de 2 la fréquence du signal entré.  Cette valeur du diviseur est définie dans le registre spécifique (PSCR) du timer.

## Calcul de la période

Le STM8S possède un oscillateur interne avec une fréquence de 16 MHz. Par défaut, il sera utilisé comme source d'horloge système avec le prédiviseur 1, ce qui signifie que la fréquence d'horloge système sera de **16 MHz**. 

Par défaut, le timer 2 fonctionnera avec la même fréquence que le système.
Supposons que nous voulions basculer la LED à chaque seconde et que nous allions utiliser la minuterie 2 pour identifier le moment où 1 seconde s'est écoulée.

Chaque tick de l'horloge système sera 1/16 000 000 = 0,0000000625 seconde ou **0,0625 µs**.

Si nous définissons 2048 comme prédiviseur pour le temporisateur 2, le compteur du temporisateur 2 s'incrémentera toutes les **128 µs** (0,0625 µs x 2048).

Ainsi, 1 seconde se seront écoulé lorsque le compteur du timer atteindra  1 000 000/128 = **7812** .

Le timer 2 a un compteur de 16 bits.

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


