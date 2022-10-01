# STM8 Timer PWM

La modulation de largeur d'impulsion (PWM) est une fonctionnalité indispensable de tout microcontrôleur. Le PWM a de nombreuses utilisations comme le contrôle moteur,  le contrôle de l'éclairage. Dans cette section, nous verrons comment utiliser TIM2 pour générer des PWM simples.

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
Ceci est un exemple assez simple. Ici, les trois canaux de TIM2 sont utilisés pour fondre et faire briller en douceur trois LED connectées aux canaux de la minuterie. 

Nous devons d'abord définir la base de temps avant de configurer réellement les canaux PWM.  De plus, nous pouvons définir la polarité PWM et commander le canal si oui ou non il doit se comporter de manière inversée.
```c
/**
 * @brief Active l'horloge du timer 2
 *      Configure le pré-diviseur, sur 32 (500 kHz)
 *      Configure le retour à zero du compteur sur la valeur 1000
 *      la periode d'une seconde correspond à 7812
 */
void TIM2_setup(void) {

    TIM2_DeInit();
    TIM2_TimeBaseInit(TIM2_PRESCALER_32, 1000);
    TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 1000, TIM2_OCPOLARITY_HIGH);
    TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 1000, TIM2_OCPOLARITY_LOW);
    TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 1000, TIM2_OCPOLARITY_HIGH);
    TIM2_Cmd(ENABLE);
}
```
Les broches GPIO doivent être configurées en sortie
```c
void GPIO_setup() {

    GPIO_Init(GPIOC, LED_BUILTIN, GPIO_MODE_OUT_PP_LOW_FAST);        // PC5  Output push-pull, low level, 10MHz
    
    GPIO_Init(GPIOD, GPIO_PWM_TIM2_CH1, GPIO_MODE_OUT_PP_HIGH_FAST); // PD4  Output push-pull, low level, 10MHz
    GPIO_Init(GPIOD, GPIO_PWM_TIM2_CH2, GPIO_MODE_OUT_PP_HIGH_FAST); // PD3  Output push-pull, low level, 10MHz
    GPIO_Init(GPIOA, GPIO_PWM_TIM2_CH3, GPIO_MODE_OUT_PP_HIGH_FAST); // PA3  Output push-pull, low level, 10MHz
}
```

Pour changer le rapport cyclique PWM, nous devons appeler la fonction suivante :
```c 
	TIM2_SetCompare1(pwm_duty);   // pour le canal 1
    TIM2_SetCompare2(pwm_duty);   // pour le canal 2
    TIM2_SetCompare3(pwm_duty);	  // pour le canal 3
```
Notez que dans les micros STM8, il existe un compromis entre le rapport cyclique et la fréquence PWM. Si la résolution PWM, c'est-à-dire le rapport cyclique est grand, alors la fréquence PWM est petite et vice-versa. Ceci est vrai pour toutes les minuteries.
