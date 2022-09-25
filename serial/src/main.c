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

    begin(115200);

    printf("\n UART3  Example :retarget the C library printf()/getchar() functions to the UART3\r\n");

    int i = 0;

    while (1) {
        i++;
        printf("%3d", i);
        printf(" Message de STM8S07!\r\n");

        delay(2);

        /* you may also use blocking getchar() to get input */
        char ans = getchar();
        printf("%c", ans);
        
    }
}