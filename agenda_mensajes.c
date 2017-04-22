//
//  agenda_mensajes.c
//  Agenda
//
//  Created by Manuel Castro, Raquel Balboa y Xoan Cosmed.
//

#include "agenda_mensajes.h"


int Salir (int modif) // Subprograma / función de salida
{
    int salir = -2;
    char resp; // Respuesta
    
    if (modif == 0) // Si no se ha modificado se permite salir sin confirmación
    {
        salir = 1;
    }
    else if (modif == 1) // Si se ha modificado se pide confirmación
    {
        do
        {
            printf("\n1) Guardar cambios\n");
            printf("2) Descartar cambios\n");
            printf("3) Cancelar\n");
            printf("¿Opción? ");
            scanf(" %c", &resp);
            
            if (resp == '1') // Si la respuesta es 1 se devuelve 0 (guardar y salir)
            {
                salir = 0;
            }
            else if (resp == '2') // Si la respuesta es 2 se devuelve 1 (salir)
            {
                salir = 1;
            }
            else if (resp == '0') // Si se tecleó 0, se devuelve -1 (no salir)
            {
                salir = -1;
            }
            else // Si no se tecleó ninguna de las anteriores se vuelve a preguntar
            {
                salir = -2;
            }
            
        } while (salir == -2);
    }
    else
    {
        printf("\tE: Problemas para detectar salida!\t"); // Mensaje en caso de error
    }
    
    return salir;
}


void aster (int num, char sim) // Imprime "num" símbolos ("sin")
{
    int i; // Declaro un contador
    
    for (i = 0; i<=num; i++) // Escribo un asterisco hasta que llegue al numero solicitado (num)
    {
        printf("%c", sim);
    }
}


int asterMensj (char sim, char mensj[], int tam) // Imprime un mensaje rodeado de "sim"
{
    const int tam_max = 100; // Tamaño máximo permitido
    int tam_mensj = (int)strlen(mensj); // Tamaño del mensaje
    int i;
    
    if (tam > tam_max)
    {
        return -1; // Error
    }
    
    tam = tam - tam_mensj - 10; // Tamaño total menos el del mensaje y 10 para espacios
    
    for (i = 0; i*2 < tam; i++) // Poner el "sim"
    {
        printf("%c", sim);
    }
    
    printf("     %s     ", mensj); // Imprimir mensaje enviado
    
    for (i = 0; i*2 < tam; i++) // Poner el "sim"
    {
        printf("%c", sim);
    }
    
    return 0;
}