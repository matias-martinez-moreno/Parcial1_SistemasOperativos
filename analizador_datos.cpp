#include <iostream>
#include <vector>
#include <limits>
#include <map>
#include <algorithm>
#include "analizador_datos.h"

// --- Implementación de Funciones ---

int calcularEdad(const std::string& fechaNacimiento) {
    if (fechaNacimiento.length() < 4) return 0;
    try {
        return 2025 - std::stoi(fechaNacimiento.substr(0, 4));
    } catch (const std::exception& e) {
        return 0;
    }
}

PersonaCpp encontrarPersonaMasLongeva(const std::vector<PersonaCpp>& personas) {
    if (personas.empty()) return PersonaCpp();
    PersonaCpp masLongeva = personas[0];
    int maxEdad = 0;
    for (const auto& p : personas) {
        int edadActual = calcularEdad(p.fechaNacimiento);
        if (edadActual > maxEdad) {
            maxEdad = edadActual;
            masLongeva = p;
        }
    }
    return masLongeva;
}

std::map<std::string, PersonaCpp> encontrarMasLongevaPorCiudad(const std::vector<PersonaCpp>& personas) {
    std::map<std::string, PersonaCpp> masLongevaPorCiudad;
    std::map<std::string, int> maxEdadPorCiudad;
    for (const auto& p : personas) {
        int edadActual = calcularEdad(p.fechaNacimiento);
        // Si la ciudad no existe en el mapa, maxEdadPorCiudad[p.ciudadResidencia] será 0 por defecto.
        if (edadActual > maxEdadPorCiudad[p.ciudadResidencia]) {
            maxEdadPorCiudad[p.ciudadResidencia] = edadActual;
            masLongevaPorCiudad[p.ciudadResidencia] = p;
        }
    }
    return masLongevaPorCiudad;
}

PersonaCpp encontrarPersonaMayorPatrimonio(const std::vector<PersonaCpp>& personas) {
    if (personas.empty()) return PersonaCpp();
    PersonaCpp masRica = personas[0];
    long long maxPatrimonioNeto = std::numeric_limits<long long>::min();
    for (const auto& p : personas) {
        long long patrimonioNeto = p.patrimonio - p.deudas;
        if (patrimonioNeto > maxPatrimonioNeto) {
            maxPatrimonioNeto = patrimonioNeto;
            masRica = p;
        }
    }
    return masRica;
}

std::map<std::string, PersonaCpp> encontrarMasRicaPorCiudad(const std::vector<PersonaCpp>& personas) {
    std::map<std::string, PersonaCpp> masRicaPorCiudad;
    std::map<std::string, long long> maxPatrimonioPorCiudad;
     for (const auto& p : personas) {
        long long patrimonioNeto = p.patrimonio - p.deudas;
        // Si la ciudad no existe, maxPatrimonioPorCiudad[p.ciudadResidencia] será 0 por defecto.
        if (patrimonioNeto > maxPatrimonioPorCiudad[p.ciudadResidencia]) {
            maxPatrimonioPorCiudad[p.ciudadResidencia] = patrimonioNeto;
            masRicaPorCiudad[p.ciudadResidencia] = p;
        }
    }
    return masRicaPorCiudad;
}

std::map<char, PersonaCpp> encontrarMasRicaPorGrupo(const std::vector<PersonaCpp>& personas) {
    std::map<char, PersonaCpp> masRicaPorGrupo;
    std::map<char, long long> maxPatrimonioPorGrupo;
    for (const auto& p : personas) {
        long long patrimonioNeto = p.patrimonio - p.deudas;
        if (patrimonioNeto > maxPatrimonioPorGrupo[p.grupoDeclaracion]) {
            maxPatrimonioPorGrupo[p.grupoDeclaracion] = patrimonioNeto;
            masRicaPorGrupo[p.grupoDeclaracion] = p;
        }
    }
    return masRicaPorGrupo;
}

void contarYValidarPorGrupo(const std::vector<PersonaCpp>& personas) {
    std::map<char, int> conteo;
    int validacionesIncorrectas = 0;
    for (const auto& p : personas) {
        conteo[p.grupoDeclaracion]++;
        int ultimosDosDigitos = p.documentoIdentidad % 100;
        char grupoCorrecto = (ultimosDosDigitos <= 39) ? 'A' : (ultimosDosDigitos <= 79) ? 'B' : 'C';
        if (p.grupoDeclaracion != grupoCorrecto) {
            validacionesIncorrectas++;
        }
    }
    std::cout << "\n--- Conteo y Validación por Grupo de Declaración ---" << std::endl;
    for (auto const& [grupo, cantidad] : conteo) {
        std::cout << "Grupo " << grupo << ": " << cantidad << " personas." << std::endl;
    }
    // La validación es 0 porque nuestro generador es perfecto, pero la lógica está aquí.
    std::cout << "Validaciones de grupo incorrectas: " << validacionesIncorrectas << std::endl;
}

void encontrarCiudadesConMayorPatrimonioPromedio(const std::vector<PersonaCpp>& personas) {
    std::map<std::string, std::pair<long long, int>> datosPorCiudad;
    for (const auto& p : personas) {
        datosPorCiudad[p.ciudadResidencia].first += (p.patrimonio - p.deudas);
        datosPorCiudad[p.ciudadResidencia].second++;
    }
    std::vector<std::pair<std::string, double>> promedios;
    for (auto const& [ciudad, datos] : datosPorCiudad) {
        if (datos.second > 0) {
            promedios.push_back({ciudad, (double)datos.first / datos.second});
        }
    }
    std::sort(promedios.begin(), promedios.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    std::cout << "\n--- 5 Ciudades con Mayor Patrimonio Promedio ---" << std::endl;
    for (int i = 0; i < 5 && i < promedios.size(); ++i) {
        std::cout << i + 1 << ". " << promedios[i].first << ": $" << (long long)promedios[i].second << std::endl;
    }
}

void calcularPorcentajeMayores80PorGrupo(const std::vector<PersonaCpp>& personas) {
    std::map<char, int> totalPorGrupo;
    std::map<char, int> mayores80PorGrupo;
    for (const auto& p : personas) {
        totalPorGrupo[p.grupoDeclaracion]++;
        if (calcularEdad(p.fechaNacimiento) >= 80) {
            mayores80PorGrupo[p.grupoDeclaracion]++;
        }
    }
    std::cout << "\n--- Porcentaje de Personas > 80 años por Grupo ---" << std::endl;
    for (auto const& [grupo, total] : totalPorGrupo) {
        double porcentaje = (total > 0) ? (double)mayores80PorGrupo[grupo] * 100.0 / total : 0.0;
        std::cout << "Grupo " << grupo << ": " << porcentaje << "%" << std::endl;
    }
}