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

## printf
Dans de nombreux projets nous avons besoin d'afficher le contenu d'une variable. Les ressources du STM8 sont très limitées et ses limitations ont des conséquences.

### Afficher un entier
```c
printf("valeur entière : %d\r\n", 32767);
printf("valeur entière : %d\r\n", 32768);
printf("valeur entière : %d\r\n", (uint32_t)1);
```
Sur le terminal :
La première ligne  affiche  `valeur entière : 32767`
La seconde ligne affiche  `valeur entière : 0`
La troisième ligne affiche  `valeur entière : 0`
Conclusion la fonction `printf` est limité aux entiers stockés sur 16 bits. 

### Afficher un float
```c
	float f = 12.345f;
    printf("valeur  : %f\r\n", f);
```
Affiche sur le terminal
`valeur  : <NO FLOAT>`
`printf` n'affiche pas les `float`

Une solution convertir la variable de type `float` en `int` puis afficher la valeur entière et la partie fractionnaire.
```c
    float f = 12.345f;
    int i = (int) (f * 1000.0f);
    printf("%d.%03d\n", i / 1000, i % 1000); // for positive values
```

### Afficher plusieurs champs
```c
	int a = 23;
    printf("%s %d %s\r\n", "Valeur : ", a, "°C");
```
Affiche sur le terminal :

    Valeur :  23 °C




