//
//  agenda_tareas_lista.c
//  Agenda 2
//
//  Created by Xoán Carlos Cosmed Peralejo.
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

void VerLista ()
{
    if (primero == NULL)
    {
        printf("AVISO: ");
        printRojo("Lista de tareas vacía.\n");
        
        printf("\nPulsar ENTER para volver al menú principal del programa:"); // Salir
        while (getchar()!='\n') {}
        return;
    }
    
    
    
    int opc; // Opción elegida
    char resp[15]; // Respuesta del usuario (de la que se saca "opc")
    
    int tipo = -2; // Qué tareas presentar (0 = todas; 1 = pendientes; 2 = terminadas)
    int forma = -2; // De qué forma presentar (0 = pantalla; 1 = archivo)
    int orden = -2; // En qué orden presentar (0 = sin orden; 1 = prioridad decreciente; 2 = plazo creciente)
    
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
        printf("1) Sin ordenación\n");
        printf("2) Por prioridad descendente\n");
        printf("3) Por plazo ascendente\n");
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
                orden = 1;
                break;
                
            case 2:
                orden = 2;
                break;
                
            case 3:
                orden = 3;
                break;
                
            case 0:
                orden = -1;
                break;
                
            default:
                orden = -2;
                break;
        }
        
    } while (orden == -2); // Repetir hasta obtener una respuesta correcta
    
    if (orden == -1) return; // Si se cancela, vuelvo al menú
    
    do{
        
        printf("\n");
        printf("1) Por pantalla\n");
        printf("2) A archivo\n");
        printf("0) Cancelar\n");
        printf("¿Presentación de resultado? ");
        fflush(stdin);
        
        fgets(resp, 15, stdin); // Obtener la forma de presentarlo
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
            listaTodas(forma, orden); // Mostrar todas
            break;
            
        case 1:
            listaPendientes(forma, orden); // Mostrar pendientes
            break;
            
        case 2:
            listaTerminadas(forma, orden); // Mostrar terminadas
            break;
            
        default:
            break;
    }
}


///// FUNCIONES SECUNDARIAS //////


