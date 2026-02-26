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
  * Archivo instancia_secuencia.h: 
  */

#ifndef INSTANCIA_SECUENCIA_H
#define INSTANCIA_SECUENCIA_H

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "instancia.h"

class InstanciaSecuencia : public Instancia {
 public:
  InstanciaSecuencia(int n);
  InstanciaSecuencia(std::string nombre_fichero);
  InstanciaSecuencia(std::vector<int> secuencia) : secuencia_(secuencia) {}
  
  // Getters
  inline std::vector<int> GetSecuencia() const { return secuencia_; }
  inline int GetElemento(int indice) const { return secuencia_[indice]; } 
  
  // Setters
  inline void SetSecuencia(const std::vector<int>& secuencia) { secuencia_ = secuencia; }
  inline void SetElemento(int indice, int valor) { secuencia_[indice] = valor; }

  // Sobrecarga del operador de inserción para imprimir la instancia
  void Print(std::ostream& os) const override;
 private:
  std::vector<int> secuencia_;
};


#endif