#ifndef ANALIZADOR_DATOS_H
#define ANALIZADOR_DATOS_H
#include <string>
#include <map>
#include <vector>
#include "persona_cpp.h"

// --- Funciones para las preguntas obligatorias ---
int calcularEdad(const std::string& fechaNacimiento);
PersonaCpp encontrarPersonaMasLongeva(const std::vector<PersonaCpp>& personas);
std::map<std::string, PersonaCpp> encontrarMasLongevaPorCiudad(const std::vector<PersonaCpp>& personas);
PersonaCpp encontrarPersonaMayorPatrimonio(const std::vector<PersonaCpp>& personas);
std::map<std::string, PersonaCpp> encontrarMasRicaPorCiudad(const std::vector<PersonaCpp>& personas);
std::map<char, PersonaCpp> encontrarMasRicaPorGrupo(const std::vector<PersonaCpp>& personas);
void contarYValidarPorGrupo(const std::vector<PersonaCpp>& personas);

// --- Funciones para las preguntas creadas por nosotros ---
void calcularPatrimonioTotalPorGrupo(const std::vector<PersonaCpp>& personas);
void encontrarCiudadesConMasDeclarantes(const std::vector<PersonaCpp>& personas);
void calcularEdadPromedioPorGrupo(const std::vector<PersonaCpp>& personas);

#endif