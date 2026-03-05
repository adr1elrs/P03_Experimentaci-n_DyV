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
  * Archivo planificacion_dyv.cc: 
  */

#include "../lib/instancia_planificacion.h"
#include "../lib/solucion_planificacion.h"
#include "../lib/planificacion_dyv.h"


bool PlanificacionDyV::Small(std::shared_ptr<Instancia> instancia) {
  std::shared_ptr<InstanciaPlanificacion> instancia_dyv = std::dynamic_pointer_cast<InstanciaPlanificacion>(instancia);
  return (instancia_dyv->GetNumDias() == 1);
}

std::shared_ptr<Solucion> PlanificacionDyV::SolveSmall(std::shared_ptr<Instancia> instancia) {
  std::shared_ptr<InstanciaPlanificacion> instancia_dyv = std::dynamic_pointer_cast<InstanciaPlanificacion>(instancia);
  
  if (!instancia_dyv) return nullptr;

  int num_empleados = instancia_dyv->GetNumEmpleados();
  int num_turnos = instancia_dyv->GetNumTurnos();

  auto solucion = std::make_shared<SolucionPlanificacion>(instancia_dyv->GetDiaInicio(), 1, num_empleados, num_turnos);

  const std::vector<int>& empleados_requeridos = instancia_dyv->GetCapacidadesTurnosDia(0);

  std::vector<bool> empleado_ocupado(num_empleados, false);

  for (size_t t{0}; t < empleados_requeridos.size(); ++t) {
    int requeridos = empleados_requeridos[t];
    int gente_trabajando = 0;
    for (int i{0}; i < requeridos; ++i) {
      int mejor_empleado = -1;
      int mejor_sat = -1;
      
      for (int e{0}; e < num_empleados; ++e) {
        if (!empleado_ocupado[e]) {
          int actual_sat_empleado = instancia_dyv->GetSatisfaccion(e, 0, t);
          
          if (actual_sat_empleado > mejor_sat) {
            mejor_sat = actual_sat_empleado;
            mejor_empleado = e;
          }
        }
      }

      if (mejor_empleado != -1) {
        solucion->AsignarEmpleado(0, t, mejor_empleado, mejor_sat);
        empleado_ocupado[mejor_empleado] = true;
        ++gente_trabajando;
      }
    }

    if (gente_trabajando >= requeridos && requeridos > 0) {
      solucion->RegistrarTurnoCubierto();
    }
  }
  
  return solucion;
}

std::pair<std::shared_ptr<Instancia>, std::shared_ptr<Instancia>> PlanificacionDyV::Divide(std::shared_ptr<Instancia> instancia) {
  std::shared_ptr<InstanciaPlanificacion> instancia_dyv = std::dynamic_pointer_cast<InstanciaPlanificacion>(instancia);
  if (!instancia_dyv) return {nullptr, nullptr};
  int mitad_dias = instancia_dyv->GetNumDias() / 2;
  auto primera_mitad_instancia = std::make_shared<InstanciaPlanificacion>(instancia_dyv->GetDiaInicio(), mitad_dias, *instancia_dyv);
  auto segunda_mitad_instancia = std::make_shared<InstanciaPlanificacion>(instancia_dyv->GetDiaInicio() + mitad_dias, instancia_dyv->GetNumDias() - mitad_dias, *instancia_dyv);
  return {primera_mitad_instancia, segunda_mitad_instancia};
}

std::shared_ptr<Solucion> PlanificacionDyV::Combine(std::shared_ptr<Solucion> solucion_1, std::shared_ptr<Solucion> solucion_2) {
  auto solucion_izquierda = std::dynamic_pointer_cast<SolucionPlanificacion>(solucion_1);
  auto solucion_derecha = std::dynamic_pointer_cast<SolucionPlanificacion>(solucion_2);
  if (!solucion_izquierda || !solucion_derecha) return nullptr;
  return nullptr;
}

