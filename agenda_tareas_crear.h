//
//  agenda_tareas_crear.h
//  Agenda 2
//
//  Created by Xoán Carlos Cosmed Peralejo.
//

#ifndef __Agenda_2__tareas_crear__
#define __Agenda_2__tareas_crear__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "agenda_pantalla.h"

int comprobarFecha(char fecha[25]); // Funciones secundarias
int comprobarNombre(char nombre[55]);
int comprobarDependencias();
int obtenerID();

void CrearTarea(); // Función principal

#endif /* defined(__Agenda_2__tareas_crear__) */