# STM8 Timer

## Calcul de la période

Les temporisateurs à l'intérieur des microcontrôleurs STM8 sont des périphériques très utiles et essentiels pour les applications de temporisation.

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