void listaTodas (int forma, int orden) // Lista de TODAS las tareas
{
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
    
    
    int cont = 0; // Contador
    
    int permitido = 0; // Permisos sobre la(s) tarea(s) (0 = denegado; 1 = permitido)
    
    tarea = primero; // Empezaremos por la primera tarea
    while (tarea != NULL)
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
        
        if ((permitido == 1) && (tarea->borrado == 0))
        {
            cont++; // Primero contamos el número de tareas que posee el usuario
        }
        
        permitido = 0;
        tarea = tarea->siguiente;
    }
    
    if (cont == 0) // Si no hay tareas a mostrar doy un aviso
    {
        printf("\nAVISO: ");
        printRojo("El usuario no tiene tareas de ese tipo o no tiene tareas.\n\n");
        
        printf("Pulsa ENTER para volver al menú principal del programa: ");
        
        if (forma == 1)
        {
            fclose(archivo);
        }
        
        while (getchar()!='\n') {}
        return;
    }
    else
    {
        cont++;
    }
    
    if (orden == 1) // SIN ORDEN
    {
        permitido = 0;
        tarea = primero;
        while (tarea != NULL) // Mostramos TAREAS hasta que no haya más
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
            
            if ((permitido == 1) && (tarea->borrado == 0)) // Comprobamos el usuario y borrado
            {
                fprintf(archivo, "ID: %i\n", tarea->id); // Imprimimos los datos
                fprintf(archivo, "Descripción: %s\n\n", tarea->descripcion);
            }
            
            permitido = 0;
            tarea = tarea->siguiente; // La nueva tarea será la siguiente a la actual
        }
    }
    else if (orden == 2 || orden == 3) // CON ORDEN
    {
        int *ids = (int *)calloc(cont, sizeof(int));
        int *prioridades = (int *)calloc(cont, sizeof(int));
        time_t *plazos = (time_t *)calloc(cont, sizeof(time_t));
        
        int i = 0;
        permitido = 0;
        tarea = primero;
        while (tarea != NULL)
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
            
            if ((permitido == 1) && (tarea->borrado == 0))
            {
                ids[i] = tarea->id; // Guardamos las IDs de esas tareas en un vector
                
                prioridades[i] = tarea->prioridad; // Guardamos también los parametros de ordenación
                plazos[i] = obtenerTiempo(tarea->fecha); // En el caso del plazo primero convertimos
            }
            
            i++;
            permitido = 0;
            tarea = tarea->siguiente;
        }
        
        if (orden == 2) // Ordenamos por prioridad de manera descendente
        {
            ordenPrioridadD(prioridades, ids, cont);
        }
        else if (orden == 3) // Ordenamos por plazo de manera ascendente
        {
            ordenPlazoA(plazos, ids, cont);
        }
        
        for (i = 0; i < cont; i++) // Imprimimos de manera ordenada
        {
            tarea = primero;
            while (tarea != NULL)
            {
                if (tarea->id == ids[i])
                {
                    fprintf(archivo, "ID: %i\n", tarea->id); // Imprimimos los datos
                    fprintf(archivo, "Descripción: %s\n", tarea->descripcion);
                    
                    if (orden == 2)
                    {
                        fprintf(archivo, "Prioridad: %i\n\n", tarea->prioridad);
                    }
                    else if (orden == 3)
                    {
                        fprintf(archivo, "Plazo: %s\n\n", tarea->fecha);
                    }
                    
                    break;
                }
                
                tarea = tarea->siguiente;
            }
        }
        
        free(ids);
        free(prioridades);
        free(plazos);
    }
    else
    {
        printf("\n\tERROR al detectar el orden\t\n");
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


void listaPendientes (int forma, int orden) // Lista de las tareas PENDIENTES
{
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
    
    
    int cont = 0; // Contador
    
    int permitido = 0; // Permisos sobre la(s) tarea(s) (0 = denegado; 1 = permitido)
    
    tarea = primero; // Empezaremos por la primera tarea
    while (tarea != NULL)
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
        
        if ((permitido == 1) && (tarea->estado == 0) && (tarea->borrado == 0))
        {
            cont++; // Primero contamos el número de tareas que posee el usuario
        }
        
        permitido = 0;
        tarea = tarea->siguiente;
    }
    
    if (cont == 0) // Si no hay tareas a mostrar doy un aviso
    {
        printf("\nAVISO: ");
        printRojo("El usuario no tiene tareas de ese tipo o no tiene tareas.\n\n");
        
        printf("Pulsa ENTER para volver al menú principal del programa: ");
        
        if (forma == 1)
        {
            fclose(archivo);
        }
        
        while (getchar()!='\n') {}
        return;
    }
    else
    {
        cont++;
    }
    
    if (orden == 1) // SIN ORDEN
    {
        permitido = 0;
        tarea = primero;
        while (tarea != NULL) // Mostramos TAREAS hasta que no haya más
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
            
            if ((permitido == 1) && (tarea->estado == 0) && (tarea->borrado == 0)) // Comprobamos los permisos, estado y borrado
            {
                fprintf(archivo, "ID: %i\n", tarea->id); // Imprimimos los datos
                fprintf(archivo, "Descripción: %s\n\n", tarea->descripcion);
            }
            
            permitido = 0;
            tarea = tarea->siguiente; // La nueva tarea será la siguiente a la actual
        }
    }
    else if (orden == 2 || orden == 3) // CON ORDEN
    {
        int *ids = (int *)calloc(cont, sizeof(int));
        int *prioridades = (int *)calloc(cont, sizeof(int));
        time_t *plazos = (time_t *)calloc(cont, sizeof(time_t));
        
        int i = 0;
        permitido = 0;
        tarea = primero;
        while (tarea != NULL)
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
            
            if ((permitido == 1) && (tarea->estado == 0) && (tarea->borrado == 0))
            {
                ids[i] = tarea->id; // Guardamos las IDs de esas tareas en un vector
                
                prioridades[i] = tarea->prioridad; // Guardamos también los parametros de ordenación
                plazos[i] = obtenerTiempo(tarea->fecha); // En el caso del plazo primero convertimos
            }
            
            i++;
            permitido = 0;
            tarea = tarea->siguiente;
        }
        
        if (orden == 2) // Ordenamos por prioridad de manera descendente
        {
            ordenPrioridadD(prioridades, ids, cont);
        }
        else if (orden == 3) // Ordenamos por plazo de manera ascendente
        {
            ordenPlazoA(plazos, ids, cont);
        }
        
        for (i = 0; i < cont; i++) // Imprimimos de manera ordenada
        {
            tarea = primero;
            while (tarea != NULL)
            {
                if (tarea->id == ids[i])
                {
                    fprintf(archivo, "ID: %i\n", tarea->id); // Imprimimos los datos
                    fprintf(archivo, "Descripción: %s\n", tarea->descripcion);
                    
                    if (orden == 2)
                    {
                        fprintf(archivo, "Prioridad: %i\n\n", tarea->prioridad);
                    }
                    else if (orden == 3)
                    {
                        fprintf(archivo, "Plazo: %s\n\n", tarea->fecha);
                    }
                    
                    break;
                }
                
                tarea = tarea->siguiente;
            }
        }
        
        free(ids);
        free(prioridades);
        free(plazos);
    }
    else
    {
        printf("\n\tERROR al detectar el orden\t\n");
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


void listaTerminadas (int forma, int orden) // Lista de las tareas TERMINADAS
{
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
    
    int permitido = 0; // Permisos sobre la(s) tarea(s) (0 = denegado; 1 = permitido)
    
    tarea = primero; // Empezaremos por la primera tarea
    while (tarea != NULL)
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
        
        if ((permitido == 1) && (tarea->estado == 1) && (tarea->borrado == 0))
        {
            cont++; // Primero contamos el número de tareas que posee el usuario
        }
        
        permitido = 0;
        tarea = tarea->siguiente;
    }
    
    if (cont == 0) // Si no hay tareas a mostrar doy un aviso
    {
        printf("\nAVISO: ");
        printRojo("El usuario no tiene tareas de ese tipo o no tiene tareas.\n\n");
        
        printf("Pulsa ENTER para volver al menú principal del programa: ");
        
        if (forma == 1)
        {
            fclose(archivo);
        }
        
        while (getchar()!='\n') {}
        return;
    }
    else
    {
        cont++;
    }
    
    if (orden == 1) // SIN ORDEN
    {
        permitido = 0;
        tarea = primero;
        while (tarea != NULL) // Mostramos TAREAS hasta que no haya más
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
            
            
            if ((permitido == 1) && (tarea->estado == 1) && (tarea->borrado == 0)) // Comprobamos los permisos, estado y borrado
            {
                fprintf(archivo, "ID: %i\n", tarea->id); // Imprimimos los datos
                fprintf(archivo, "Descripción: %s\n\n", tarea->descripcion);
            }
            
            permitido = 0;
            tarea = tarea->siguiente; // La nueva tarea será la siguiente a la actual
        }
    }
    else if (orden == 2 || orden == 3) // CON ORDEN
    {
        int *ids = (int *)calloc(cont, sizeof(int));
        int *prioridades = (int *)calloc(cont, sizeof(int));
        time_t *plazos = (time_t *)calloc(cont, sizeof(time_t));
        
        int i = 0;
        permitido = 0;
        tarea = primero;
        while (tarea != NULL)
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
            
            if ((permitido == 1) && (tarea->estado == 1) && (tarea->borrado == 0))
            {
                ids[i] = tarea->id; // Guardamos las IDs de esas tareas en un vector
                
                prioridades[i] = tarea->prioridad; // Guardamos también los parametros de ordenación
                plazos[i] = obtenerTiempo(tarea->fecha); // En el caso del plazo primero convertimos
            }
            
            i++;
            permitido = 0;
            tarea = tarea->siguiente;
        }
        
        if (orden == 2) // Ordenamos por prioridad de manera descendente
        {
            ordenPrioridadD(prioridades, ids, cont);
        }
        else if (orden == 3) // Ordenamos por plazo de manera ascendente
        {
            ordenPlazoA(plazos, ids, cont);
        }
        
        for (i = 0; i < cont; i++) // Imprimimos de manera ordenada
        {
            tarea = primero;
            while (tarea != NULL)
            {
                if (tarea->id == ids[i])
                {
                    fprintf(archivo, "ID: %i\n", tarea->id); // Imprimimos los datos
                    fprintf(archivo, "Descripción: %s\n", tarea->descripcion);
                    
                    if (orden == 2)
                    {
                        fprintf(archivo, "Prioridad: %i\n\n", tarea->prioridad);
                    }
                    else if (orden == 3)
                    {
                        fprintf(archivo, "Plazo: %s\n\n", tarea->fecha);
                    }
                    
                    break;
                }
                
                tarea = tarea->siguiente;
            }
        }
        
        free(ids);
        free(prioridades);
        free(plazos);
    }
    else
    {
        printf("\n\tERROR al detectar el orden\t\n");
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


///// FUNCIONES TERCIARIAS /////

void ordenPrioridadD (int *prioridades, int *ids, int elem) // Ordenamos las IDs por PRIORIDAD (decreciente)
{
    int aux1, aux2;
    int i, j;
    
    for (i = 0; i < elem; i++) // Usamos el argoritmo de la burbuja a la vez en ambos vectores
    {
        for (j = elem - 1; j > i; j--)
        {
            if (prioridades[j] < prioridades[j-1])
            {
                aux1 = prioridades[j];
                aux2 = ids[j];
                
                prioridades[j] = prioridades[j-1];
                ids[j] = ids[j-1];
                
                prioridades[j-1] = aux1;
                ids[j-1] = aux2;
            }
        }
    }
    
    int ids2[elem]; // Copiamos las IDs ordenadas en orden inverso en otro vector
    for (i = 0; i < elem; i++)
    {
        ids2[i] = ids[i];
    }
    
    for (i = 0, j = elem; i < elem; i++, j--) // Invertimos el orden del vector
    {
        ids[i] = ids2[j];
    }
}

void ordenPlazoA (time_t *plazos, int *ids, int elem) // Ordenamos las IDs por PLAZO (ascendente)
{
    time_t aux1;
    int aux2;
    int i, j;
    
    for (i = 0; i < elem; i++) // Usamos el argoritmo de la burbuja a la vez en ambos vectores
    {
        for (j = elem - 1; j > i; j--)
        {
            if (plazos[j] < plazos[j-1])
            {
                aux1 = plazos[j];
                aux2 = ids[j];
                
                plazos[j] = plazos[j-1];
                ids[j] = ids[j-1];
                
                plazos[j-1] = aux1;
                ids[j-1] = aux2;
            }
        }
    }
}

time_t obtenerTiempo (char fecha[25]) // Convertimos la FECHA en TIEMPO desde la Época Unix
{
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
    
    return fechaU;
}