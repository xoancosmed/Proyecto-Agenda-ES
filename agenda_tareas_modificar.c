//
//  agenda_tareas_modificar.c
//  Agenda 2
//
//  Created by Xoán Carlos Cosmed Peralejo.
//

#include "agenda_tareas_modificar.h"


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

void ModificarTarea ()
{
    int ID; // Identificador de la tarea
    
    int modo = -1;
    
    
    printf("\n\n");
    printf("1) Terminar tarea\n");
    printf("2) Transferir tarea\n");
    printf("3) Modificar otro\n");
    printf("0) Cancelar\n");
    
    do{
        
        printf("¿Qué desea modificar? ");
        fflush(stdin);
        scanf(" %i", &modo); // Obtener lo que se quiere modificar
        
        if (modo == 0) return;
        
    } while((modo < 0) || (modo > 3)); // Repetir hasta obtener una respuesta correcta
    
    do {
        
        printf("\nIntroducir el identificador de la tarea (0 = cancelar): "); // Pedimos el ID
        scanf(" %i", &ID);
        
        if (ID == 0)
        {
            return;
        }
        
    } while (ID < 1);
    
    
    switch (modo) {
        case 1:
            terminarTarea(ID); // Llamamos a la función correspondiente
            getchar();
            break;

        case 2:
            transferirTarea(ID); // Llamamos a la función correspondiente
            break;
            
        case 3:
            modificarDatosTarea(ID); // Llamamos a la función correspondiente
            break;
            
        case 0:
            return; // Si se cancela se vuelve al menú principal
            break;
            
        default:
            break;
    }
    
    printf("\nPulsar ENTER para volver al menú principal del programa: ");
    while (getchar()!='\n') {}
    return;
}


///// FUNCIONES SECUNDARIAS /////

void terminarTarea (int ID) // Modificamos el ESTADO de la TAREA a Terminada
{
    int permitido = 0; // Permisos sobre la tarea (0 = denegado; 1 = permitido)
    int ndep = 0; // Si tiene dependencias nodep > 0 y no se puede terminar la tarea
    
    tarea = primero; // Buscamos la tarea empezando por la primera
    while (tarea != NULL)
    {
        if ((tarea->id == ID) && (tarea->borrado == 0)) // Buscamos por ID
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
            
            if (permitido == 1) // Comprobamos los permisos
            {
                int l = 0;
                while (tarea->dependencias[l] != 0) // Comprobamos si tiene dependencias
                {
                    TareaS *tareaTMP;
                    tareaTMP = primero;
                    
                    while (tareaTMP != NULL)
                    {
                        if (tareaTMP->id == tarea->dependencias[l])
                        {
                            if ((tareaTMP->borrado == 0) && (tareaTMP->estado == 0))
                            {
                                ndep++;
                            }
                        }
                        
                        tareaTMP = tareaTMP->siguiente;
                    }
                    
                    l++;
                }
                
                if (ndep == 0)
                {
                    tarea->estado = 1; // Marcamos la tarea como terminada
                    
                    printf ("\nLa tarea %i ha sido marcada como terminada.\n", ID);
                    
                    return; // Si ya la encontramos retornamos
                }
                else
                {
                    printf("\nAVISO: ");
                    printRojo("La tarea tiene dependencias sin terminar.\n");
                    return;
                }
            }
            else
            {
                printf("\nAVISO: "); // Si la tarea no pertenece al usuario avisamos
                printRojo("Operación no permitida sobre esta tarea.\n");
                return;
            }
        }
        
        tarea = tarea->siguiente;
    }
    
    printf("\nAVISO: "); // Si la tarea no existe avisamos (si se llega aquí es que no existe)
    printRojo("Tarea no existe.\n");
    return;
}

