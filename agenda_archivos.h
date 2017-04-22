//
//  agenda_archivos.h
//  Agenda 2
//
//  Created by Xoán Carlos Cosmed Peralejo.
//

#ifndef __Agenda_2__archivos__
#define __Agenda_2__archivos__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "agenda_pantalla.h"



int contarCaractArchivo (char nombre[], char caractBuscar); // Funciones Secundarias
void liberarMemoria ();

void LeerArchivo (); // Leer el archivo para obtener las tareas
void GuardarArchivo (); // Guardar las tareas en el archivo

#endif /* defined(__Agenda_2__archivos__) */
