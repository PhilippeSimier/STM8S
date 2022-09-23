# STM8S

## Liaison Série

La version du STM8S2007 dans un boitier  32 broches ne possède qu'un seul uart connecté, l'**UART3**.

UART3  est connecté  à  **ST-LINK/V2-1** par l'intermédaire des ponts soudés SB3 et SB4. (Solder Bridge). Le flux série sur la liasison USB est disponible sur **ttyACM0** 

Lorsque la communication virtuelle UART n'est pas utilisée,  il est possible en déplaçant les ponts, de connecter PD5/PD6 aux broches TX et RX de UART3.

![Brochage STM8S207](/serial/brochageSTM8S2007.png)









