//
//  agenda_tareas_ver.c
//  Agenda 2
//
//  Created by Xoán Carlos Cosmed Peralejo.
//

#include "agenda_tareas_ver.h"

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
 

///// FUNCIÓN PRINCIPAL //////

void VerTarea ()
{
    int ID = 0; // Variable para el ID
    
    int permitido = 0; // Permiso para ver la tarea (0 = denegado; 1 = permitido)
    int cont = 0;
    
    do {
        
        printf("\nIntroducir el identificador de la tarea: "); // Pedimos el ID
        scanf(" %i", &ID);
        
    } while (ID < 1);
    
    tarea = primero;
    while (tarea != NULL) // Buscamos la tarea
    {
        if (tarea->id == ID) // Si el ID coincide comprobamos los permisos
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
                        
                        if (tarea->borrado == 0)
                        {
                            printf("\nGrupo: %s\n", grupo->nombre);
                        }
                        
                        break;
                    }
                    
                    grupo = grupo->siguiente; // Si no lo encontramos pasamos al siguiente
                }
            }
            
            
            if (permitido == 1) // Comprobamos los permisos
            {
                if (tarea->borrado == 0) // Comprobamos si la tarea está borrada
                {
                    printf("\nDescripción: %s\n", tarea->descripcion); // IMPRIMIMOS LOS DATOS
                    
                    printf("Prioridad: %i\n", tarea->prioridad);
                    
                    if (tarea->estado == 0)
                    {
                        printf("Estado: pendiente\n");
                    }
                    else if (tarea->estado == 1)
                    {
                        printf("Estado: terminado\n");
                        
                    }
                    else
                    {
                        printf("Estado: desconocido\n");
                    }
                    
                    if (tarea->tipo == 0)
                    {
                        printf("Tipo: simple\n");
                    }
                    else if (tarea->tipo == 1)
                    {
                        printf("Tipo: con_plazo\n");
                        
                    }
                    else
                    {
                        printf("Tipo: desconocido\n");
                    }
                    
                    printf("Plazo: %s\n", tarea->fecha);
                    
                    if ((tarea->tipo == 1) && (tarea->estado == 0))
                    {
                        printf("Días para terminar la tarea: %i\n", diasRestantes(tarea->fecha));
                    }
                    
                    imprimirDependencias1(tarea->id);
                    imprimirDependencias2(tarea->id);
                }
                else
                {
                    printf("\nAVISO: ");
                    printRojo("La tarea ha sido borrada.\n");
                    printf("\nPulsa ENTER para volver al menú principal del programa: ");
                    getchar();
                    while (getchar()!='\n') {}
                    return;
                }
            }
            else
            {
                printf("\nAVISO: ");
                printRojo("Opción no permitida sobre esta tarea.\n");
                printf("\nPulsa ENTER para volver al menú principal del programa: ");
                getchar();
                while (getchar()!='\n') {}
                return;
            }
            
            cont = 1;
            break;
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


///// FUNCIONES SECUNDARIAS //////

int diasRestantes (char fecha[18]) // Calcular los DÍAS RESTANTES
{
    int dias; // Días para que termine la tarea
    long int differencia;
    
    int a; // Declaramos contadores
    int b = 0;
    
    char fechaP[5][10]; // Variable para las compenentes de la fecha
    
    for (a = 0; a < 10; a++) // Primero separamos sus componentes (formato de la fecha: DD/MM/YYYY:hh:mm)
    {
        if (fecha[b] == '/')
        {
            fechaP[0][a] = '\0'; // Día
            b++;
            break;
        }
        else
        {
            fechaP[0][a] = fecha[b];
        }
        b++;
    }
    for (a = 0; a < 10; a++)
    {
        if (fecha[b] == '/')
        {
            fechaP[1][a] = '\0'; // Mes
            b++;
            break;
        }
        else
        {
            fechaP[1][a] = fecha[b];
        }
        b++;
    }
    for (a = 0; a < 10; a++)
    {
        if (fecha[b] == ':')
        {
            fechaP[2][a] = '\0'; // Año
            b++;
            break;
        }
        else
        {
            fechaP[2][a] = fecha[b];
        }
        b++;
    }
    for (a = 0; a < 10; a++)
    {
        if (fecha[b] == ':')
        {
            fechaP[3][a] = '\0'; // Hora
            b++;
            break;
        }
        else
        {
            fechaP[3][a] = fecha[b];
        }
        b++;
    }
    fechaP[4][0] = fecha[b++];
    fechaP[4][1] = fecha[b++];
    fechaP[4][2] = '\0'; // Minutos
    
    typedef struct tm Tm; // Definimos un tipo que sea un estructura tm (de la librería time.h)
    
    Tm *fechaS; // Creamos una variable del tipo Tm (struct tm) y reservamos meoria
    fechaS = (Tm *)calloc(1, sizeof(Tm));
    
    fechaS->tm_mday = atoi(fechaP[0]); // Ahí metemos las compenentes de la fecha convertidos a int
    fechaS->tm_mon = atoi(fechaP[1])-1;
    fechaS->tm_year = atoi(fechaP[2])-1900;
    fechaS->tm_hour = atoi(fechaP[3]);
    fechaS->tm_min = atoi(fechaP[4]);
    fechaS->tm_isdst = 1; // Activamos el horario de verano
    
    time_t fechaU = mktime(fechaS); // Convertimos la fecha en segundos después de la época Unix (estandar)
    time_t fechaA = time(NULL); // Obtenemos la fecha actual en segundos desde la época Unix
    
    differencia = (long int) (fechaU - fechaA); // Calculamos la diferencia
    dias = (int) (differencia / (60 * 60 * 24)); // Y lo pasamos a días
    
    return dias;
}

