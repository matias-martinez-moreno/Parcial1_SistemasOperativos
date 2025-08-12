#ifndef MEDIDOR_RENDIMIENTO_H
#define MEDIDOR_RENDIMIENTO_H

#include <chrono>
#include <string>
#include "persona_cpp.h"

class Temporizador {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> inicio;
public:
    Temporizador();
    void detener();
    std::chrono::time_point<std::chrono::high_resolution_clock> getInicio() const { return inicio; }
};

// Función para obtener el uso de memoria RAM del proceso actual (en KB)
long getUsoRAM();

// Funciones para la comparación de rendimiento
void procesarPorValor(PersonaCpp persona);
void procesarPorReferencia(const PersonaCpp& persona);

#endif