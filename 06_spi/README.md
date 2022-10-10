# STM8 Bus SPI

## Introduction
Une liaison **SPI** (pour _**Serial Peripheral Interface**_) est un bus de données série synchrone.

Les circuits communiquent selon le schéma maître-esclave, où le maître contrôle la communication. 

Plusieurs esclaves peuvent coexister sur un même bus, dans ce cas, la sélection du destinataire se fait par une ligne dédiée entre le maître et l'esclave appelée « _Slave Select (SS)

Un bus SPI full-duplex typique nécessite quatre broches d'E/S de base :
![Liaison SPI](/06_spi/single_slave.png)

Lorsque le bus est inutilisé, ce qui revient à dire qu’aucun esclave n’est sélectionné, la ligne **MISO** est à l’état haute impédance, ce qui ne permet pas d’en définir l’état logique. On évite cela par l’utilisation d’une résistance de polarisation, de 47 kOhms.


## Configuration 

Les GPIO doivent être configurés en tant qu'E/S rapides
**Configuration des broches GPIO** 
```c
void GPIO_setup()
 {
    GPIO_DeInit(GPIOC);
    GPIO_Init(GPIOC, ((GPIO_Pin_TypeDef)GPIO_PIN_5 | GPIO_PIN_6),GPIO_MODE_OUT_PP_HIGH_FAST);  //Sorties  PC5 -> CLK et PC6 -> MOSI
    GPIO_Init(CS_port, CS_pin, GPIO_MODE_OUT_PP_HIGH_FAST); // Sortie CS  -> PC4 
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);    // Entrée PC7 -> MISO 
}
``` 
**Passons maintenant à la partie configuration SPI.**

Nous configurons le registre CR1 du port SPI pour qu'il envoie en premier le bit de poids fort (MSB), 
nous  sélectionnons le prescaler d'horloge à 128.

Nous demandons que le SPI agisse comme un maître  et nous avons défini SPI_CLOCKPOLARITY_LOW   SPI_CLOCKPHASE_1EDGE. 

```c
SPI->CR1 = (SPI_FIRSTBIT_MSB | SPI_BAUDRATEPRESCALER_128 | SPI_MODE_MASTER | SPI_CLOCKPOLARITY_LOW | SPI_CLOCKPHASE_1EDGE);
```
Nous configurons le registre CR2 du port SPI  pour obtenir 2 lignes en full duplex
```c
SPI->CR2 = (SPI_DATADIRECTION_2LINES_FULLDUPLEX | SPI_NSS_HARD);
```
Pas d'interruption et enable
```c
	SPI->ICR=0;
    SPI_Cmd(ENABLE);
```
## Ecriture de données sur le bus SPI
```c
void spi_write(unsigned char address, unsigned char value) {
     
    while (SPI_GetFlagStatus(SPI_FLAG_BSY));  //attends que le bus soit pret
    GPIO_WriteLow(CS_port, CS_pin);           //chip select
    
    SPI_SendData(address);                    //envoi l'adresse
    while (!SPI_GetFlagStatus(SPI_FLAG_TXE)); //attends que le registre d'envoi prenne en compte l'octet d'adresse  
    
    SPI_SendData(value);                      //envoi la donnée
    while (!SPI_GetFlagStatus(SPI_FLAG_TXE)); //attends que le registre d'envoi prenne en compte l'octet de donnée
        
    while (SPI_GetFlagStatus(SPI_FLAG_BSY)); //attends que le bus soit libéré
    GPIO_WriteHigh(CS_port, CS_pin); 		 //relache le CS   
}
```


## Chronogrammes 

Il existe donc **4 modes de transmission** différents (voir tableau ci-dessous). Pour une transmission correcte il faut que ces paramètres soient réglés de la même manière pour tous les composants reliés au bus.

|Mode SPI|CPOL|CPHA|
|--|--|--|--|
| **0**  |0  |0 |
| **1**  |0  |1 |
| **2**  |1  |0 |
| **3**  |1  |1 |

 - **CPOL** détermine si au repos l’horloge est au niveau BAS (CPOL=0) ou HAUT (CPOL=1)
 - **CPHA** détermine à quel front de l’horloge les données sont transmises. CPHA=0 les données sont valides au **premier front** d’horloge, CPHA=1 elles sont valides au **deuxième front**.
 
 Par défaut, le mode le plus courant est appelé mode 0, c’est-à-dire celui ou CPOL et CPHA sont tous les deux nuls.

Voici les chronogrammes obtenus pour les différents modes.
**Mode 0** SPI_CLOCKPOLARITY_LOW   SPI_CLOCKPHASE_1EDGE

![Liaison SPI](/06_spi/CLK_LOW_1EDGE.png)

**Mode 1** SPI_CLOCKPOLARITY_LOW   SPI_CLOCKPHASE_2EDGE
![Liaison SPI](/06_spi/CLK_LOW_2EDGE.png)

**Mode 2** SPI_CLOCKPOLARITY_HIGH   SPI_CLOCKPHASE_1EDGE
![Liaison SPI](/06_spi/CLK_HIGH_1EDGE.png)

**Mode 3** SPI_CLOCKPOLARITY_HIGH   SPI_CLOCKPHASE_2EDGE
![Liaison SPI](/06_spi/CLK_HIGH_2EDGE.png)
