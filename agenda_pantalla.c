//
//  agenda_pantalla.c
//  Agenda 2
//
//  Created by Xoán Carlos Cosmed Peralejo.
//

#include "agenda_pantalla.h"

void printNegro (const char mensj[]) // ESCRIBE EN NEGRO
{
    printf("\033[30m%s\033[0m", mensj);
}

void printRojo (const char mensj[]) // ESCRIBE EN ROJO
{
    printf ("\033[31m%s\033[0m", mensj);
}

void printVerde (const char mensj[]) // ESCRIBE EN VERDE
{
    printf ("\033[32m%s\033[0m", mensj);
}
void printAmarillo (const char mensj[]) // ESCRIBE EN AMARILLO
{
    printf ("\033[33m%s\033[0m", mensj);
}

void printAzul (const char mensj[]) // ESCRIBE EN AZUL
{
    printf ("\033[34m%s\033[0m", mensj);
}

void printMagenta (const char mensj[]) // ESCRIBE EN MAGENTA
{
    printf ("\033[35m%s\033[0m", mensj);
}

void printCian (const char mensj[]) // ESCRIBE EN CIAN
{
    printf ("\033[36m%s\033[0m", mensj);
}

void printBlanco (const char mensj[]) // ESCRIBE EN BLANCO
{
    printf ("\033[37m%s\033[0m", mensj);
}

void printNegritaNegro (const char mensj[]) // ESCRIBE EN NEGRO Y NEGRITA
{
    printf("\033[1m\033[30m%s\033[0m", mensj);
}

void printNegritaRojo (const char mensj[]) // ESCRIBE EN ROJO Y NEGRITA
{
    printf ("\033[1m\033[31m%s\033[0m", mensj);
}

void printNegritaVerde (const char mensj[]) // ESCRIBE EN VERDE Y NEGRITA
{
    printf ("\033[1m\033[32m%s\033[0m", mensj);
}
void printNegritaAmarillo (const char mensj[]) // ESCRIBE EN AMARILLO Y NEGRITA
{
    printf ("\033[1m\033[33m%s\033[0m", mensj);
}

void printNegritaAzul (const char mensj[]) // ESCRIBE EN AZUL Y NEGRITA
{
    printf ("\033[1m\033[34m%s\033[0m", mensj);
}

void printNegritaMagenta (const char mensj[]) // ESCRIBE EN MAGENTA Y NEGRITA
{
    printf ("\033[1m\033[35m%s\033[0m", mensj);
}

void printNegritaCian (const char mensj[]) // ESCRIBE EN CIAN Y NEGRITA
{
    printf ("\033[1m\033[36m%s\033[0m", mensj);
}

void printNegritaBlanco (const char mensj[]) // ESCRIBE EN BLANCO Y NEGRITA
{
    printf ("\033[1m\033[37m%s\033[0m", mensj);
}

void printSubrayadoNegro (const char mensj[]) // ESCRIBE EN NEGRO Y SUBRAYADO
{
    printf("\033[4m\033[30m%s\033[0m", mensj);
}

void printSubrayadoRojo (const char mensj[]) // ESCRIBE EN ROJO Y SUBRAYADO
{
    printf ("\033[4m\033[31m%s\033[0m", mensj);
}

void printSubrayadoVerde (const char mensj[]) // ESCRIBE EN VERDE Y SUBRAYADO
{
    printf ("\033[4m\033[32m%s\033[0m", mensj);
}
void printSubrayadoAmarillo (const char mensj[]) // ESCRIBE EN AMARILLO Y SUBRAYADO
{
    printf ("\033[4m\033[33m%s\033[0m", mensj);
}

void printSubrayadoAzul (const char mensj[]) // ESCRIBE EN AZUL Y SUBRAYADO
{
    printf ("\033[4m\033[34m%s\033[0m", mensj);
}

void printSubrayadoMagenta (const char mensj[]) // ESCRIBE EN MAGENTA  Y SUBRAYADO
{
    printf ("\033[4m\033[35m%s\033[0m", mensj);
}

void printSubrayadoCian (const char mensj[]) // ESCRIBE EN CIAN Y SUBRAYADO
{
    printf ("\033[4m\033[36m%s\033[0m", mensj);
}

void printSubrayadoBlanco (const char mensj[]) // ESCRIBE EN BLANCO Y SUBRAYADO
{
    printf ("\033[4m\033[37m%s\033[0m", mensj);
}

void errorMess (const char mensj[]) // IMPRIME MENSAJE DE ERROR
{
    printf("\n\n\tE: \"%s\"\n\n", mensj);
}

void sound (const char mensj[]) // EMITE UN SONIDO DE ERROR
{
    printf("\a%s", mensj);
}

void clearScreen () // LIMPIA LA PANTALLA
{
    system("clear");
}