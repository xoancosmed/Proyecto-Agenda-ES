//
//  agenda.c
//  Agenda
//
//  Created by Manuel Castro, Raquel Balboa y Xoan Cosmed.
//




  //////////////////
 ///* INCLUDES *///
//////////////////


#include <stdio.h> // Se incluye la librería básica de Input y Output
#include <stdlib.h> // Se incluye la librería standar de C
#include <string.h> // Se incluye la librería básica de Strings


#include "agenda_pantalla.h" // Se incluye la librería con las funciones de la pantalla
#include "agenda_mensajes.h" // Se incluye la librería con los mensajes de bienvendia y salida
#include "agenda_archivos.h" // Se incluye la librería para procesar los archivos

#include "agenda_tareas_crear.h" // Se incluye las librerías con las funciones de la agenda
#include "agenda_tareas_ver.h"
#include "agenda_tareas_lista.h"





  /////////////////
 ///* DEFINES *///
/////////////////


#define CREAR 1 // Constantes
#define VER 2
#define LISTA 3
#define SALIR 0




  ///////////////////
 ///* VARIABLES *///
///////////////////


int tareas_num; // Contador de tareas

struct tareaS {
    
    int id; // Identificador (1 o superior)
    int tipo; // Tipo (0 = simple; 1 = con plazo)
    int estado; // Estado (0 = pendiente; 1 = terminada)
    int prioridad; // Prioridad (de 1 a 10)
    int *dependencias; // IDs separados por comas (",")
    char fecha[18]; // Fecha (formato = dd/mm/aaaa:hh:mm   -> 16 caract)
    char descripcion[52]; // Descripción (max = 50)
    char propietario[22]; // Propietario (max = 20)
    
    struct tareaS *siguiente; // Siguiente tarea
    
};

typedef struct tareaS TareaS;
TareaS *primero = NULL;
TareaS *ultimo = NULL;
TareaS *tarea = NULL;

char usuario[22]; // Nombre de usuario (máx 20 caract)




  ////////////////////////////
 ///* PROGRAMA PRINCIPAL *///
////////////////////////////


int main(int argc, const char * argv[]) {
    
    int opc; // Opción elegida
    char opcS[16];
    
    int modif = 0; // Se han realizado modificaciones ?
    int salir = 0; // Salir ?
    int salirpreg = 0; // Salir del preguntar ?
    
    clearScreen(); // Limpiar la pantalla
    
    
    printf("\n");
    
    aster(39, '*'); printf("\n"); // Mensaje de bienvenida con asteriscos
    aster(39, '*'); printf("\n");
    asterMensj('*', "AGENDA", 39); printf("\n");
    aster(39, '*'); printf("\n");
    aster(39, '*'); printf("\n");
    
    
    
    printf("\n\n");
    
    printf("Introduzca su identificador: "); // Pedir el usuario
    fgets(usuario, 20, stdin);
    fflush(stdin);
    setbuf(stdin, NULL);
    
    int k;
    for (k = 0; k < strlen(usuario); k++)
    {
        if (usuario[k] == '\n')
        {
            usuario[k] = '\0';
        }
    }
    
    
    LeerArchivo ();

    
    
    printf("\n\n");
    
    // Menú principal
    do{
        printNegritaBlanco("Agenda:\n\n"); // Imprimir menú
        printf("1) Crear tarea\n");
        printf("2) Ver tarea\n");
        printf("3) Ver lista tareas\n");
        printf("0) Salir\n\n");
        printf("¿Siguiente operación? ");
        
        do{
            //scanf(" %i", &opc);
            fgets(opcS, 15, stdin); // Leer opción
            opc = atoi(opcS);
            
            if (opc == 0)
            {
                if (opcS[0] != '0')
                {
                    opc = -1;
                }
            }
            
            
            switch (opc) { // Realizar tareas según opción elegida
                case CREAR:
                    modif = 1;
                    salirpreg = 1;
                    CrearTarea(); // Llamamos a la función
                    break;
                    
                case VER:
                    salirpreg = 1;
                    VerTarea(); // Llamamos a la función
                    break;
                    
                case LISTA:
                    salirpreg = 1;
                    VerLista(); // Llamamos a la función
                    break;
                    
                case SALIR:
                    salirpreg = 1;
                    salir = Salir(modif); // Ver si se puede salir
                    if (salir == 0)
                    {
                        GuardarArchivo(); // Guardamos los cambios si se desea
                        salir = 1;
                    }
                    break;
                    
                default:
                    salirpreg = 0;
                    printRojo("\nElección incorrecta, pulsa 1, 2, 3 o 0: "); // Opción incorrecta
                    break;
            }
            
        }while (salirpreg == 0);
        
        fflush(stdin); // Borrar caché
        setbuf(stdin, NULL);
        
        
        printf("\n\n\n");
        
        clearScreen(); // Limpiar la pantalla
        
    }while (salir <= 0); // Volver al menú principal si no se sale
    
    return 0;
}