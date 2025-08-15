#include <iostream>
#include <fstream>      // Para escribir en archivos (file stream)
#include <string>
#include <vector>
#include <random>       // Para la generacion moderna de numeros aleatorios en C++
#include <chrono>       // Para obtener una semilla unica para el generador aleatorio

// --- Estructura para organizar un registro 
struct Registro {
    std::string nombreCompleto;
    std::string fechaNacimiento; // Formato "YYYY-MM-DD"
    std::string ciudadResidencia;
    long long patrimonio;
    long long deudas;
    int documentoIdentidad;
    char grupoDeclaracion;
};

// --- Datos base para la generacion aleatoria ---
const std::vector<std::string> NOMBRES = {
    "Santiago", "Sebastian", "Matias", "Nicolas", "Samuel", "Alejandro", "Mateo", "Diego", "Daniel", "Benjamin","Juan", "Jose", "David", "Gabriel", "Lucas", "Martin", "Tomas", "Jeronimo", "Emiliano", "Felipe","Nestor","Edison",
    "Joaquin", "Emmanuel", "Andres", "Simon", "Maximiliano", "Agustin", "Pablo", "Esteban", "Emilio", "Isaac",
    "Bruno", "Miguel", "Angel", "Christopher", "Leonardo", "Francisco", "Adrian", "Thiago", "Mario", "Sergio","Carlos", "Fernando",
     "Jorge", "Ricardo", "Javier", "Luis", "Pedro", "Antonio", "Manuel", "Victor",
    "Sofia", "Valentina", "Isabella", "Mariana", "Luciana", "Camila", "Antonella", "Salome", "Gabriela", "Victoria",
    "Martina", "Samantha", "Valeria", "Julieta", "Emily", "Maria", "Guadalupe", "Ximena", "Regina", "Renata",
    "Mia", "Catalina", "Elena", "Sara", "Ana", "Paula", "Daniela", "Laura", "Antonia", "Juana", "Manuela",
    "Alejandra", "Veronica", "Carolina", "Patricia", "Sandra", "Monica", "Claudia", "Adriana", "Marcela", "Paulina"
};

const std::vector<std::string> APELLIDOS = {
    "Rodriguez", "Gomez", "Perez", "Lopez", "Martinez", "Garcia", "Sanchez", "Ramirez", "Torres", "Diaz","Vargas", "Moreno", "Rojas", 
    "Hernandez", "Jimenez", "Gonzalez", "Gutierrez", "Castro", "Ortiz", "Suarez",
    "Rubio", "Marin", "Silva", "Soto", "Mendoza", "Morales", "Reyes", "Castillo", "Romero", "Herrera",
    "Medina", "Aguilar", "Cardona", "Paredes", "Salazar", "Montoya", "Rios", "Valencia", "Osorio", "Franco","Munoz", "Navarro", "Correa", 
    "Delgado", "Pena", "Campos", "Vega", "Maldonado", "Cardenas", "Guerrero",
    "Acosta", "Arias", "Benitez", "Cabrera", "Duque", "Estrada", "Figueroa", "Giraldo", "Henao", "Ibarra",
    "Jaramillo", "Lara", "Nieto", "Ochoa", "Pardo", "Quintero", "Rincon", "Serrano", "Trujillo", "Uribe"
};

const std::vector<std::string> CIUDADES = {
    "Bogota", "Medellin", "Cali", "Barranquilla", "Cartagena", "Cucuta", "Bucaramanga", "Pereira", "Santa Marta",
    "Ibague", "Manizales", "Villavicencio", "Pasto", "Monteria", "Neiva", "Armenia", "Valledupar", "Popayan",
    "Sincelejo", "Tunja", "Riohacha", "Florencia", "Yopal", "Quibdo", "Mocoa", "Leticia", "Arauca",
    "San Jose del Guaviare", "Inirida", "Mitu", "Puerto Carreno","Marinilla","La ceja"
    "Soacha", "Bello", "Soledad", "Itagui", "Envigado", "Palmira", "Buenaventura", "Tulua", "Dosquebradas",
    "Giron", "Floridablanca", "Barrancabermeja", "Rionegro", "Zipaquira", "Fusagasuga", "Chia", "Apartado",
    "Turbo", "Ocana", "Maicao", "Pitalito", "Duitama", "Sogamoso", "Facatativa", "Magangue"
};

