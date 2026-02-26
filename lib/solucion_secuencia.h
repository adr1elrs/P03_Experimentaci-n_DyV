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
  * Archivo solucion_secuencia.h: 
  */

#ifndef SOLUCION_SECUENCIA_H
#define SOLUCION_SECUENCIA_H

#include <iostream>
#include <vector>

#include "solucion.h"

class SolucionSecuencia : public Solucion {
 public:
  SolucionSecuencia(std::vector<int> vector_ordenado) : solucion_(vector_ordenado) {}
  void Print(std::ostream& os) const override;
  // Getter
  std::vector<int> GetSolucion() {return solucion_; }
 private:
  std::vector<int> solucion_;
};

#endif