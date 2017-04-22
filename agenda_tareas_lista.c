//
//  agenda_tareas_lista.c
//  Agenda
//
//  Created by Manuel Castro, Raquel Balboa y Xoan Cosmed.
//

#include "agenda_tareas_lista.h"


///// VARIABLES /////

extern int tareas_num; // Contador de tareas

struct tareaS {
    
    int id; // Identificador (1 o superior)
    int tipo; // Tipo (0 = simple; 1 = con plazo)
    int estado; // Estado (0 = pendiente; 1 = terminada)
    int prioridad; // Prioridad (de 1 a 10)
    int *dependencias; // IDs separados por comas (",") (termina en 0)
    char fecha[18]; // Fecha (formato = dd/mm/aaaa:hh:mm   -> 16 caract)
    char descripcion[52]; // Descripción (max = 50)
    char propietario[22]; // Propietario (max = 20)
    
    struct tareaS *siguiente; // Siguiente tarea
};

typedef struct tareaS TareaS;
extern TareaS *primero;
extern TareaS *ultimo;
extern TareaS *tarea;

extern char usuario[22]; // Nombre de usuario (máx 20 caract)


///// FUNCIÓN PRINCIPAL //////

void VerLista ()
{
    int opc; // Opción elegida
    char resp[15]; // Respuesta del usuario (de la que se saca "opc")
    
    int tipo = -2; // Qué tareas presentar (0 = todas; 1 = pendientes; 2 = terminadas)
    int forma = -2; // De qué forma presentar (0 = pantalla; 1 = archivo)
    
    do{
        
        printf("\n\n");
        printf("1) Pendientes\n");
        printf("2) Terminadas\n");
        printf("3) Todas\n");
        printf("0) Cancelar\n");
        printf("¿Tareas a presentar? ");
        fflush(stdin);
        
        fgets(resp, 15, stdin); // Obtener el tipo de tareas a presentar
        opc = atoi(resp);
        
        if (opc == 0)
        {
            if (resp[0] != '0')
            {
                opc = -1;
            }
        }
        
        switch (opc) {
            case 1:
                tipo = 1;
                break;
            case 2:
                tipo = 2;
                break;
                
            case 3:
                tipo = 0;
                break;
                
            case 0:
                tipo = -1;
                break;
                
            default:
                tipo = -2;
                break;
        }
    
    } while(tipo == -2); // Repetir hasta obtener una respuesta correcta
    
    if (tipo == -1) return; // Si se cancela, se vuelve al menú
    
    do{
        
        printf("\n");
        printf("1) Por pantalla\n");
        printf("2) A archivo\n");
        printf("0) Cancelar\n");
        printf("¿Presentación de resultado? ");
        fflush(stdin);
        
        fgets(resp, 15, stdin); // Obtener el orden en el que presentarlo
        opc = atoi(resp);
        
        if (opc == 0)
        {
            if (resp[0] != '0')
            {
                opc = -1;
            }
        }
        
        switch (opc) {
            case 1:
                forma = 0;
                break;
                
            case 2:
                forma = 1;
                break;
                
            case 0:
                forma = -1;
                break;
                
            default:
                forma = -2;
                break;
        }
        
    } while (forma == -2); // Repetir hasta obtener una respuesta correcta
    
    if (forma == -1) return; // Si se cancela, vuelvo al menú
    
    printf("\n");
    
    switch (tipo) {
        case 0:
            listaTodas(forma); // Mostrar todas
            break;
            
        case 1:
            listaPendientes(forma); // Mostrar pendientes
            break;
            
        case 2:
            listaTerminadas(forma); // Mostrar terminadas
            break;
            
        default:
            break;
    }
}


///// FUNCIONES SECUNDARIAS //////


void listaTodas (int forma) // Lista de TODAS las tareas
{
    tarea = primero; // Empezaremos por la primera tarea
    
    FILE *archivo = NULL;
    
    if (forma == 0) // PANTALLA
    {
        archivo = stdout; // El archivo es el de la pantalla
    }
    else if (forma == 1) // ARCHIVO
    {
        char nombrearchivo[25];
        printf("Indicar el identificador del fichero (nombre con extensión .txt): ");
        setbuf(stdin, NULL);
        fflush(stdin);
        fgets(nombrearchivo, 25, stdin); // Solicito nombre
        int k;
        for (k = 0; k < strlen(nombrearchivo); k++)
        {
            if (nombrearchivo[k] == '\n')
            {
                nombrearchivo[k] = '\0';
            }
        }
        
        if ((archivo = fopen(nombrearchivo, "w+")) == NULL) // Abrimos el archivo
        {
            printf("ERROR: ");
            printRojo("No es posible abrir el fichero ");
            
            printf("\tPulsar ENTER para iniciar la salida del programa."); // Salir
            while (getchar()!='\n') {}
            exit(5);
        }
        
        printf("\n");
    }
    
    int cont = 0;
    
    while (tarea != NULL) // Mostramos TAREAS hasta que no haya más
    {
        if (!strcmp(tarea->propietario, usuario)) // Comprobamos el usuario
        {
            fprintf(archivo, "ID: %i\n", tarea->id); // Imprimimos los datos
            fprintf(archivo, "Descripción: %s\n\n", tarea->descripcion);
            
            cont++;
        }
        
        tarea = tarea->siguiente; // La nueva tarea será la siguiente a la actual
    }
    
    if (cont == 0) // Si no hay tareas a mostrar doy un aviso
    {
        printf("\nAVISO: ");
        printRojo("El usuario no tiene tareas de ese tipo o no tiene tareas.\n");
    }
    
    fflush(stdin);
    setbuf(stdin, NULL);

    
    printf("Pulsa ENTER para volver al menú principal del programa: ");
    
    if (forma == 1)
    {
        fclose(archivo);
    }
    
    while (getchar()!='\n') {}
    return;
}


