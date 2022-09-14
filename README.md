# STM8

## Introduction
Vous trouverez des programmes en C à titre d'exemple  pour utiliser la carte STM8S207.
La carte est compatible au niveau des broches avec l' arduino nano. **Attention cela ne veut pas dire que vous pouvez utiliser le framwork Arduino.** 

La carte posséde un bus SPI, un bus I2C, 6 entrées analogiques, une liaison série et des broches GPIO.

## Configuration de platformIO

Créer un projet pour l'EDI netbeans en utilisant la commande suivante:
```bash
	pio project init --ide netbeans --board nucleo_8s207k8
```
Le fichier `plateformio.ini` est créé et contient les lignes suivantes
```ini
[env:nucleo_8s207k8]
platform = ststm8
board = nucleo_8s207k8
framework = spl
``` 
## Programmation

La carte se programme en langage C. A ma connaissance le langage C++ n'est pas supporté.
Le programme doit impérativement contenir la définition d'une fonction `assert_failed` afin de gérer les erreurs irrécupérables. 
```c
void assert_failed(uint8_t* file, uint32_t line) {
     // Infinite loop 
    while (1) {
    }
}
```
Le programme principale
```c
void main() {

    /* Setup  Initialize GPIO */
    GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef) LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);

    /* Loop */
    while (1) {

        GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef) LED_GPIO_PINS); // Toggles Led builtin
        Delay(0xFFFF);
    }
}
```

## Documentation officielle

Documentation carte [nucleo 8s207k8](https://www.st.com/en/evaluation-tools/nucleo-8s207k8.html#documentation)