void imprimirDependencias1 (int ID) // Obtener las DEPENDENCIAS
{
    struct dependenciasL {
        int dependencia;
        int esultima;
        struct dependenciasL *siguiente;
    };
    
    typedef struct dependenciasL DependenciasL;
    DependenciasL *primeraD = NULL;
    DependenciasL *ultimaD = NULL;
    
    DependenciasL *depTMP = NULL;
    
    int cont = 0;
    int i;
    
    TareaS *tareaTMP = primero;
    
    while (tareaTMP != NULL) // Buscamos la tarea
    {
        if (tareaTMP->id == ID)
        {
            break;
        }
        
        tareaTMP = tareaTMP->siguiente;
    }
    
    printf("Tareas de las que depende la tarea:\n");
    
    
    printf("\tDirectamente: "); // Obtenemos las dependencias DIRECTAS
    
    if (tareaTMP->dependencias[0] != 0)
    {
        for (i = 0; tareaTMP->dependencias[i] != 0; i++)
        {
            printf("%i ", tareaTMP->dependencias[i]);
            
            depTMP = (DependenciasL *)calloc(1, sizeof(DependenciasL));
            
            depTMP->dependencia = tareaTMP->dependencias[i];
            depTMP->esultima = 1;
            
            if (primeraD == NULL)
            {
                primeraD = depTMP;
                ultimaD = depTMP;
            }
            else
            {
                ultimaD->siguiente = depTMP;
                ultimaD->esultima = 0;
                ultimaD = depTMP;
            }
        }
    }
    else
    {
        printf("0");
        printf("\n\tIndirectamente: 0\n");
        return;
    }
    
    
    depTMP = (DependenciasL *)calloc(1, sizeof(DependenciasL));
    depTMP->esultima = 1;
    ultimaD->siguiente = depTMP;
    ultimaD->esultima = 0;
    ultimaD = depTMP;
    
    
    
    printf("\n\tIndirectamente: "); // Obtenemos las dependencias INDIRECTAS
    
    DependenciasL *dep2TMP = NULL;
    depTMP = primeraD;
    
    
    while (depTMP->esultima != 1)
    {
        
        tareaTMP = primero;
        
        while (tareaTMP != NULL)
        {
            if (tareaTMP->id == depTMP->dependencia)
            {
                for (i = 0; tareaTMP->dependencias[i] != 0; i++)
                {
                    printf("%i ", tareaTMP->dependencias[i]); // Imprimimos la dependencia actual
                    
                    cont++;
                    
                    
                    ultimaD->dependencia = tareaTMP->dependencias[i]; // La añadimos a la lista para buscar más
                    ultimaD->esultima = 0;
                    
                    dep2TMP = (DependenciasL *)calloc(1, sizeof(DependenciasL));
                    dep2TMP->esultima = 1;
                    ultimaD->siguiente = dep2TMP;
                    ultimaD = dep2TMP;
                    ultimaD->siguiente = NULL;
                }
            }
            
            tareaTMP = tareaTMP->siguiente;
        }
        
        depTMP = depTMP->siguiente;
        
    }
    
    if (cont == 0)
    {
        printf("0");
    }
    
    printf("\n");
}

void imprimirDependencias2 (int ID) // Obtener las DEPENDENCIAS
{
    printf("Tareas dependientes directamente de la tarea: ");
    
    int cont = 0;
    
    int j;
    TareaS *tareaTMP = primero;
    while (tareaTMP != NULL)
    {
        for (j = 0; tareaTMP->dependencias[j] != 0; j++)
        {
            if (tareaTMP->dependencias[j] == ID) // Buscamos por todas las tareas y dependencias ...
            {
                printf("%i ", tareaTMP->id); // ... cuando una dependencia y una id coincidan lo imprimimos
                
                cont++;
            }
        }
        
        tareaTMP = tareaTMP->siguiente;
    }
    
    if (cont == 0)
    {
        printf("0");
    }
    
    printf("\n");
}