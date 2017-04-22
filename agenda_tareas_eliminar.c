//
//  agenda_tareas_eliminar.c
//  Agenda 2
//
//  Created by Xoán Carlos Cosmed Peralejo.
//

#include "agenda_tareas_eliminar.h"


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


///// FUNCIÓN PRINCIPAL /////

void EliminarTarea ()
{
    int ID; // Identificador de la tarea
    
    int permitido = 0; // Permisos sobre la tarea (0 = denegado; 1 = permitido)
    
    int cont = 0;
    
    
    do {
        
        printf("\nIntroducir el identificador de la tarea: "); // Pedimos el ID
        scanf(" %i", &ID);
        
    } while (ID < 1);
    
    
    if (primero == NULL)
    {
        printf("\nAVISO: ");
        printRojo("Lista de tareas vacía.\n");
        
        getchar();
        printf("\nPulsar ENTER para volver al menú principal del programa: ");
        while (getchar()!='\n') {}
        return;
    }
    
    
    tarea = primero; // Empezaremos a buscar por la perimera tarea hasta la última
    
    while (tarea != NULL)
    {
        if (tarea->id == ID) // Buscamos la tarea por ID
        {
            if (!strcmp(tarea->propietario, usuario)) // Comprobamos el usuario
            {
                permitido = 1; // Permitido
            }
            else
            {
                grupo = primerG; // Empezamos a buscar los grupos por el primero
                
                while (grupo != NULL)
                {
                    if (!strcmp(tarea->propietario, grupo->nombre))
                    {
                        permitido = 1; // Permitido
                    }
                    
                    grupo = grupo->siguiente; // Si no lo encontramos pasamos al siguiente
                }
            }

            
            if (permitido == 1) // Comprobamos los permisos sobre esta tarea
            {
                int k = 0;
                int j = 0;
                while (tarea->dependencias[k] != 0) // Comprobamos si no tiene dependencias
                {
                    TareaS *tareaTMP;
                    tareaTMP = primero;
                    
                    while (tareaTMP != NULL)
                    {
                        if (tareaTMP->id == tarea->dependencias[k])
                        {
                            if (tareaTMP->borrado == 0)
                            {
                                j++;
                            }
                        }
                        
                        tareaTMP = tareaTMP->siguiente;
                    }
                    
                    k++;
                }
                
                if (j == 0) // Si todo va bien la eliminamos
                {
                    tarea->borrado = 1; // Establecemos la tarea como eliminada (luego no se guardará)
                    
                    printf("\nLa tarea %i ha sido eliminada con éxito.\n", ID);
                }
                else
                {
                    printf("\nAVISO: ");
                    printRojo("Otras tareas dependen de esta tarea.\n");
                }
            }
            else
            {
                printf("\nAVISO: ");
                printRojo("Operación no permitida sobre esta tarea.\n");
            }
            
            cont++;
        }
        
        tarea = tarea->siguiente;
    }
    
    
    if (cont == 0) // Tarea no encontrada
    {
        printf("\nAVISO: ");
        printRojo("Tarea no existente.\n");
    }
    
    
    getchar();
    printf("\nPulsar ENTER para volver al menú principal del programa: ");
    while (getchar()!='\n') {}
    return;
}