/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Diseño y Análisis de Algoritmos 2025-2026
  * Curso: 3º
  * Práctica 3 - Experimentación DYV
  * 
  * @author Sergio Rosales Calzadilla
  * @author Adriel Reyes Suárez
  * @date 26/02/2026
  * Archivo quick_sort.h: 
  */

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "divide_y_venceras.h"
#include "instancia.h"
#include "solucion.h"
#include "solucion_secuencia.h"

class QuickSort : public DivideYVenceras {
 public:
  // Función que comprueba que la instancia es suficientemente pequeña para ser resuelta directamente
  bool Small(std::shared_ptr<Instancia> instancia) override;
  // Función para resolver la instancia si es suficientemente pequeña
  std::shared_ptr<Solucion> SolveSmall(std::shared_ptr<Instancia> instancia) override;
  // Función para dividir la instancia en dos subinstancias
  std::pair<std::shared_ptr<Instancia>, std::shared_ptr<Instancia>> Divide(std::shared_ptr<Instancia> instancia) override;
  // Función para combinar las soluciones de las subinstancias
  std::shared_ptr<Solucion> Combine(std::shared_ptr<Solucion> solucion_1, std::shared_ptr<Solucion> solucion_2) override;
};

#endif

  