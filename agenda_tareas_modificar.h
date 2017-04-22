//
//  agenda_tareas_modificar.h
//  Agenda 2
//
//  Created by Xoán Carlos Cosmed Peralejo.
//

#ifndef __Agenda_2__tareas_modificar__
#define __Agenda_2__tareas_modificar__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "agenda_tareas_crear.h"
#include "agenda_pantalla.h"


void terminarTarea (int ID); // Funciones secundarias
void transferirTarea (int ID);
void modificarDatosTarea (int ID);

void ModificarTarea (); // Función principal

#endif /* defined(__Agenda_2__tareas_modificar__) */
