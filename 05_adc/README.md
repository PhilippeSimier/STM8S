# STM8 Conversion analogique

## Présentation du convertisseur AN
Les microcontrôleurs de la famille STM8 incluent un convertisseur analogique-numérique qui a jusqu'à 16 entrées multiplexées. 

l'ADC peut être de deux types :

 - type ADC de base nommé **ADC2**
 - type ADC étendu nommé **ADC1**

La résolution des deux types d'ADC est de **10 bits**. La plage de tension de conversion est comprise entre 0 V et 3,3 V. Cela signifie que l'ADC donne **0** lorsque la tension 0 V  est appliquée et donne un maximum de **1023** lorsque 3,3 V est appliquée.

Le nombre d'entrées analogiques externes dépend de la taille du boîtier du microcontrôleur  STM8 choisi. 

L'ADC est un convertisseur analogique-numérique  à approximations successives (**SAR**). 

La conversion peut être effectuée en mode continu ou en mode unique. 

Les canaux d'entrée analogiques peuvent être sélectionnés individuellement ou en mode balayage. 

En mode balayage, plusieurs canaux sont convertis en séquence, le numéro de canal est incrémenté à chaque conversion. Le résultat numérique est ensuite stocké dans des registres.

## programmation
Premièrement activer l'horloge périphérique du module ADC :
```c
CLK_PeripheralClockConfig(CLK_PERIPHERAL_ADC, ENABLE);
```
### Configuration de l' ADC
La conversion ADC peut être déclenchée par un événement Timer1 ou par un front montant sur la broche externe ADC_ETR. La conversion peut également être déclenchée par logiciel avec la fonction ADC2_StartConversion().

 - Conversion continu
 - Sélection du channel 0
 - ADC2 clock prescaler selection
 - Disable Conversion from External interrupt on ADC_ETR pin 
 - ADC2 data alignment à droite
 - Disable Schmitt trigger on Channel 0 
 
```c
    ADC2_DeInit();
    ADC2_Init(ADC2_CONVERSIONMODE_CONTINUOUS,
              ADC2_CHANNEL_0,
              ADC2_PRESSEL_FCPU_D18,
              ADC2_EXTTRIG_GPIO,
              DISABLE,
              ADC2_ALIGN_RIGHT,
              ADC2_SCHMITTTRIG_CHANNEL0,
              DISABLE);

    ADC2_Cmd(ENABLE);
```

Pour la lecture, nous devons démarrer la conversion ADC, puis attendre la fin de la conversion. Comme nous n'utilisons pas de méthodes d'interruption, nous devons donc interroger si la conversion ADC est terminée. À la fin de la conversion, nous pouvons lire l'ADC et effacer l'indicateur ADC de fin de conversion (EOC).

```c
uint16_t ADC2_read() {
    uint16_t A0;
    ADC2_StartConversion();
    while (ADC2_GetFlagStatus() == FALSE);
    A0 = ADC2_GetConversionValue();
    ADC2_ClearFlag();
    return A0;
}
```


