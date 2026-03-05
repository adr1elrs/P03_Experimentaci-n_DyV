#ifndef UTILIDADES_MAIN_H
#define UTILIDADES_MAIN_H

#include <iostream>
#include <random>
#include <iomanip>
#include <chrono>
#include <memory>
#include <vector>
#include "algoritmo.h"
#include "divide_y_venceras.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "solucion.h"
#include "solucion_secuencia.h"
#include "instancia.h"
#include "instancia_secuencia.h"
#include "utilidades_main.h"

std::shared_ptr<Algoritmo> SeleccionarAlgoritmo() {
  int opcion;
  std::cout << "Seleccione algoritmo (1: MergeSort, 2: QuickSort): ";
  std::cin >> opcion;
  if (opcion == 1) return std::make_shared<MergeSort>();
  return std::make_shared<QuickSort>();
}

void ModoNormal(std::shared_ptr<Algoritmo> algoritmo) {
  std::vector<int> tamanos = {100, 1000, 5000, 10000, 100000}; // Ejemplo de tamaños
  
  std::cout << "\n--- MODO NORMAL (Tiempos de ejecución) ---\n";
  std::cout << "Tamaño\t\tTiempo (ms)\n";
  
  for (int n : tamanos) {
    // Aquí deberías tener una función que genere una instancia aleatoria de tamaño n
    auto instancia = std::make_shared<InstanciaSecuencia>(n); 
    
    auto inicio = std::chrono::high_resolution_clock::now();
    auto solucion = algoritmo->solve(instancia);
    auto fin = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> tiempo = fin - inicio;
    std::cout << n << "\t\t" << tiempo.count() << " ms" << std::endl;
  }
}

void ModoDebug(std::shared_ptr<Algoritmo> algoritmo, int tamano) {
  std::cout << "\n--- MODO DEBUG ---\n";
  auto instancia = std::make_shared<InstanciaSecuencia>(tamano);
  
  std::cout << "Instancia inicial: " << *instancia << std::endl;
  
  auto solucion = algoritmo->solve(instancia);
  
  if (solucion) {
    std::cout << "Solución obtenida: " << *solucion << std::endl;
  } else {
    std::cerr << "Error: La solución es nula." << std::endl;
  }
}


double MedirTiempo(std::shared_ptr<Algoritmo> algoritmo, std::shared_ptr<Instancia> instancia) {
  auto inicio = std::chrono::high_resolution_clock::now();
  algoritmo->solve(instancia);
  auto fin = std::chrono::high_resolution_clock::now();
  
  std::chrono::duration<double, std::milli> tiempo = fin - inicio;
  return tiempo.count();
}

void MostrarTablaComparativa(const std::vector<int>& tamanos, const std::vector<double>& tiempos_merge, const std::vector<double>& tiempos_quick) {
  std::cout << "\n" << std::setw(10) << "Tamaño" << std::setw(20) << "MergeSort (ms)" << std::setw(20) << "QuickSort (ms)" << "\n";
  std::cout << std::string(50, '-') << "\n";

  for (size_t i = 0; i < tamanos.size(); ++i) {
    std::cout << std::setw(10) << tamanos[i] << std::setw(20) << std::fixed << std::setprecision(4) << tiempos_merge[i]
    << std::setw(20) << std::fixed << std::setprecision(4) << tiempos_quick[i] << "\n";
  }
}
#endif