#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "procesador_datos.h"
std::vector<PersonaCpp> cargarDatos(const std::string& nombreArchivo) {
    std::vector<PersonaCpp> personas;
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir  " << nombreArchivo << std::endl;
        return personas;
    }
    std::string linea;
    std::getline(archivo, linea); 
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string campo;
        std::vector<std::string> campos;
        while(std::getline(ss, campo, ',')) {
            campos.push_back(campo);
        }
        if (campos.size() == 7) {
            PersonaCpp p;
            p.nombreCompleto =campos[0];
            p.fechaNacimiento =campos[1];
            p.ciudadResidencia = campos[2];
            try {
                p.patrimonio = std::stoll(campos[3]);
                p.deudas = std::stoll(campos[4]);
                p.documentoIdentidad = std::stoi(campos[5]);
                p.grupoDeclaracion = campos[6][0];
            } catch (const std::exception& e) {
                continue;
            }
            personas.push_back(p);
        }
    }
    archivo.close();
    return personas;
}