void transferirTarea (int ID) // Modificamos el PROPIETARIO de la TAREA
{
    char usuarioNuevo[22];
    
    int permitido = 0; // Permisos sobre la tarea (0 = denegado; 1 = permitido)
    
    getchar();
    
    tarea = primero; // Buscamos la tarea empezando por la primera
    while (tarea != NULL)
    {
        if ((tarea->id == ID) && (tarea->borrado == 0)) // Buscamos por ID
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
            
            if (permitido == 1) // Comprobamos los permisos
            {
                
                printf("\n¿A qué usuario o grupo deseas transferirla? ");
                fgets(usuarioNuevo, 22, stdin); // Pedimos el nombre del nuevo propietario
                
                int k;
                for (k = 0; k < strlen(usuarioNuevo); k++)
                {
                    if (usuarioNuevo[k] == '\n')
                    {
                        usuarioNuevo[k] = '\0';
                    }
                }
                
                char confirmacion;
                int salirconfirmar = 0;
                
                do {
                    
                    printf("¿Transferir la tarea a %s (S/N)? ", usuarioNuevo);
                    scanf(" %c", &confirmacion); // Pedimos confirmación
                    
                    if (confirmacion == 'S' || confirmacion == 's')
                    {
                        strcpy(tarea->propietario, usuarioNuevo); // Guardamos el nuevo propietario
                        
                        return; // Volvemos
                    }
                    else if (confirmacion == 'N' || confirmacion == 'n')
                    {
                        return; // Volvemos
                    }
                    else
                    {
                        salirconfirmar = 0;
                    }
                        
                } while (salirconfirmar == 0);
                
                return; // Si ya la encontramos retornamos
            }
            else
            {
                printf("\nAVISO: "); // Si la tarea no pertenece al usuario avisamos
                printRojo("Operación no permitida sobre esta tarea.\n");
                return;
            }
        }
        
        tarea = tarea->siguiente;
    }
    
    printf("\nAVISO: "); // Si la tarea no existe avisamos (si se llega aquí es que no existe)
    printRojo("Tarea no existe.\n");
    return;
}