void listaPendientes (int forma) // Lista de las tareas PENDIENTES
{
    tarea = primero; // Empezaremos por la primera tarea
    
    FILE *archivo = NULL;
    
    if (forma == 0) // PANTALLA
    {
        archivo = stdout; // El archivo es el de la pantalla
    }
    else if (forma == 1) // ARCHIVO
    {
        char nombrearchivo[25];
        printf("Indicar el identificador del fichero (nombre con extensión .txt): ");
        setbuf(stdin, NULL);
        fflush(stdin);
        fgets(nombrearchivo, 25, stdin); // Solicito nombre
        int k;
        for (k = 0; k < strlen(nombrearchivo); k++)
        {
            if (nombrearchivo[k] == '\n')
            {
                nombrearchivo[k] = '\0';
            }
        }
        
        if ((archivo = fopen(nombrearchivo, "w+")) == NULL) // Abrimos el archivo
        {
            printf("ERROR: ");
            printRojo("No es posible abrir el fichero ");
            
            printf("\tPulsar ENTER para iniciar la salida del programa."); // Salir
            while (getchar()!='\n') {}
            exit(5);
        }
        
        printf("\n");
    }
    
    int cont = 0;
    
    while (tarea != NULL) // Mostramos TAREAS hasta que no haya más
    {
        if (tarea->estado == 0 && !strcmp(tarea->propietario, usuario)) // Sólo tomamos las tareas pendientes (estado 0) y las que pertenezcan al usuario
        {
            fprintf(archivo, "ID: %i\n", tarea->id); // Imprimimos los datos
            fprintf(archivo, "Descripción: %s\n\n", tarea->descripcion);
            
            cont++;
        }
        
        tarea = tarea->siguiente; // La nueva tarea será la siguiente a la actual
    }
    
    if (cont == 0) // Si no hay tareas a mostrar doy un aviso
    {
        printf("\nAVISO: ");
        printRojo("El usuario no tiene tareas de ese tipo o no tiene tareas.\n");
    }
    
    fflush(stdin);
    setbuf(stdin, NULL);
    
    printf("Pulsa ENTER para volver al menú principal del programa: ");
    
    if (forma == 1)
    {
        fclose(archivo);
    }
    
    while (getchar()!='\n') {}
    return;
}


void listaTerminadas (int forma) // Lista de las tareas TERMINADAS
{
    tarea = primero; // Empezaremos por la primera tarea
    
    FILE *archivo = NULL;
    
    if (forma == 0) // PANTALLA
    {
        archivo = stdout; // El archivo es el de la pantalla
    }
    else if (forma == 1) // ARCHIVO
    {
        char nombrearchivo[25];
        printf("Indicar el identificador del fichero (nombre con extensión .txt): ");
        setbuf(stdin, NULL);
        fflush(stdin);
        fgets(nombrearchivo, 25, stdin); // Solicito nombre
        int k;
        for (k = 0; k < strlen(nombrearchivo); k++)
        {
            if (nombrearchivo[k] == '\n')
            {
                nombrearchivo[k] = '\0';
            }
        }
        
        if ((archivo = fopen(nombrearchivo, "w+")) == NULL) // Abrimos el archivo
        {
            printf("ERROR: ");
            printRojo("No es posible abrir el fichero ");
            
            printf("\tPulsar ENTER para iniciar la salida del programa."); // Salir
            while (getchar()!='\n') {}
            exit(5);
        }
        
        printf("\n");
    }
    
    int cont = 0;
    
    while (tarea != NULL) // Mostramos TAREAS hasta que no haya más
    {
        if (tarea->estado == 1 && !strcmp(tarea->propietario, usuario)) // Sólo tomamos las tareas pendientes (estado 1) y las que pertenezcan al usuario
        {
            fprintf(archivo, "ID: %i\n", tarea->id); // Imprimimos los datos
            fprintf(archivo, "Descripción: %s\n\n", tarea->descripcion);
            
            cont++;
        }
        
        tarea = tarea->siguiente; // La nueva tarea será la siguiente a la actual
    }
    
    if (cont == 0) // Si no hay tareas a mostrar doy un aviso
    {
        printf("\nAVISO: ");
        printRojo("El usuario no tiene tareas de ese tipo o no tiene tareas.\n");
    }
    
    fflush(stdin);
    setbuf(stdin, NULL);
    
    printf("Pulsa ENTER para volver al menú principal del programa: ");
    
    if (forma == 1)
    {
        fclose(archivo);
    }
    
    while (getchar()!='\n') {}
    return;
}