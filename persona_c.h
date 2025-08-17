#ifndef PERSONA_C_H
#define PERSONA_C_H

// Estructura estilo C para un registro de persona.
// Se usa para la comparacion de eficiencia, aunque el programa principal usara la clase C++.
typedef struct {
    char nombreCompleto[70];
    char fechaNacimiento[11]; 
    char ciudadResidencia[50];
    long long patrimonio;
    long long deudas; 
    int documentoIdentidad;
    char grupoDeclaracion;
} PersonaC;

#endif