# STM8S

## Introduction
Cet exemple montre comment rediriger les fonctions `printf/getchar` de la bibliothèque C vers l'UART3 . Le programme proposé génère un message avec `printf` sur le terminal à l'aide de l'UART3 et continue d'attendre qu'un caractère soit saisi par l'utilisateur.

L'UART3 est configuré comme suit :

-   BaudRate = 115200 bauds
-   Longueur de mot = 8 bits
-   Un bit d'arrêt
-   Pas de parité
-   Réception et transmission activées

## Liaison Série

La version du STM8S207 dans un boitier  32 broches ne possède qu'un seul uart connecté, l'**UART3**.

![Brochage STM8S207](/02_serial/brochageSTM8S2007.png)

UART3  est connecté  à  **ST-LINK/V2-1** par l'intermédaire des ponts soudés SB3 et SB4. (Solder Bridge). Le flux série sur la liasison USB est disponible sur **ttyACM0** 

Lorsque la communication virtuelle UART de ST-LINK n'est pas utilisée,  il est possible en déplaçant les ponts, de connecter PD5/PD6 qui sont aussi les broches TX et RX de UART3 aux broche D1 et D0 de la carte.











