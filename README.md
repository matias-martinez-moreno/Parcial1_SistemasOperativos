* Matias Martinez
* Sofia Gallo
* Juan Manuel Gallo
## IMPORTANTE PARA EJECUTAR

Asegurate de tener un compilador de C++ (`g++`) instalado.

### 1. Generar el Archivo de Datos

Primero, se debe compilar y ejecutar el generador para crear el archivo `datos.csv`.

**Compilar:**
```bash
g++ generador_datos.cpp -std=c++17 -O2 -o generador
```

**Ejecutar (ejemplo con 5 millones de registros):**
```bash
./generador 5000000 datos.csv
```

### 2. Analizar los Datos

Una vez que `datos.csv` exista, compila y ejecuta el programa principal.

**Compilar:**
```bash
g++ main.cpp procesador_datos.cpp analizador_datos.cpp medidor_rendimiento.cpp -std=c++17 -O2 -o parcial1
```

**Ejecutar:**
```bash
./parcial1
```
El programa leera el archivo `datos.csv` y mostrara todos los resultados del analisis en la terminal.
