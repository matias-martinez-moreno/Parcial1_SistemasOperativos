#ifndef PERSONA_CPP_H
#define PERSONA_CPP_H

#include <string>

class PersonaCpp {
public:
    std::string nombreCompleto;
    std::string fechaNacimiento;
    std::string ciudadResidencia;
    long long patrimonio;
    long long deudas;
    int documentoIdentidad;
    char grupoDeclaracion;
};

#endif