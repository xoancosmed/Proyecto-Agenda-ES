//
//  agenda_tareas_ver.h
//  Agenda
//
//  Created by Manuel Castro, Raquel Balboa y Xoan Cosmed.
//

#ifndef __Agenda__tareas_ver__
#define __Agenda__tareas_ver__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "agenda_pantalla.h"


int diasRestantes (char fecha[18]); // Funciones secundarias
void imprimirDependencias1 (int ID);
void imprimirDependencias2 (int ID);

void VerTarea (); // Función principal

#endif /* defined(__Agenda__tareas_ver__) */
