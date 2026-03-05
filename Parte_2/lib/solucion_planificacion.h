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
  * Archivo solucion_planificacion.h: 
  */

/**
 * Archivo: solucion_planificacion.h
 * Descripción: Declaración de la clase SolucionPlanificacion para el problema
 * de asignación de turnos mediante Divide y Vencerás.
 */

#ifndef SOLUCION_PLANIFICACION_H
#define SOLUCION_PLANIFICACION_H

#include <vector>
#include <iostream>
#include <memory>
#include "solucion.h" 

/**
 * @brief Representa una solución (o subsolución) del problema de planificación.
 * Almacena las asignaciones y mantiene un estado interno (caché) para que 
 * las operaciones de mezcla en el DyV sean eficientes.
 */
class SolucionPlanificacion : public Solucion {
 public:
  /**
   * @brief Constructor. Inicializa las estructuras vacías para la ventana de tiempo.
   */
  SolucionPlanificacion(int dia_inicio, int num_dias, int num_empleados, int num_turnos);
  /**
   * @brief Asigna un empleado a un turno y actualiza las métricas internas.
   * @param dia_relativo Día dentro de la subsolución (0 a num_dias_ - 1).
   * @param turno El turno a cubrir.
   * @param empleado ID del empleado asignado.
   * @param satisfaccion Valor A[e][d][t] para sumarlo a la caché.
   */
  void AsignarEmpleado(int dia_relativo, int turno, int empleado, int satisfaccion);
  /**
   * @brief Registra que un turno ha alcanzado el mínimo B[d][t].
   */
  void RegistrarTurnoCubierto();
  /**
   * @brief Devuelve la lista de empleados asignados a un turno concreto.
   */
  const std::vector<int>& GetAsignaciones(int dia_relativo, int turno) const;
  /**
   * @brief Devuelve cuántos días ha trabajado un empleado en esta subsolución.
   * Esencial para que el Combine valide las restricciones de descanso.
   */
  int GetDiasTrabajados(int empleado) const;
  /**
   * @brief Calcula y devuelve la función objetivo f(x)
   * Fórmula: SUMA(satisfaccion) + SUMA(turnos_cubiertos) * 100
   */
  int GetCalidad() const;
  // --- Getters del bloque temporal ---
  int GetDiaInicio() const { return dia_inicio_; }
  int GetNumDias() const { return num_dias_; }
  /**
   * @brief Muestra la solución por pantalla de forma legible
   */
  void Print(std::ostream& os) const override;

  /**
   * @brief Fusiona otra subsolución cronológicamente posterior a esta.
   */
  void Concatenar(const SolucionPlanificacion& otra);

 private:
  int dia_inicio_; ///< Día absoluto en el que comienza esta subsolución.
  int num_dias_;   ///< Cantidad de días que abarca.

  // Matriz 3D: [dia_relativo][turno] -> Lista de IDs de empleados asignados
  // Se usa un vector interno porque un turno puede requerir múltiples empleados.
  std::vector<std::vector<std::vector<int>>> asignaciones_;

  // Vector: [ID_empleado] -> Cuántos días ha trabajado en esta subsolución
  std::vector<int> dias_trabajados_;

  // Caché para la función objetivo f(x)
  int suma_satisfaccion_;
  int turnos_cubiertos_;
};

#endif