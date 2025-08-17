#include <iostream>
#include <vector>
#include <limits>
#include <map>
#include <algorithm>
#include <iomanip> // se usa para std::fixed y std::setprecision
#include <cstring>
#include "analizador_datos.h"
#include "persona_c.h"
#include <chrono>
#include <string>

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

// funcion usando struct en C
PersonaC encontrarPersonaMasLongevaC(PersonaC personas[], int tamaño) {
    if (tamaño == 0) return PersonaC{};
    
    PersonaC masLongeva = personas[0];
    int maxEdad = 0;
    
    for (int i = 0; i < tamaño; i++) {
        // Calcular edad (suponiendo formato YYYY-MM-DD)
        int año = (personas[i].fechaNacimiento[0] - '0') * 1000 + 
                  (personas[i].fechaNacimiento[1] - '0') * 100 +
                  (personas[i].fechaNacimiento[2] - '0') * 10 + 
                  (personas[i].fechaNacimiento[3] - '0');
        int edad = 2025 - año;
        
        if (edad > maxEdad) {
            maxEdad = edad;
            masLongeva = personas[i];
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

void medirTiempoBusquedaLongeva(const std::vector<PersonaCpp>& personas) {
    std::cout << "\n--- Midiendo busqueda con PersonaCpp ---" << std::endl;
    
    // Llamada de calentamiento
    encontrarPersonaMasLongeva(personas);
    
    // Medicion real
    auto inicio = std::chrono::high_resolution_clock::now();
    PersonaCpp resultado = encontrarPersonaMasLongeva(personas);
    auto fin = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duracion = fin - inicio;
    
    std::cout << "Persona mas longeva encontrada:\n";
    std::cout << "Nombre: " << resultado.nombreCompleto << "\n";
    std::cout << "Tiempo de ejecucion: " << duracion.count() << " segundos\n";
    std::cout << "Para " << personas.size() << " registros\n";
}

void medirTiempoBusquedaLongevaC(PersonaC personas[], int tamaño) {
    std::cout << "\n--- Midiendo busqueda con PersonaC ---" << std::endl;
    
    // Llamada de calentamiento
    encontrarPersonaMasLongevaC(personas, tamaño);
    
    // Medicion real
    auto inicio = std::chrono::high_resolution_clock::now();
    PersonaC resultado = encontrarPersonaMasLongevaC(personas, tamaño);
    auto fin = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duracion = fin - inicio;
    
    std::cout << "Persona mas longeva encontrada:\n";
    std::cout << "Nombre: " << resultado.nombreCompleto << "\n";
    std::cout << "Tiempo de ejecucion: " << duracion.count() << " segundos\n";
    std::cout << "Para " << tamaño << " registros\n";
}