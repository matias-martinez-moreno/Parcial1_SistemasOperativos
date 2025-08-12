#ifndef PERSONA_C_H
#define PERSONA_C_H

// Estructura estilo C para un registro de persona.
// Se usa para la comparación de eficiencia, aunque el programa principal usará la clase C++.
typedef struct {
    char nombreCompleto[150];
    char fechaNacimiento[11]; 
    char ciudadResidencia[50];
    long long patrimonio;
    long long deudas;
    int documentoIdentidad;
    char grupoDeclaracion;
} PersonaC;

#endif