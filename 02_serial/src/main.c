/**
 * @file    main.c
 * @author  Philippe SIMIER Lycée Touchard Le Mans
 * @date    23 Septembre 2022
 * @brief   Projet liaison série STM8S207 avec platformIO
 *          Principalement pour tester la liaison série avec le câble USB
 */

#include <stm8s_conf.h>
#include <Serial.h>



void main(void) {

    serial_setup(115200);

    printf("\n Serial\n\r retarget the C library printf()/getchar() functions to the UART3\r\n");
    
    float pi=3.1415f;
    
    float teta = 2.0 * pi;
    printf("2 PI = ");
    print_float(teta);
    printf("\r\n");

    
    int32_t i = 32760;

    while (1) {
        i++;
        printf("%3d", (uint16_t)i);
        printf(" Entrer un caractère!\r\n");

        delay_ms(2);

        /* you may also use blocking getchar() to get input */
        char ans = getchar();
        printf("%c", ans);
        printf(" Code Ascii 0x%X\r\n", ans); 
        
    }
}

