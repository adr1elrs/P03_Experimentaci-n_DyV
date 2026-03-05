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
  * Archivo merge_sort.cc: 
  */

#include "../lib/merge_sort.h"

bool MergeSort::Small(std::shared_ptr<Instancia> instancia) {
  std::shared_ptr<InstanciaSecuencia> instancia_secuencia = std::dynamic_pointer_cast<InstanciaSecuencia>(instancia);
  if (!instancia_secuencia) {
    return true;
  }
  return (instancia_secuencia->GetSecuencia().size() <= 1);
}

std::shared_ptr<Solucion> MergeSort::SolveSmall(std::shared_ptr<Instancia> instancia) {
  std::shared_ptr<InstanciaSecuencia> instancia_secuencia = std::dynamic_pointer_cast<InstanciaSecuencia>(instancia);
  return std::make_shared<SolucionSecuencia>(instancia_secuencia->GetSecuencia());
}

std::pair<std::shared_ptr<Instancia>, std::shared_ptr<Instancia>> MergeSort::Divide(std::shared_ptr<Instancia> instancia) {
  std::shared_ptr<InstanciaSecuencia> instancia_secuencia = std::dynamic_pointer_cast<InstanciaSecuencia>(instancia);
  if (!instancia_secuencia) return {nullptr, nullptr};
  const std::vector<int> secuencia_actual = instancia_secuencia->GetSecuencia();
  int mitad = secuencia_actual.size() / 2;
  std::vector<int> parte_izquierda(secuencia_actual.begin(), secuencia_actual.begin() + mitad);
  std::vector<int> parte_derecha(secuencia_actual.begin() + mitad, secuencia_actual.end());
  auto primera_mitad = std::make_shared<InstanciaSecuencia>(parte_izquierda);
  auto segunda_mitad = std::make_shared<InstanciaSecuencia>(parte_derecha);
  return {primera_mitad, segunda_mitad};
}

std::shared_ptr<Solucion> MergeSort::Combine(std::shared_ptr<Solucion> solucion_1, std::shared_ptr<Solucion> solucion_2) {
  std::shared_ptr<SolucionSecuencia> solucion_secuencia_1 = std::dynamic_pointer_cast<SolucionSecuencia>(solucion_1);
  std::shared_ptr<SolucionSecuencia> solucion_secuencia_2 = std::dynamic_pointer_cast<SolucionSecuencia>(solucion_2);
  if (!solucion_secuencia_1 || !solucion_secuencia_2) return nullptr;
  const std::vector<int> datos_secuencia_1 = solucion_secuencia_1->GetSolucion();
  const std::vector<int> datos_secuencia_2 = solucion_secuencia_2->GetSolucion();
  int tamaño_primera_solucion = datos_secuencia_1.size();
  int tamaño_segunda_solucion = datos_secuencia_2.size();
  std::vector<int> secuencia_unida;
  secuencia_unida.reserve(tamaño_primera_solucion + tamaño_segunda_solucion);
  int indice_primera_solucion = 0;
  int indice_segunda_solucion = 0;
  while (indice_primera_solucion < tamaño_primera_solucion && indice_segunda_solucion < tamaño_segunda_solucion) {
    if (datos_secuencia_1[indice_primera_solucion] <= datos_secuencia_2[indice_segunda_solucion]) {
      secuencia_unida.push_back(datos_secuencia_1[indice_primera_solucion]);
      indice_primera_solucion++;
    } else {
      secuencia_unida.push_back(datos_secuencia_2[indice_segunda_solucion]);
      indice_segunda_solucion++;
    }
  }
  while (indice_primera_solucion < tamaño_primera_solucion) {
    secuencia_unida.push_back(datos_secuencia_1[indice_primera_solucion]);
    indice_primera_solucion++;
  }
  while (indice_segunda_solucion < tamaño_segunda_solucion) {
    secuencia_unida.push_back(datos_secuencia_2[indice_segunda_solucion]);
    indice_segunda_solucion++;
  }
  return std::make_shared<SolucionSecuencia>(secuencia_unida);
}

