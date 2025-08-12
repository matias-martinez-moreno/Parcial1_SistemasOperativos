#ifndef PROCESADOR_DATOS_H
#define PROCESADOR_DATOS_H

#include <vector>
#include <string>
#include "persona_cpp.h"

// Declaración de la función que leerá el CSV.
std::vector<PersonaCpp> cargarDatos(const std::string& nombreArchivo);

#endif