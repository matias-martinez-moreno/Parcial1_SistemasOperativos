#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include "procesador_datos.h"
#include "analizador_datos.h"
#include "medidor_rendimiento.h"
#include "persona_c.h"

void imprimirResultadosPorCiudad(const std::string& titulo, const std::map<std::string, PersonaCpp>& resultados) {
    std::cout << "\n--- " << titulo << " ---" << std::endl;
    int count = 0;
    for (auto const& [ciudad, persona] : resultados) {
        if(count++ >= 5) break;
        std::cout << ciudad << ": " << persona.nombreCompleto << std::endl;
    }
}

void imprimirResultadosPorGrupo(const std::string& titulo, const std::map<char, PersonaCpp>& resultados) {
    std::cout << "\n--- " << titulo << " ---" << std::endl;
    for (auto const& [grupo, persona] : resultados) {
        std::cout << "Grupo " << grupo << ": " << persona.nombreCompleto << std::endl;
    }
}

int main() {
    std::cout << "--- PARCIAL 1 SISTEMAS OPERATIVOS ---" << std::endl;
    std::cout << "SOFIA GALLO, JUAN MANUEL GALLO, MATIAS MARTINEZ" << std::endl;
    long ram_inicial = getUsoRAM();
    std::cout << "Uso de RAM inicial: " << ram_inicial << " KB" << std::endl;
    //archivo csv que contiene todos los registros de las personas
    const std::string nombreArchivo = "datos.csv";

    std::cout << "\n[Paso 1: Cargando datos desde " << nombreArchivo << "]" << std::endl;
    Temporizador timer_carga;
    std::vector<PersonaCpp> personas = cargarDatos(nombreArchivo);
    timer_carga.detener();

    if (personas.empty()) {
        std::cout << "No se cargaron bien" << std::endl;
        return 1;
    }
    long ram_post_carga = getUsoRAM();
    std::cout << "Se cargaron " << personas.size() << " registros." << std::endl;
    //mostrar cambios de uso de RAM
    std::cout << "Uso de RAM tras cargar datos: " << ram_post_carga << " KB (Incremento: " << ram_post_carga - ram_inicial << " KB)" << std::endl;

    std::cout << "\n[Paso 2: Preguntas propuestas del parcial]" << std::endl;
    Temporizador timer_analisis;

    // Pregunta 1: Persona más longeva
    PersonaCpp longeva = encontrarPersonaMasLongeva(personas);
    std::cout << "\nPersona más longeva (País): " << longeva.nombreCompleto << " (" << calcularEdad(longeva.fechaNacimiento) << " anios)" << std::endl;
    auto longevaPorCiudad = encontrarMasLongevaPorCiudad(personas);
    imprimirResultadosPorCiudad("Persona más longeva (por ciudad, top 5)", longevaPorCiudad);

    // Pregunta 2: Persona con mayor patrimonio
    PersonaCpp rica = encontrarPersonaMayorPatrimonio(personas);
    std::cout << "\nPersona con mayor patrimonio neto (País): " << rica.nombreCompleto << " ($" << rica.patrimonio - rica.deudas << ")" << std::endl;
    auto ricaPorCiudad = encontrarMasRicaPorCiudad(personas);
    imprimirResultadosPorCiudad("Persona más rica (por ciudad, top 5)", ricaPorCiudad);
    auto ricaPorGrupo = encontrarMasRicaPorGrupo(personas);
    imprimirResultadosPorGrupo("Persona más rica (por grupo)", ricaPorGrupo);

    // Pregunta 3: Conteo y validación de declarantes
    contarYValidarPorGrupo(personas);

    timer_analisis.detener();

    std::cout << "\n[Paso 3: Preguntas adicionales del grupo]" << std::endl;
    Temporizador timer_adicional;
    calcularPatrimonioTotalPorGrupo(personas);
    encontrarCiudadesConMasDeclarantes(personas);
    calcularEdadPromedioPorGrupo(personas);
    timer_adicional.detener();

    std::cout << "\n[Paso 4: Comparaciones Técnicas del Rendimiento]" << std::endl;
    
    // Comparación Struct vs Class
    std::cout << "\n--- Comparación Struct (C) vs Class (C++) ---" << std::endl;
    std::cout << "sizeof(PersonaC): " << sizeof(PersonaC) << " bytes" << std::endl;
    std::cout << "sizeof(PersonaCpp): " << sizeof(PersonaCpp) << " bytes" << std::endl;
    std::cout << "Nota: La diferencia se debe a la gestión de memoria de std::string en la clase. El struct usa memoria fija en la pila, mientras que la clase usa memoria dinámica para los strings." << std::endl;

    // Comparación Valores vs Apuntadores (Referencias)
    std::cout << "\n--- Comparación Valores vs. Apuntadores (Referencias) ---" << std::endl;
    // Mostrar encabezado para la comparación de rendimiento al procesar 5 millones de registros
    const int N_ITERACIONES = 5000000;
    
    Temporizador timer_valor;
    for(int i=0; i<N_ITERACIONES; ++i) {
        procesarPorValor(personas[i % personas.size()]);
    }
    auto fin_valor = std::chrono::high_resolution_clock::now();
    
    Temporizador timer_referencia;
    for(int i=0; i<N_ITERACIONES; ++i) {
        procesarPorReferencia(personas[i % personas.size()]);
    }
    auto fin_referencia = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duracion_valor = fin_valor - timer_valor.getInicio();
    std::chrono::duration<double> duracion_referencia = fin_referencia - timer_referencia.getInicio();

    std::cout << "Procesando " << N_ITERACIONES << " registros por VALOR:" << std::endl;
    std::cout << "-> Tiempo de ejecución: " << duracion_valor.count() << " segundos." << std::endl;
    
    std::cout << "Procesando " << N_ITERACIONES << " registros por REFERENCIA:" << std::endl;
    std::cout << "-> Tiempo de ejecución: " << duracion_referencia.count() << " segundos." << std::endl;

    if (duracion_valor.count() > 0 && duracion_referencia.count() > 0) {
        double mejora = (duracion_valor.count() / duracion_referencia.count());
        std::cout << "\nConclusión: Pasar por referencia fue " << std::fixed << std::setprecision(2) << mejora << " veces más rápido que por valor." << std::endl;
    }

    std::cout << "\n--- FIN DEL PROGRAMA ---" << std::endl;

    return 0;
}