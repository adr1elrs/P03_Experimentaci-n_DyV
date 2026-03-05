/**
 * @file solucion_planificacion.cc
 * @brief Implementación de la clase SolucionPlanificacion.
 * @author Sergio Rosales Calzadilla
 * @author Adriel Reyes Suárez
 * @date 26/02/2026
 * * @details Gestiona la matriz de asignaciones de turnos y mantiene una caché
 * de orden O(1) para el cálculo instantáneo de la función objetivo.
 */

#include "../lib/solucion_planificacion.h"
#include <iomanip>

/**
 * @brief Constructor. Reserva la memoria exacta para la ventana temporal.
 * @param dia_inicio Día absoluto de inicio.
 * @param num_dias Tamaño de la ventana de tiempo.
 * @param num_empleados Total de empleados en la plantilla.
 * @param num_turnos Total de turnos disponibles por día.
 */
SolucionPlanificacion::SolucionPlanificacion(int dia_inicio, int num_dias, int num_empleados, int num_turnos) 
    : dia_inicio_(dia_inicio), 
      num_dias_(num_dias),
      suma_satisfaccion_(0),
      turnos_cubiertos_(0) {
  
  // Reserva de memoria O(D * T) para evitar realojamientos dinámicos
  asignaciones_.resize(num_dias_, std::vector<std::vector<int>>(num_turnos));
  dias_trabajados_.resize(num_empleados, 0);
}

/**
 * @brief Asigna un empleado a un turno y actualiza la caché en O(1).
 * @param dia_relativo Índice del día dentro de esta subsolución (0 a num_dias_-1).
 * @param turno Identificador del turno.
 * @param empleado Identificador del empleado.
 * @param satisfaccion Valor de satisfacción aportado por esta asignación.
 */
void SolucionPlanificacion::AsignarEmpleado(int dia_relativo, int turno, int empleado, int satisfaccion) {
  asignaciones_[dia_relativo][turno].push_back(empleado);
  dias_trabajados_[empleado]++;
  suma_satisfaccion_ += satisfaccion;
}

/**
 * @brief Incrementa el contador de turnos que han alcanzado el mínimo requerido.
 */
void SolucionPlanificacion::RegistrarTurnoCubierto() {
  turnos_cubiertos_++;
}

/**
 * @brief Fusiona esta solución con otra posterior cronológicamente.
 * Complejidad temporal lineal respecto al tamaño de la solución entrante.
 * @param otra Objeto SolucionPlanificacion correspondiente al siguiente bloque de días.
 */
void SolucionPlanificacion::Concatenar(const SolucionPlanificacion& otra) {
  // 1. Inserción de las matrices 3D
  asignaciones_.insert(asignaciones_.end(), otra.asignaciones_.begin(), otra.asignaciones_.end());
  
  // 2. Actualización de las dimensiones temporales
  num_dias_ += otra.num_dias_;
  
  // 3. Suma vectorial de los días trabajados por cada empleado
  for (size_t e = 0; e < dias_trabajados_.size(); ++e) {
    dias_trabajados_[e] += otra.dias_trabajados_[e];
  }
  
  // 4. Unificación de la caché de calidad
  suma_satisfaccion_ += otra.suma_satisfaccion_;
  turnos_cubiertos_ += otra.turnos_cubiertos_;
}

/**
 * @brief Recupera la lista de empleados trabajando en un momento dado en O(1).
 * @param dia_relativo Índice del día en la subsolución.
 * @param turno Identificador del turno.
 * @return Referencia constante al vector de empleados asignados.
 */
const std::vector<int>& SolucionPlanificacion::GetAsignaciones(int dia_relativo, int turno) const {
  return asignaciones_[dia_relativo][turno];
}

/**
 * @brief Consulta la carga de trabajo acumulada de un empleado en O(1).
 * @param empleado Identificador del empleado.
 * @return Número de días que ha trabajado en esta ventana temporal.
 */
int SolucionPlanificacion::GetDiasTrabajados(int empleado) const {
  return dias_trabajados_[empleado];
}

/**
 * @brief Devuelve el valor de la función objetivo f(x) instantáneamente.
 * @return Puntuación total (Satisfacción + Turnos cubiertos * 100).
 */
int SolucionPlanificacion::GetCalidad() const {
  return suma_satisfaccion_ + (turnos_cubiertos_ * 100);
}

/**
 * @brief Imprime la matriz de horarios por consola de forma tabulada.
 * @param os Flujo de salida (ej. std::cout).
 */
void SolucionPlanificacion::Print(std::ostream& os) const {
   os << "\n--- Planificación de Empleados (Días " << dia_inicio_ << " a "
      << (dia_inicio_ + num_dias_ - 1) << ") ---\n";
   os << "Calidad de la solución: " << GetCalidad() << " (Satisfacción: "
      << suma_satisfaccion_ << ", Turnos cubiertos: " << turnos_cubiertos_ << ")\n\n";

   if (asignaciones_.empty() || asignaciones_[0].empty()) return;

   int num_turnos = asignaciones_[0].size();

   os << std::left << std::setw(10) << "Día";
   for (int t = 0; t < num_turnos; ++t) {
       os << "| Turno " << std::setw(8) << t << " ";
   }
   os << "\n" << std::string(10 + (17 * num_turnos), '-') << "\n";

   for (int d = 0; d < num_dias_; ++d) {
       os << std::left << std::setw(10) << (dia_inicio_ + d);
       
       for (int t = 0; t < num_turnos; ++t) {
           os << "| ";
           if (asignaciones_[d][t].empty()) {
               os << std::setw(14) << "Vacío";
           } else {
               std::string emps = "";
               for (size_t i = 0; i < asignaciones_[d][t].size(); ++i) {
                   emps += std::to_string(asignaciones_[d][t][i]);
                   if (i < asignaciones_[d][t].size() - 1) emps += ",";
               }
               os << std::setw(14) << emps;
           }
       }
       os << "\n";
   }
   os << "\n";
}