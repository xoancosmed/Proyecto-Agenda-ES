//
//  agenda_archivos.c
//  Agenda 2
//
//  Created by Xoán Carlos Cosmed Peralejo.
//


#include "agenda_archivos.h"



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
    
    int borrado; // Borrado (0 = no (existe); 1 = eliminada)
    
    struct tareaS *siguiente; // Siguiente tarea
};

typedef struct tareaS TareaS;
extern TareaS *primero;
extern TareaS *ultimo;
extern TareaS *tarea;

struct grupoS {
    
    char nombre [52]; // Nombre del grupo (max = 50 caract)
    
    struct grupoS *siguiente; // Siguiente grupo
    
};

typedef struct grupoS GrupoS; // Grupos
extern GrupoS *primerG;
extern GrupoS *ultimoG;
extern GrupoS *grupo;

extern char usuario[22]; // Nombre de usuario (máx 20 caract)



///// FUNCIONES PRINCIPALES /////


void LeerArchivo () // LEER la información del ARCHIVO
{
    FILE *archivo;
    if ((archivo = fopen("tareas.txt", "r"))==NULL) // Abrimos el archvio
    {
        printf("Error:");
        printRojo(" No existe el fichero ");
        printAzul("tareas.txt");
        printRojo(".");
        
        printf("\n\nPulsar ENTER para crearlo.");
        if (getchar()=='\n') // Si no existe se crea
        {
            archivo = fopen("tareas.txt", "a+");
            fclose(archivo);
            return;
        }
        else exit(1);
    }
    
    tareas_num = contarCaractArchivo("tareas.txt", '*') + 1; // Buscamos el número de tareas y reservamos memoria
    
    rewind(archivo); // Vamos al principio del archivo
    
    int i; // Contador
    char stringTMP[1000]; // Variables temporales
    char stringsTMP[31][31];
    
    fgets(stringTMP, 1000, archivo); // Si está vacío no hay tareas
    if (feof(archivo) == 1)
    {
        tareas_num = 0;
    }
    else if (stringTMP[0] == '\n' || stringTMP[0] == '\0' || stringTMP[0] == EOF || stringTMP[0] == ' ')
    {
        tareas_num = 0;
    }
    
    rewind(archivo);
    
    for (i = 0; i < tareas_num; i++)
    {
        tarea = (TareaS *)calloc(1, sizeof(TareaS)); // Reservamos memoria para el nuevo elemento
        
        
        fgets(stringTMP, 100, archivo); // Obtenemos el tipo de tarea (tarea i)
        if (!strcmp(stringTMP, "con_plazo\n"))
        {
            tarea->tipo = 1;
        }
        else if (!strcmp(stringTMP, "simple\n"))
        {
            tarea->tipo = 0;
        }
        else
        {
            printf("Error:");
            printRojo(" El fichero ");
            printAzul("tareas.txt");
            printRojo(" no sigue el formato establecido.");
            
            printf("\tPulsar ENTER para iniciar la salida del programa.");
            while (getchar()!='\n') {}
            exit(1);
        }
        
        fgets(stringTMP, 100, archivo); // Obtenemos la ID
        tarea->id = atoi(stringTMP);
        if (tarea->id < 0)
        {
            printf("Error:");
            printRojo(" El fichero ");
            printAzul("tareas.txt");
            printRojo(" no sigue el formato establecido.");
            
            printf("\tPulsar ENTER para iniciar la salida del programa.");
            while (getchar()!='\n') {}
            exit(1);
        }
        
        fgets(stringTMP, 100, archivo); // Obtenemos la descripción
        int j;
        for (j = 0; j < strlen(stringTMP); j++)
        {
            if (stringTMP[j] == '\n')
            {
                stringTMP[j] = '\0';
            }
        }
        strcpy(tarea->descripcion, stringTMP);
        tarea->descripcion[50] = '\0';
        
        fgets(stringTMP, 100, archivo); // Obtenemos el propietario
        int k;
        for (k = 0; k < strlen(stringTMP); k++)
        {
            if (stringTMP[k] == '\n')
            {
                stringTMP[k] = '\0';
            }
        }
        strcpy(tarea->propietario, stringTMP);
        tarea->propietario[20] = '\0';

        fgets(stringTMP, 100, archivo); // Obtenemos la prioridad
        tarea->prioridad = atoi(stringTMP);
        if ((tarea->prioridad > 10) || (tarea->prioridad < 0)) // No sigue el formato establecido
        {
            printf("Error:");
            printRojo(" El fichero ");
            printAzul("tareas.txt");
            printRojo(" no sigue el formato establecido.");
            
            printf("\tPulsar ENTER para iniciar la salida del programa.");
            while (getchar()!='\n') {}
            exit(1);
        }

        fgets(stringTMP, 100, archivo); // Obtenemos el estado
        if (!strcmp(stringTMP, "terminada\n"))
        {
            tarea->estado = 1;
        }
        else if (!strcmp(stringTMP, "pendiente\n"))
        {
            tarea->estado = 0;
        }
        else
        {
            printf("Error:");
            printRojo(" El fichero ");
            printAzul("tareas.txt");
            printRojo(" no sigue el formato establecido.");
            
            printf("\tPulsar ENTER para iniciar la salida del programa.");
            while (getchar()!='\n') {}
            exit(1);
        }

        fgets(stringTMP, 100, archivo); // Obtenemos la fecha
        int l;
        for (l = 0; l < strlen(stringTMP); l++)
        {
            if (stringTMP[l] == '\n')
            {
                stringTMP[l] = '\0';
            }
        }
        strcpy(tarea->fecha, stringTMP);
        tarea->fecha[16] = '\0';
        
        fgets(stringTMP, 1000, archivo);// Obtenemos las dependencias
        if (strcmp(stringTMP, "-\n"))
        {
            int j, k, l, m = 0;
            for (j = 0, k = 0, l = 0; j < 1000; j++,l++)
            {
                if (stringTMP[j] == '\n' || stringTMP[j] == '\0')
                {
                    break;
                }
                else if (stringTMP[j] == ',')
                {
                    k++;
                    l = -1;
                    m++;
                }
                else
                {
                    stringsTMP[k][l] = stringTMP[j];
                    stringsTMP[k][l+1] = '\0';
                }
            }
            m++;
            tarea->dependencias = (int *)calloc(m+1, sizeof(int));
            for (j = 0; j < m; j++)
            {
                tarea->dependencias[j] = atoi(stringsTMP[j]);
            }
            tarea->dependencias[m] = 0;
        }
        else
        {
            tarea->dependencias = (int *)calloc(1, sizeof(int));
            tarea->dependencias[0] = 0;
        }
        
        if (i != (tareas_num - 1))
        {
            fgets(stringTMP, 100, archivo); // Compruebo que se acabaron los datos de la tarea i
            if (!(!strcmp(stringTMP, "*\n") || !strcmp(stringTMP, "*")))
            {
                printf("Error:");
                printRojo(" El fichero ");
                printAzul("tareas.txt");
                printRojo(" no sigue el formato establecido.");
                
                printf("\tPulsar ENTER para iniciar la salida del programa.");
                while (getchar()!='\n') {}
                exit(1);
            }
        }
        
        
        
        tarea->borrado = 0; // La tarea no está borrada al comenzar
        
        
        
        
        // Guardamos la dirección del nuevo elemento
        
        if (primero == NULL) // Si es el primer elemento de la lista, será el primero y el último
        {
            primero = tarea;
            ultimo = tarea;
        }
        else // Sino es el primero, será el siguiente del último y pasará a ser el nuevo último
        {
            ultimo -> siguiente = tarea;
            ultimo = tarea;
        }
        
        
        ultimo -> siguiente = NULL; // Inicializo el puntero "siguiente" del último introducido

    }
    
    
    fclose(archivo); // Cerrar el archivo
    return;
}