// --- generacion de los numeros aleatorios ---
// Se usa el tiempo actual como la "semilla" para que cada ejecucion sea diferente
std::mt19937 generador(std::chrono::steady_clock::now().time_since_epoch().count());
// Genera un numero entero en un rango minimo y maximo
int generarEnteroAleatorio(int min, int max) {
    std::uniform_int_distribution<int> distribucion(min, max);
    return distribucion(generador);
}

// Genera un numero largo en un rango minimo y maximo
long long generarLongAleatorio(long long min, long long max) {
    std::uniform_int_distribution<long long> distribucion(min, max);
    return distribucion(generador);
}
// Genera un nombre completo combinando un nombre y dos apellidos de la lista
std::string generarNombreCompleto() {
    return NOMBRES[generarEnteroAleatorio(0, NOMBRES.size() - 1)] + " " +
           APELLIDOS[generarEnteroAleatorio(0, APELLIDOS.size() - 1)] + " " +
           APELLIDOS[generarEnteroAleatorio(0, APELLIDOS.size() - 1)];
}

// Genera una fecha de nacimiento en formato año,mes,dia
std::string generarFechaNacimiento() {
    int anio = generarEnteroAleatorio(1945, 2005);
    int mes = generarEnteroAleatorio(1, 12);
    int dia = generarEnteroAleatorio(1, 28); // Se usa 28 para simplificar y evitar fechas invalidas
    return std::to_string(anio) + "-" + (mes < 10 ? "0" : "") + std::to_string(mes) + "-" + (dia < 10 ? "0" : "") + std::to_string(dia);
}

// Asigna el grupo de declaracion segun los dos ultimos digitos del documento
char calcularGrupoDeclaracion(int documento) {
    int ultimosDosDigitos = documento % 100;
    if (ultimosDosDigitos <= 39) return 'A';
    if (ultimosDosDigitos <= 79) return 'B';
    return 'C';
}

// --- Funcion Principal ---
int main(int argc, char* argv[]) {
    // Verificacion de los argumentos de entrada
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <numero_de_registros> <nombre_archivo_salida.csv>" << std::endl;
        return 1; // Termina el programa con un codigo de error
    }

    // Conversion de los argumentos de entrada
    long long numRegistros = std::stoll(argv[1]);
    std::string nombreArchivo = argv[2];

    // Abrir el archivo de salida para escritura
    std::ofstream archivoSalida(nombreArchivo);
    if (!archivoSalida.is_open()) {
        std::cerr << "Error: '" << nombreArchivo << "'" << std::endl;
        return 1;
    }

    std::cout << "Generando " << numRegistros << " registros en el archivo '" << nombreArchivo  << std::endl;

    // cabecera del CSV
    archivoSalida << "Nombre Completo,Fecha Nacimiento,Ciudad Residencia,Patrimonio,Deudas,Documento Identidad,Grupo Declaracion\n";

    // Bucle principal para generar y escribir cada registro
    for (long long i = 0; i < numRegistros; ++i) {
        Registro reg;

        reg.documentoIdentidad = generarEnteroAleatorio(10000000, 1200000000);
        reg.nombreCompleto = generarNombreCompleto();
        reg.fechaNacimiento = generarFechaNacimiento();
        reg.ciudadResidencia = CIUDADES[generarEnteroAleatorio(0, CIUDADES.size() - 1)];
        reg.patrimonio = generarLongAleatorio(2000000, 5000000000); // Patrimonio entre 2 millones y 5 mil millones
        reg.deudas = generarLongAleatorio(0, reg.patrimonio / 2); // Deudas hasta la mitad del patrimonio
        reg.grupoDeclaracion = calcularGrupoDeclaracion(reg.documentoIdentidad);

        // Escribe el registro en el archivo, separando los campos con comas
        archivoSalida << reg.nombreCompleto << ","
                      << reg.fechaNacimiento << ","
                      << reg.ciudadResidencia << ","
                      << reg.patrimonio << ","
                      << reg.deudas << ","
                      << reg.documentoIdentidad << ","
                      << reg.grupoDeclaracion << "\n";

        // imprime el indicador de progreso de los registros
        if ((i + 1) % (numRegistros / 20) == 0) {
            std::cout << "Progreso: " << (100 * (i + 1) / numRegistros) << "% completado." << std::endl;
        }
    }
    archivoSalida.close();

    std::cout << "Los datos fueron generados exitosamente." << std::endl;

    return 0;
}