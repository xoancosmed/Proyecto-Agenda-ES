//
//  agenda_grupos.c
//  Agenda 2
//
//  Created by Xoán Carlos Cosmed Peralejo.
//

#include "agenda_grupos.h"


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
    
    char nombre [51]; // Nombre del grupo (max = 50 caract)
    
    struct grupoS *siguiente; // Siguiente grupo
    
};

typedef struct grupoS GrupoS; // Grupos
extern GrupoS *primerG;
extern GrupoS *ultimoG;
extern GrupoS *grupo;

extern char usuario[22]; // Nombre de usuario (máx 20 caract)


///// FUNCIONES PRINCIPALES /////

void LeerGrupos ()
{
    FILE *archivo;
    if ((archivo = fopen("grupos.txt", "r"))==NULL) // Abrimos el archvio
    {
        printf("Error:");
        printRojo(" No existe el fichero ");
        printAzul("grupos.txt");
        printRojo(".");
        
        printf("\n\nPulsar ENTER para crearlo y a continuación rellenarlo (con otra app).");
        while (getchar() != '\n') {}
        archivo = fopen("grupos.txt", "a+");
        fclose(archivo);
        exit(2);
    }
    
    char stringTMP[1000]; // Variable temporal
    char nombreTMP[51];
    char usuarioTMP[21];
    
    int grupos_num = contarCaractArchivo("grupos.txt", ':'); // Número de grupos en el archivo
    int i; // Contador
    
    rewind(archivo); // Volvemos al principio del archivo
    
    for (i = 0; i < grupos_num; i++)
    {
        fgets(stringTMP, 1000, archivo); // Obtenemos un grupo
        
        int j,k;
        
        //printf("\n\n%s", stringTMP);
        
        for (j = 0, k = 0; j < strlen(stringTMP); j++) // Buscamos el nombre del grupo
        {
            if (stringTMP[j] == '\n' || stringTMP[j] == '\0')
            {
                printf("\n\nERROR: El archivo grupos.txt no sigue el formato adecuado.\n");
                exit(2);
            }
            else if (stringTMP[j] == ':')
            {
                j++;
                break;
            }
            else
            {
                if ((k + 1) >= 51)
                {
                    printf("\n\nERROR: El archivo grupos.txt no sigue el formato adecuado (nombre de grupo demasiado largo).\n");
                    exit(2);
                }
                
                nombreTMP[k] = stringTMP[j];
                nombreTMP[k+1] = '\0';
                
                k++;
            }
        }
        
        
        for (k = 0; j < strlen(stringTMP); j++) // Buscamos los componentes del grupo
        {
            
            if (stringTMP[j] == '\n' || stringTMP[j] == '\0')
            {
                if (!strcmp(usuario, usuarioTMP)) // Si uno de los componentes coincide con el usuario ...
                {
                    grupo = (GrupoS *)calloc(1, sizeof(GrupoS)); // ... lo guardamos en la lista
                    grupo->siguiente = NULL;
                    strcpy(grupo->nombre, nombreTMP);
                    
                    if (primerG == NULL)
                    {
                        primerG = grupo;
                        ultimoG = grupo;
                    }
                    else
                    {
                        ultimoG->siguiente = grupo;
                        ultimoG = grupo;
                    }
                }
                
                break;
            }
            else if (stringTMP[j] == ',')
            {
                if (!strcmp(usuario, usuarioTMP)) // Si uno de los componentes coincide con el usuario ...
                {
                    grupo = (GrupoS *)calloc(1, sizeof(GrupoS)); // ... lo guardamos en la lista
                    grupo->siguiente = NULL;
                    strcpy(grupo->nombre, nombreTMP);
                    
                    if (primerG == NULL)
                    {
                        primerG = grupo;
                        ultimoG = grupo;
                    }
                    else
                    {
                        ultimoG->siguiente = grupo;
                        ultimoG = grupo;
                    }
                }
                
                k = 0;
            }
            else if (stringTMP[j] == ' ')
            {
                
            }
            else
            {
                if ((k + 1) >= 21)
                {
                    printf("\n\nERROR: El archivo grupos.txt no sigue el formato adecuado (nombre de usuario demasiado largo).\n");
                    exit(2);
                }
                
                usuarioTMP[k] = stringTMP[j];
                usuarioTMP[k+1] = '\0';
                
                
                k++;
            }
        }
    }

    
    grupo = primerG;
    while (grupo != NULL)
    {
        grupo = grupo->siguiente;
    }
}

void LiberarGrupos ()
{
    grupo = primerG;
    GrupoS *grupoTMP;
    while (grupo != NULL) // Liberamos la memoria ocupada por la lista de grupos
    {
        grupoTMP = grupo->siguiente;
        free(grupo);
        grupo = grupoTMP;
    }
}