#ifndef ANALIZADOR_DATOS_H
#define ANALIZADOR_DATOS_H

#include <vector>
#include <string>
#include <map>
#include "persona_cpp.h"

// Funciones para preguntas obligatorias
int calcularEdad(const std::string& fechaNacimiento);
PersonaCpp encontrarPersonaMasLongeva(const std::vector<PersonaCpp>& personas);
std::map<std::string, PersonaCpp> encontrarMasLongevaPorCiudad(const std::vector<PersonaCpp>& personas);
PersonaCpp encontrarPersonaMayorPatrimonio(const std::vector<PersonaCpp>& personas);
std::map<std::string, PersonaCpp> encontrarMasRicaPorCiudad(const std::vector<PersonaCpp>& personas);
std::map<char, PersonaCpp> encontrarMasRicaPorGrupo(const std::vector<PersonaCpp>& personas);
void contarYValidarPorGrupo(const std::vector<PersonaCpp>& personas);

// Funciones para preguntas adicionales
void encontrarCiudadesConMayorPatrimonioPromedio(const std::vector<PersonaCpp>& personas);
void calcularPorcentajeMayores80PorGrupo(const std::vector<PersonaCpp>& personas);

#endif