void GuardarArchivo () // ESCRIBIR la información en el ARCHIVO
{
    FILE *archivo;
    archivo = fopen("tareas.txt", "w+"); // Abrimos el archvio
    if (archivo== NULL) { printf("\n\tError al arbir el archivo\n"); }
    
 
    tarea = primero; // Empezaremos a partir del primer elemento (estructura) ...
    
    while (tarea != NULL) // ... hasta llegar al que sea nulo
    {
        if (tarea->borrado == 0) // Sólo la guardamos si no está borrada
        {
            if (tarea->tipo == 0) // Guardamos el tipo
            {
                fprintf(archivo, "simple\n");
            }
            else if (tarea->tipo == 1)
            {
                fprintf(archivo, "con_plazo\n");
            }
            
            fprintf(archivo, "%i\n", tarea->id); // Guardamos la ID
            
            fprintf(archivo, "%s\n", tarea->descripcion); // Guardamos la descripción
            
            fprintf(archivo, "%s\n", tarea->propietario); // Guardar el propietario
            
            fprintf(archivo, "%i\n", tarea->prioridad); // Guardamos prioridad
            
            if (tarea->estado == 0) // Guardamos el estado
            {
                fprintf(archivo, "pendiente\n");
            }
            else if (tarea->estado == 1)
            {
                fprintf(archivo, "terminada\n");
            }
            
            fprintf(archivo, "%s\n", tarea->fecha); // Guardamos la fecha
            
            if (tarea->dependencias[0] != 0) // Guardamos las dependencias
            {
                int j = 0;
                while (tarea->dependencias[j+1] != 0) {
                    fprintf(archivo, "%i,", tarea->dependencias[j]);
                    j++;
                }
                fprintf(archivo, "%i\n", tarea->dependencias[j]);
            }
            else
            {
                fprintf(archivo, "-\n");
            }
        
            if (tarea->siguiente != NULL)
            {
                fprintf(archivo, "*\n"); // Guardamos el final de tarea
            }
        }
        
        
        tarea = tarea->siguiente; // Pasamos al siguiente elmento
    }
    
    //free(stringTMP);
    
    fclose(archivo); // Cerrar el archivo
    liberarMemoria(); // Liberamos la memoria dinámica
}



///// FUNCIONES SECUNDARIAS /////


int contarCaractArchivo (char nombre[], char caractBuscar) // Contar un caracter de un archivo
{
    FILE *archivo;
    if ((archivo = fopen(nombre, "r"))==NULL) // Abrimos el archvio
    {
        errorMess("No se ha podido abrir el archivo."); // Archivo no encontrado
    }
    
    int i = 0; // Contador de veces que aparece
    char caractArchivo;
    
    rewind(archivo); // Ponemos el puntero del archivo al principio
    
    while (1) {
        
        caractArchivo = getc(archivo); // Obtener el caracter del archivo y sumarle 1 posición al puntero
        
        if (caractArchivo == EOF)
        {
            break; // Si llegamos al final salimos
        }
        else if (caractArchivo == caractBuscar)
        {
            i++; // Si el caracter coincide sumamos uno al contador
        }
        
    }
    
    fclose(archivo);
    
    return i;
}

void liberarMemoria () // Liberar la memoria reservada
{
    tarea = primero; // Empezaremos a partir del primer elemento (estructura) ...
    TareaS *tarea2;
    
    while (tarea != NULL) // ... hasta llegar al que sea nulo
    {
        tarea2 = tarea->siguiente;
        
        free(tarea->dependencias); // Liberamos memoria
        free(tarea);
        
        tarea = tarea2;// Pasamos al siguiente elemento
    }
}