/**
 * @file    main.c
 * @author  Philippe SIMIER Lycée Touchard Le Mans
 * @date    23 Septembre 2022
 * @brief   Projet liaison série STM8S207 avec platformIO
 *          Principalement pour tester la liaison série avec le câble USB
 */

#include <stm8s_conf.h>
#include <Serial.h>
#include <string.h>



void main(void) {

    serial_setup(115200);

    printf("\n Serial\n\r retarget the C library printf()/getchar() functions to the UART3\r\n");
    
    float pi=3.1415f;
    
    float teta = 2.0 * pi;
    printf("2 PI = ");
    printf("%F", teta);
    printf("\r\n");

    
    int8_t i = 0;  // int sur 8 bits
    char buffer[100];
    char ans;
    
    while (1) {
        
        effacer();
        i++;
        printf("loop %d\r\n", i);
       
        delay_ms(2);


        printf("%c", ans);
        printf(" Code Ascii 0x%X\r\n", ans); 
        
        printf("Entrer un message!\r\n");
        gets(buffer,100);
        printf("\r\n%s\r\n", buffer);
        hex_dump(buffer, strlen(buffer)+1);
        printf("Entrer un caractère!\r\n");
        /* you may also use blocking getchar() to get input */
        ans = getchar();
       
    }
}

