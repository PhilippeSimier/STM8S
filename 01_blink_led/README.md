# STM8S20 GPIO

## Configuration 

## Programmation

La carte se programme en langage C. *(A ma connaissance le langage C++ n'est pas supporté).*
Le programme doit impérativement contenir la définition d'une fonction `assert_failed` afin de gérer les assertions. 
```c
void assert_failed(uint8_t* file, uint32_t line) {
    (void) file;
    (void) line;
    // Infinite loop 
    while (1) {
    }
}
```
### Le programme principale 

Dans le setup, initialisation des broches  PC5 et PC7 en sortie push pull
Dans la loop, écriture  des valeurs logiques avec les GPIO_WriteHigh et GPIO_WriteLow.
```c
#include <stm8s_conf.h>
#define PORTC  GPIOC
#define LED_BUILTIN    GPIO_PIN_5
#define LED_ROUGE      GPIO_PIN_7

void main() {
    // Setup  Initialize broches PC5 & PC7 
    GPIO_Init(PORTC, LED_BUILTIN, GPIO_MODE_OUT_PP_LOW_FAST); // Output push-pull, low level, 10MHz
    GPIO_Init(PORTC, LED_ROUGE,   GPIO_MODE_OUT_PP_LOW_SLOW); // Output push-pull, low level, 2MHz
 
    // Loop 
    while (1) {
        GPIO_WriteHigh(PORTC, LED_BUILTIN);
        GPIO_WriteLow(PORTC,  LED_ROUGE);
        Delay(2);
        GPIO_WriteLow(PORTC,  LED_BUILTIN);
        GPIO_WriteHigh(PORTC, LED_ROUGE);
        Delay(10);
    }
}
```
### La fonction Delay
Le delay d'attente consiste simplement à tourner dans des boucles imbriquées. 
```c
void Delay(uint16_t nCount) {
    uint16_t n = 0xFFFF;
    while (nCount) {
        n = 0xFFFF;
        while (n) {
            n--;
        }
        nCount--;
    }
}
```
## Compilation

La commande suivante compile le programme et le télécharge sur la cible 

```bash
pio run --target upload
```
Résultat de la compilation :
```
Processing nucleo_8s207k8 (platform: ststm8; board: nucleo_8s207k8; framework: spl)

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

```


## Documentation constructeur ST

Documentation carte [nucleo 8s207k8](https://www.st.com/en/evaluation-tools/nucleo-8s207k8.html#documentation)

# Changelog

**17/09/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 
