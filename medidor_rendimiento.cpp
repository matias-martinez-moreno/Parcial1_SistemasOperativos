#include <iostream>
#include <fstream>
#include <string>
#include "medidor_rendimiento.h"

Temporizador::Temporizador() {
    inicio = std::chrono::high_resolution_clock::now();
}

void Temporizador::detener() {
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;
    std::cout << "-> Tiempo de ejecucion: " << duracion.count() << " segundos." << std::endl;
}

long getUsoRAM() {
    std::ifstream file("/proc/self/status");
    std::string line;
    long memory_usage = 0;
    while (std::getline(file, line)) {
        if (line.substr(0, 6) == "VmRSS:") {
            memory_usage = std::stol(line.substr(7));
            break;
        }
    }
    return memory_usage;
}

// Funcion que recibe una copia completa del objeto. Ineficiente.
void procesarPorValor(PersonaCpp persona) {
    volatile int doc = persona.documentoIdentidad;
}

// Funcion que recibe solo una referencia (similar a un puntero). Muy eficiente.
void procesarPorReferencia(const PersonaCpp& persona) {
    volatile int doc = persona.documentoIdentidad;
}

