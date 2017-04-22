//
//  agenda_tareas_crear.c
//  Agenda 2
//
//  Created by Xoán Carlos Cosmed Peralejo.
//

#include "agenda_tareas_crear.h"

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

void CrearTarea ()
{
    int k; // Declaramos un contador
    tarea = (TareaS *)calloc(1, sizeof(TareaS)); // Reservamos memoria para la nueva tarea
    if (tarea == NULL) printf("Error al reservar memoria");
    
    
    int errores[4]; // Creamos un array para almacenar los errores y avisos (1 si hay error)
    errores[0] = 0; // 0 -> Tarea ya existente
    errores[1] = 0; // 1 -> Fecha anterior a la actual
    errores[2] = 0; // 2 -> Alguna dependencia es incorrecta
    errores[3] = 0; // 3 -> Prioridad incorrecta
    
    
    char tmpS[100]; // Variables temporales
    char tmpDep[1000];
    char tmpDeps[100][10];
    
    printf("\n");
    
    printf("Introducir los datos de la nueva tarea: \n\n");
    fflush(stdin);
    setbuf(stdin, NULL);
    //getchar();
    
    printf("Introducir tipo de tarea: "); // Preguntamos por el tipo de la tarea
    fgets(tmpS, 100, stdin);
    fflush(stdin);
    setbuf(stdin, NULL);
    
    if (!strcmp(tmpS, "simple\n")) // SI ES SIMPLE ...
    {
        tarea->tipo = 0; // El tipo es simple (0)
        
        printf("Introducir descripción de la tarea: "); // Pedimos la descripción de la tarea
        fgets(tmpS, 100, stdin);
        fflush(stdin);
        setbuf(stdin, NULL);
        for (k = 0; k < strlen(tmpS); k++)
        {
            if (tmpS[k] == '\n')
            {
                tmpS[k] = '\0';
            }
        }
        strcpy(tarea->descripcion, tmpS);
        if (comprobarNombre(tarea->descripcion) != 1) errores[0] = 1; // Comprobamos el nombre
        
        printf("Introducir prioridad: "); // Pedimos la prioridad
        fgets(tmpS, 100, stdin);
        fflush(stdin);
        setbuf(stdin, NULL);
        tarea->prioridad = atoi(tmpS);
        if (tarea->prioridad > 10 || tarea->prioridad < 0) errores[3] = 1; // Comprobamos la prioridad
        
        strcpy(tarea->fecha, "-");
        
    }
    else if (!strcmp(tmpS, "con_plazo\n")) // SI ES CON PLAZO ...
    {
        tarea->tipo = 1; // El tipo de tarea es con plazo (1)
        
        printf("Introducir plazo: "); // Pedimos el plazo (fecha)
        fgets(tmpS, 100, stdin);
        fflush(stdin);
        setbuf(stdin, NULL);
        for (k = 0; k < strlen(tmpS); k++)
        {
            if (tmpS[k] == '\n')
            {
                tmpS[k] = '\0';
            }
        }
        strcpy(tarea->fecha, tmpS);
        if (comprobarFecha(tarea->fecha) != 1) errores[1] = 1; // Comprobamos la fecha

        
        printf("Introducir descripción de la tarea: "); // Pedimos la descripción de la tarea
        fgets(tmpS, 100, stdin);
        fflush(stdin);
        setbuf(stdin, NULL);
        for (k = 0; k < strlen(tmpS); k++)
        {
            if (tmpS[k] == '\n')
            {
                tmpS[k] = '\0';
            }
        }
        strcpy(tarea->descripcion, tmpS);
        if (comprobarNombre(tarea->descripcion) != 1) errores[0] = 1; // Comprobamos el nombre
        
        printf("Introducir prioridad: "); // Pedimos la prioridad
        fgets(tmpS, 100, stdin);
        fflush(stdin);
        setbuf(stdin, NULL);
        tarea->prioridad = atoi(tmpS);
        if (tarea->prioridad > 10 || tarea->prioridad < 1) errores[3] = 1; // Comprobamos la prioridad
        
    }
    else // TIPO de tarea incorrecta
    {
        printf("\nAviso: ");
        printRojo("Tipo de tarea incorrecto (simple o con_plazo).\n");
        printf("\nPulsa ENTER para volver al menú principal del programa: ");
        while (getchar()!='\n') {}
        free(tarea);
        return;
    }
    
    
    if (primero != NULL)
    {
        printf("Introducir dependencias (0 si no se establecen dependencias): "); // Pedimos las dependencias
        fgets(tmpDep, 1000, stdin);
        fflush(stdin);
        setbuf(stdin, NULL);
        
        
        if (strcmp(tmpDep, "0\n")) // Separamos las dependencias
        {
            int j, k, l, m = 0;
            for (j = 0, k = 0, l = 0; j < 1000; j++,l++)
            {
                if (tmpDep[j] == '\n' || tmpDep[j] == '\0')
                {
                    break;
                }
                else if (tmpDep[j] == ',')
                {
                    k++;
                    l = -1;
                    m++;
                }
                else
                {
                    tmpDeps[k][l] = tmpDep[j];
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
            tarea->dependencias = (int *)calloc(1, sizeof(int));
            tarea->dependencias[0] = 0;
        }
        
        if (comprobarDependencias() != 1) errores[2] = 1; // Comprobamos las dependencias
    }
    else
    {
        printf("\nAviso: ");
        printRojo("Primera tarea de la lista de tareas. Por defecto no se establecen dependencias.\n");
        
        printf("\nPulsar cualquier caracter ALFANUMÉRICO (salvo ñ o Ñ) para que ");
        printAzul("continúe la creación ");
        printf("del nuevo nodo: ");
        while (isalpha(getchar()) == 0) {}
        getchar();
        
        tarea->dependencias = (int *)calloc(1, sizeof(int));
        tarea->dependencias[0] = 0;
    }
   
    tarea->estado = 0; // El valor inical para el estado de la tarea será 0 (pendiente)
    
    
    tarea->id = obtenerID(); // Obtenemos un ID para la nueva tarea
    
    
    if (primerG == NULL) // Si no hay grupos ...
    {
        strcpy(tarea->propietario, usuario); // La nueva tarea pertenecerá al usuario actual
    }
    else // Si hay grupos ...
    {
        int cont = 1; // Contador
        int Ngrupo; // Número de grupo (en formato int y char)
        char NgrupoS[10];
        
        grupo = primerG;
        while (grupo != NULL)
        {
            printf("\n\t%i) %s", cont++, grupo->nombre);
            
            grupo = grupo->siguiente;
        }
        
        cont--;
        
        printf("\n\t0) Ningún grupo de usuario\n");
        
        do {
            
            printf("\n¿A qué grupo de usuarios desea que pertenezca la tarea? ");
            fgets(NgrupoS, 10, stdin); // Preguntamos por el grupo en el que guardar
            Ngrupo = atoi(NgrupoS);
            
        } while (Ngrupo < 0 && Ngrupo > cont);
        
        if (Ngrupo == 0) // Si se seleccionó 0 ...
        {
            strcpy(tarea->propietario, usuario); // Se crea en el usuario
        }
        else // Si se seleccionó otra opción ...
        {
            grupo = primerG;
            
            int i;
            for (i = 1; i <= cont; i++)
            {
                if (i == Ngrupo)
                {
                    strcpy(tarea->propietario, grupo->nombre); // Se crea en el grupo elegido
                }
                    
                grupo = grupo->siguiente;
            }
        }
    }

    
    fflush(stdin); // Limpiar la caché del teclado
    setbuf(stdin, NULL);
    
    
    if (errores[0] == 1) // AVISOS
    {
        printf("\nAviso: ");
        printRojo("Tarea ya existente.\n");
        printf("\nPulsa ENTER para volver al menú principal del programa: ");
        while (getchar()!='\n') {}
        free(tarea);
        return;
    }
    else if (errores[1] == 1)
    {
        printf("\nAviso: ");
        printRojo("La fecha debe de ser posterior a la actual (+7 días).\n");
        printf("\nPulsa ENTER para volver al menú principal del programa: ");
        while (getchar()!='\n') {}
        free(tarea);
        return;
    }
    else if (errores[2] == 1)
    {
        printf("\nAviso: ");
        printRojo("Algunas de las dependencias indicadas es incorrecta.\n");
        printf("\nPulsa ENTER para volver al menú principal del programa: ");
        while (getchar()!='\n') {}
        free(tarea);
        return;
    }
    else if (errores[3] == 1)
    {
        printf("\nError: ");
        printRojo("La prioridad es incorrecta (rango de 0 a 10).\n");
        printf("\nPulsa ENTER para volver al menú principal del programa: ");
        while (getchar()!='\n') {}
        free(tarea);
        return;
    }
    
    
    tarea->borrado = 0; // Por defecto no está borrada
    
    
    // GUARDAMOS la tarea en la lista
    
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
    
    tareas_num++; // Aumentamos en 1 el número de tareas
    
    printf("\nLa tarea se creó correctamente con el ID %i.\n", tarea->id);
    
    printf("\nPulsar ENTER para volver al menú principal del programa: ");
    while (getchar()!='\n') {}
    return;
}



///// FUNCIONES SECUNDARIAS //////


int comprobarFecha (char fecha[25]) // Función para ANALIZAR LA FECHA
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
    fechaS = (Tm *)calloc(1, sizeof(Tm)); // Ahí metemos las compenentes de la fecha convertidos a int
    
    fechaS->tm_mday = atoi(fechaP[0]) - 7; // Ponemos 7 días de margen por especificación del proyecto
    fechaS->tm_mon = atoi(fechaP[1])-1;
    fechaS->tm_year = atoi(fechaP[2])-1900;
    fechaS->tm_hour = atoi(fechaP[3]);
    fechaS->tm_min = atoi(fechaP[4]);
    fechaS->tm_isdst = 1; // Activamos el horario de verano
    
    time_t fechaU = mktime(fechaS); // Convertimos la fecha en segundos después de la época Unix (estandar)
    time_t fechaA = time(NULL); // Obtenemos la fecha actual en segundos desde la época Unix
    
    if(fechaA >= fechaU)
    {
        return -1; // Si la fecha actual es mayor retornamos -1
    }
    else if (fechaA < fechaU)
    {
        return 1; // Si la fecha actual es menor retornamos 1
    }
    
    return 0;
}


int comprobarNombre (char nombre[55]) // COMPROBAR que el NOMBRE de la tarea esté disponible
{
    TareaS *tareaTMP = primero; // Creamos un puntero a la primera tarea
    
    while (tareaTMP != NULL) // Comprobaremos hasta la última tarea
    {
        if(!strcmp(nombre, tareaTMP->descripcion))
        {
            return -1; // Si el nombre no está disponible retornamos -1
        }
        
        tareaTMP = tareaTMP->siguiente; // La nueva tarea será la siguiente a la actual
    }
    
    return 1; // Si el nombre está disponible retornamos 1
}


int comprobarDependencias () // COMPROBAR que las DEPENDENCIAS existan
{
    TareaS *tareaTMP;
    
    int i, j = 0, k = 0;
    for (i = 0; tarea->dependencias[i] != 0; i++) // Comparamos cada dependencia con todas las IDs
    {
        tareaTMP = primero;
        while (tareaTMP != NULL)
        {
            if (tareaTMP->id == tarea->dependencias[i])
            {
                j = 1;
                break;
            }
            
            tareaTMP = tareaTMP->siguiente;
        }
        
        if (j != 1)
        {
            k--;
        }
        j = 0;
    }
    
    if (k == 0)
    {
        return 1; // Si cada dependencia coincide con una ID las dependencias están bien
    }
    else
    {
        return k;
    }
    
    return 0;
}

int obtenerID () // OBTENER UN ID disponible para la tarea
{
    int ID = 1; // Variable para guardar el ID
    
    TareaS *tareaTMP = primero; // Puntero a la primera tarea
    
    while (tareaTMP != NULL) // Comparamos la nueva ID con las ya existentes y obtenemos una
    {
        if (ID < (tareaTMP->id))
        {
            ID = (tareaTMP->id) + 1;
        }
        else if (ID == (tareaTMP->id))
        {
            ID++;
        }
        
        tareaTMP = tareaTMP->siguiente;
    }
    
    return ID;
}