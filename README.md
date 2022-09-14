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

## Compilation
`Processing nucleo_8s207k8 (platform: ststm8; board: nucleo_8s207k8; framework: spl)

Verbose mode can be enabled via `-v, --verbose` option
CONFIGURATION: https://docs.platformio.org/page/boards/ststm8/nucleo_8s207k8.html
PLATFORM: ST STM8 (2.1.0) > NUCLEO-8S207K8
HARDWARE: STM8S207K8T6 16MHz, 6KB RAM, 64KB Flash
DEBUG: Current (stlink) On-board (stlink)
PACKAGES: 
 - framework-ststm8spl @ 0.20301.181217 (2.3.1) 
 - tool-openocd @ 2.1000.200630 (10.0) 
 - tool-stm8binutils @ 0.230.0 (2.30) 
 - tool-stm8flash @ 1.1.20170616 
 - tool-stm8gal @ 1.5.0 
 - toolchain-sdcc @ 1.40100.12072 (4.1.0)
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 0 compatible libraries
Scanning dependencies...
No dependencies
Building in release mode
Checking size .pio/build/nucleo_8s207k8/firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [          ]   0.0% (used 0 bytes from 6144 bytes)
Flash: [          ]   0.9% (used 582 bytes from 65536 bytes)
Configuring upload protocol...
AVAILABLE: serial, stlinkv21
CURRENT: upload_protocol = stlinkv21
Uploading .pio/build/nucleo_8s207k8/firmware.hex
Determine FLASH area
Due to its file extension (or lack thereof), ".pio/build/nucleo_8s207k8/firmware.hex" is considered as INTEL HEX format!
582 bytes at 0x8000... OK
Bytes written: 582
================================================================== [SUCCESS] Took 1.09 seconds ==================================================================

RUN FINISHED; exit value 0; real time: 1s; user: 120ms; system: 700ms
``

```


## Documentation officielle

Documentation carte [nucleo 8s207k8](https://www.st.com/en/evaluation-tools/nucleo-8s207k8.html#documentation)


