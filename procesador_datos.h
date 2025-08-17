#ifndef PROCESADOR_DATOS_H
#define PROCESADOR_DATOS_H

#include <vector>
#include <string>
#include "persona_cpp.h"

// funcion que leera el CSV.
std::vector<PersonaCpp> cargarDatos(const std::string& nombreArchivo);

#endif