//
//  agenda_tareas_ver.h
//  Agenda 2
//
//  Created by Xoán Carlos Cosmed Peralejo.
//

#ifndef __Agenda_2__tareas_ver__
#define __Agenda_2__tareas_ver__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "agenda_pantalla.h"


int diasRestantes (char fecha[18]); // Funciones secundarias
void imprimirDependencias1 (int ID);
void imprimirDependencias2 (int ID);

void VerTarea (); // Función principal

#endif /* defined(__Agenda_2__tareas_ver__) */
