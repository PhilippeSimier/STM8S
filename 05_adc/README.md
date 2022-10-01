# STM8 Conversion analogique

## Présentation du convertisseur AN
Les microcontrôleurs de la famille STM8 incluent un convertisseur analogique-numérique qui a jusqu'à 16 entrées multiplexées. 

l'ADC peut être de deux types :
● Un type ADC de base nommé **ADC2**
● Un type ADC étendu nommé **ADC1**

La résolution des deux types de CAN est de **10 bits** (valeur comprise entre 0 et 1023). Le nombre d'entrées analogiques externes dépend de la taille du boîtier de l'appareil de la famille STM8 choisi.

L'ADC est un convertisseur analogique-numérique (**SAR**) à approximations successives. 

La conversion peut être effectuée en mode continu ou en mode unique. Les canaux d'entrée analogiques peuvent être sélectionnés individuellement ou en mode balayage. 

En mode balayage, plusieurs canaux sont convertis en séquence, le numéro de canal est incrémenté à chaque conversion. Le résultat numérique est ensuite stocké dans des registres.

