# STM8S20

## Introduction
La série STM8S20 de microcontrôleurs 8 bits bénéficie de la technologie 130 nm de ST et d'une architecture de cœur avancée **pouvant atteindre 20 MIPS à 24 MHz** .

![Gamme STM8S20](/gamme_STM8S20.png)

A titre d'exemple, vous trouverez dans ce dépôt, des programmes en langage C pour utiliser le kits d'évaluation **nucleo_8s207k8**.
Cette carte est compatible au niveau des broches avec l'Arduino nano. **Attention cela ne veut pas dire que vous pouvez utiliser le framwork Arduino.**  

Le microcontrôleur possède un ensemble complet de minuteries, interfaces (UART, SPI, I²C), ADC 10 bits, système de contrôle d'horloge interne et externe, chiens de garde, unité de réveil automatique, 64KB de mémoire FLASH et 6KB de mémoire RAM. 

![brochage NUCLEO-8S207K8](/brochage_NUCLEO-8S207K8.png)

Côté gauche
|Pin name| STM8 pin | Function|
|--|--|--|
| D1|  PD5|  UART_TX  |  
| D0|  PD6|  UART_RX |
| RESET | NRST | RESET |
| GND  | - | Ground |
| D2 | PD0 | TIM3_CH2 |
| D3 | PC1 | TIM1_CH1 |
| D4 | PD2 | TIM3_CH1 |
| D5 | PC2 | TIM1_CH2 |
| D6 | PC3 | TIM1_CH3 |
| D7 | PA1 | - |
| D8 | PA2 | - |
| D9 | PC4 | TIM1_CH4 |
| D10 | PE5 / PD4 | SPI_NSS / TIM2_CH1 |
| D11 | PC6 / PD3 | SPI_MOSI / TIM2_CH2 |
| D12 | PC7 | SPI_MISO |

Côté droit
|Pin name| STM8 pin | Function|
|--|--|--|
| VIN |  - | Power input |
| GND | - | Ground |
| RESET | NRST | RESET |
| +5V | - | - |
| A7 | PD7 - PF4 | TLI - Analog input 12 |
| A6 | PF4 - PD7 |  Analog input 12 - TLI |
| A5 | PB4 | Analog input 4 - I2C_SC |
| A4 | PB5 | Analog input 5 - I2C_SDA |
| A3 | PB3 | Analog input 3 |
| A2 | PB2 | Analog input 2 |
| A1 | PB1 | Analog input 1 |
| A0 | PB0 | Analog input 0 |
| AREF | - | VDDA |
| +3V3 | - | 3.3 V I/O |
| D13 | PC5 | SPI clock |

La carte a une sonde de débogage intégrée et **EST PRÊTE** pour le débogage ! Vous n'avez pas besoin d'utiliser/d'acheter une sonde de débogage externe.

## Configuration du projet avec platformIO
Lister les cartes disponibles STM8
```
$ pio boards stm8

Platform: ststm8
=========================================================================================
ID              MCU           Frequency    Flash    RAM    Name
--------------  ------------  -----------  -------  -----  ------------------------------
nucleo_8s207k8  STM8S207K8T6  16MHz        64KB     6KB    NUCLEO-8S207K8
nucleo_8s208rb  STM8S208RBT6  16MHz        128KB    6KB    NUCLEO-8S208RB
stm8sdisco      STM8S105C6T6  16MHz        32KB     2KB    ST STM8S-DISCOVERY
stm8s003f3      STM8S003F3P6  16MHz        8KB      1KB    ST STM8S003F3 chip
stm8sblue       STM8S103F3P6  16MHz        8KB      1KB    ST STM8S103F3 Breakout Board
stm8sblack      STM8S105K4T6  16MHz        16KB     2KB    ST STM8S105K4T6 Breakout Board
mb208           STM8S208MBT6  16MHz        128KB    6KB    sduino MB (STM8S208MBT6B)
s8uno           STM8S105K6T6  16MHz        32KB     2KB    sduino UNO (STM8S105K6)

```

Créer un projet pour l'EDI Netbeans en utilisant la commande suivante:
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
**spl** est la bibliothèque de périphériques standard pour microcontrôleurs ST STM8S/A

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



## Documentation constructeur ST

Documentation carte [nucleo 8s207k8](https://www.st.com/en/evaluation-tools/nucleo-8s207k8.html#documentation)

# Changelog

**17/09/2022 : ** Creation du README.md 

> **Notes :**


> - Licence : **licence publique générale** ![enter image description here](https://img.shields.io/badge/licence-GPL-green.svg)
> - Auteur **Philippe SIMIER** Lycée Touchard Le Mans
>  ![enter image description here](https://img.shields.io/badge/built-passing-green.svg)
<!-- TOOLBOX 
