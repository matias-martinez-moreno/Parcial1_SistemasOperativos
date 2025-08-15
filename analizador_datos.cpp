#include <iostream>
#include <vector>
#include <limits>
#include <map>
#include <algorithm>
#include <iomanip> // se usa para std::fixed y std::setprecision
#include "analizador_datos.h"

// --- implementacion de las funciones obligatorias ---

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
    std::cout << "\n--- Conteo y Validacion por Grupo de Declaracion ---" << std::endl;
    for (auto const& [grupo, cantidad] : conteo) {
        std::cout << "Grupo " << grupo << ": " << cantidad << " personas." << std::endl;
    }
}
// --- Implementacion de las tres preguntas Adicionales ---

// Pregunta 1: Distribucion de Riqueza por Grupo
void calcularPatrimonioTotalPorGrupo(const std::vector<PersonaCpp>& personas) {
    std::map<char, long long> patrimonioPorGrupo;
    for (const auto& p : personas) {
        patrimonioPorGrupo[p.grupoDeclaracion] += (p.patrimonio - p.deudas);
    }
    std::cout << "\n--- Patrimonio Neto Total por Grupo ---" << std::endl;
    for (auto const& [grupo, patrimonioTotal] : patrimonioPorGrupo) {
        std::cout << "Grupo " << grupo << ": $" << patrimonioTotal << std::endl;
    }
}

// Pregunta 2: Ciudades con Mayor Cantidad de Declarantes
void encontrarCiudadesConMasDeclarantes(const std::vector<PersonaCpp>& personas) {
    std::map<std::string, int> conteoPorCiudad;
    for (const auto& p : personas) {
        conteoPorCiudad[p.ciudadResidencia]++;
    }
    std::vector<std::pair<std::string, int>> conteoVector;
    for (auto const& [ciudad, conteo] : conteoPorCiudad) {
        conteoVector.push_back({ciudad, conteo});
    }
    std::sort(conteoVector.begin(), conteoVector.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    std::cout << "\n--- 5 Ciudades con Mayor Numero de Declarantes ---" << std::endl;
    for (int i = 0; i < 5 && i < conteoVector.size(); ++i) {
        std::cout << i + 1 << ". " << conteoVector[i].first << ": " << conteoVector[i].second << " personas" << std::endl;
    }
}

// Pregunta 3: Analisis de Edad por Grupo
void calcularEdadPromedioPorGrupo(const std::vector<PersonaCpp>& personas) {
    std::map<char, std::pair<long long, int>> datosEdadPorGrupo; // Suma de edades y conteo
    for (const auto& p : personas) {
        datosEdadPorGrupo[p.grupoDeclaracion].first += calcularEdad(p.fechaNacimiento);
        datosEdadPorGrupo[p.grupoDeclaracion].second++;
    }
    std::cout << "\n--- Edad Promedio por Grupo de Declaracion ---" << std::endl;
    for (auto const& [grupo, datos] : datosEdadPorGrupo) {
        if (datos.second > 0) {
            double edadPromedio = (double)datos.first / datos.second;
            std::cout << "Grupo " << grupo << ": " << std::fixed << std::setprecision(2) << edadPromedio << " anios" << std::endl;
        }
    }
}