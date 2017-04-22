//
//  agenda_tareas_lista.h
//  Agenda 2
//
//  Created by Xoán Carlos Cosmed Peralejo.
//

#ifndef __Agenda_2__tareas_lista__
#define __Agenda_2__tareas_lista__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "agenda_pantalla.h"


void ordenPrioridadD (int *prioridades, int *ids, int elem); // Funciones terciarias
void ordenPlazoA (time_t *plazos, int *ids, int elem);
time_t obtenerTiempo (char fecha[25]);

void listaTodas (int forma, int orden); // Funciones secundarias
void listaPendientes (int forma, int orden);
void listaTerminadas (int forma, int orden);

void VerLista (); // Función principal

#endif /* defined(__Agenda_2__tareas_lista__) */
