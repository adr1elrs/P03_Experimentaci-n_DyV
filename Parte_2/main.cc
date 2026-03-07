/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Diseño y Análisis de Algoritmos 2025-2026
 *
 * @author Sergio Rosales Calzadilla
 * @author Adriel Reyes Suárez
 * @date 26/02/2026
 * @brief Archivo main para la ejecución del algoritmo Divide y Vencerás
 */

#include <iostream>
#include <memory>
#include <string>
#include <exception>

// Asegúrate de que las rutas coincidan con la estructura de tus carpetas
#include "../lib/instancia_planificacion.h"
#include "../lib/planificacion_dyv.h"

int main(int argc, char* argv[]) {
  // 1. Control de parámetros de entrada
  if (argc != 2) {
    std::cerr << "Error de sintaxis.\n";
    std::cerr << "Uso correcto: " << argv[0] << " <ruta_al_fichero.json>\n";
    return 1;
  }

  try {
    // 2. Lectura del argumento
    std::string ruta_fichero = argv[1];
    std::cout << "[*] Cargando instancia desde: " << ruta_fichero << "...\n";

    // 3. Instanciación del problema (Lee el JSON y reserva memoria)
    auto instancia = std::make_shared<InstanciaPlanificacion>(ruta_fichero);
    
    // (Opcional) Imprimimos los datos para comprobar que se leyó bien
    instancia->Print(std::cout);

    // 4. Inicialización del Algoritmo
    std::cout << "\n[*] Iniciando resolución mediante Divide y Vencerás...\n";
    PlanificacionDyV algoritmo;

    // 5. Ejecución del motor (La magia ocurre aquí)
    auto solucion = algoritmo.solve(instancia);

    // 6. Presentación de resultados
    if (solucion) {
      std::ofstream fichero_salida("salida.txt")  ;
      std::cout << "\n[+] ¡Solución encontrada con éxito!\n";
      std::cout << "Volcando resultados a 'salida.txt'...\n";
      solucion->Print(fichero_salida);
    } else {
      std::cerr << "\n[-] El algoritmo no pudo encontrar una solución válida.\n";
    }

  } catch (const std::exception& e) {
    // Control de excepciones (ej: si el JSON no existe o está mal formateado)
    std::cerr << "\n[!] Error crítico durante la ejecución: " << e.what() << "\n";
    return 1;
  }

  return 0;
}