void modificarDatosTarea (int ID)
{
    int permitido = 0; // Permisos sobre la tarea (0 = denegado; 1 = permitido)
    
    tarea = primero; // Buscamos la tarea (empezando por la primera)
    while (tarea != NULL)
    {
        if ((tarea->id == ID) && (tarea->borrado == 0)) // Buscamos por ID
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
            
            if (permitido == 1) // Comprobamos los permisos
            {
                break; // Una vez encontrada dejamos de buscar (la tendremos en "tarea")
            }
            else
            {
                printf("\nAVISO: "); // Si la tarea no pertenece al usuario avisamos
                printRojo("Operación no permitida sobre esta tarea.\n");
                return;
            }
        }
        
        tarea = tarea->siguiente;
    }
    
    if (tarea == NULL)
    {
        printf("\nAVISO: "); // Si la tarea no existe avisamos (si se llega aquí es que no existe)
        printRojo("Tarea no existe.\n");
        getchar();
        return;
    }
    
    
    int modificar = -1; // Qué modificar ?
    
    printf("\n");
    printf("1) Descripción\n");
    printf("2) Prioridad\n");
    printf("3) Plazo\n");
    printf("4) Dependencias\n");
    printf("0) Cancelar\n");
    
    do{
        
        printf("¿Qué parámetro desea modificar? ");
        fflush(stdin);
        scanf(" %i", &modificar); // Obtener lo que se quiere modificar
        
        if (modificar == 0) return;
        
    } while((modificar < 0) || (modificar > 4)); // Repetir hasta obtener una respuesta correcta
    
    
    printf("\n");
    
    
    int k;
    getchar();
    
    if (modificar == 1) // Modificar la DESCRIPCIÓN
    {
        char nuevoDato[52];
        
        printf("Antigua descripción: %s\n", tarea->descripcion); // Pedimos nuevo dato
        printf("Nueva descripción: ");
        fgets(nuevoDato, 52, stdin);
        
        for (k = 0; k < strlen(nuevoDato); k++)
        {
            if (nuevoDato[k] == '\n')
            {
                nuevoDato[k] = '\0';
            }
        }
        
        if (comprobarNombre(nuevoDato) != 1) // Vemos si es correcto
        {
            printf("\nAVISO: ");
            printRojo("El nombre ya está en uso.\n");
            return;
        }
        
        strcpy(tarea->descripcion, nuevoDato); // Lo guardamos
        
    }
    else if (modificar == 2) // Modificar la PRIORIDAD
    {
        char nuevoDato[50];
        
        printf("Antigua prioridad: %i\n", tarea->prioridad); // Pedimos nuevo dato
        printf("Nueva prioridad: ");
        fgets(nuevoDato, 52, stdin);
        
        if (atoi(nuevoDato) < 1 || atoi(nuevoDato) > 10) // Lo comprobamos
        {
            printf("\nAVISO: ");
            printRojo("La prioridad debe de estar entre 1 y 10.\n");
            return;
        }
        
        tarea->prioridad = atoi(nuevoDato); // Lo guardamos
        
    }
    else if (modificar == 3) // Modificar el PLAZO
    {
        char nuevoDato[18]; // Pedimos el nuevo dato
        
        if (tarea->tipo == 0)
        {
            printf("Antiguo plazo: 'tarea simple (se convertirá a con_plazo)'\n");
        }
        else if (tarea->tipo == 1)
        {
            printf("Antiguo plazo: %s\n", tarea->fecha);
        }
        
        printf("Nuevo plazo: ");
        fgets(nuevoDato, 18, stdin);
        
        for (k = 0; k < strlen(nuevoDato); k++)
        {
            if (nuevoDato[k] == '\n')
            {
                nuevoDato[k] = '\0';
            }
        }
        
        if (comprobarFecha(nuevoDato) != 1) // Lo comprobamos
        {
            printf("\nAVISO: ");
            printRojo("La fecha debe de ser posterior a la actual (+7 días).\n");
            return;
        }
        
        strcpy(tarea->fecha, nuevoDato); // Lo guardamos
        tarea->tipo = 1;
        
    }
    else if (modificar == 4) // Modificar las dependencias
    {
        char nuevoDato[1000]; // Pedimos nuevo dato
        
        printf("Antiguas dependencias: ");
        for (k = 0; tarea->dependencias[k] != 0; k++)
        {
            printf("%i ", tarea->dependencias[k]);
        }
        if (tarea->dependencias[0] == 0) printf(" - ");
        printf("\n");
        
        printf("Nuevas dependencias (0 si no hay - separadas por comas): ");
        fgets(nuevoDato, 1000, stdin);
        
        int *antiguasDependencias;
        antiguasDependencias = tarea->dependencias; // Salvaguardamos las antiguas
        

        
        char tmpDeps[32][32];
        
        if (strcmp(nuevoDato, "0\n")) // Separamos las dependencias
        {
            int j, k, l, m = 0;
            for (j = 0, k = 0, l = 0; j < 1000; j++,l++)
            {
                if (nuevoDato[j] == '\n' || nuevoDato[j] == '\0')
                {
                    break;
                }
                else if (nuevoDato[j] == ',')
                {
                    k++;
                    l = -1;
                    m++;
                }
                else
                {
                    tmpDeps[k][l] = nuevoDato[j];
                    tmpDeps[k][l+1] = '\0';
                }
            }
            m++;
            tarea->dependencias = (int *)calloc(m+1, sizeof(int));
            for (j = 0; j < m; j++)
            {
                tarea->dependencias[j] = atoi(tmpDeps[j]);
            }
            tarea->dependencias[m] = 0;
        }
        else
        {
            tarea->dependencias = (int *)calloc(1, sizeof(int)); // Las guardamos
            tarea->dependencias[0] = 0;
        }
        
        if (comprobarDependencias() != 1) // Comprobamos las dependencias
        {
            tarea->dependencias = antiguasDependencias; // En caso de incorrectas recuperamos las antiguas
            
            printf("\nAVISO: ");
            printRojo("Alguna dependencia es incorrecta.\n");
            return;
        }
    }
}