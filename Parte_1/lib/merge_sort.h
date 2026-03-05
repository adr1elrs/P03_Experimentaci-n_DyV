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
  * @file instruccion.h: 
  */

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "divide_y_venceras.h"

class MergeSort : public DivideYVenceras {
 public:
  bool Small(std::shared_ptr<Instancia> instancia) override;
  // Función vitual para resolver cuando es suficientemente pequeña
  std::shared_ptr<Solucion> SolveSmall(std::shared_ptr<Instancia> instancia) override;
  // Función virtual para dividir la instancia en subinstancias
  std::pair<std::shared_ptr<Instancia>, std::shared_ptr<Instancia>> Divide(std::shared_ptr<Instancia> instancia) override;
  // Función virtual para combinar las subinstancias
  std::shared_ptr<Solucion> Combine(std::shared_ptr<Solucion> solucion_1, std::shared_ptr<Solucion> solucion_2) override;
 private:
};

#endif