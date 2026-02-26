
#include <utility>
#include "../lib/quick_sort.h"

bool QuickSort::Small(std::shared_ptr<Instancia> instancia) {
  std::shared_ptr<InstanciaSecuencia> instancia_secuencia = std::dynamic_pointer_cast<InstanciaSecuencia>(instancia);
  if (!instancia_secuencia) {
    return true;
  }
  return instancia_secuencia->GetSecuencia().size() <= 2;
}

std::shared_ptr<Solucion> QuickSort::SolveSmall(std::shared_ptr<Instancia> instancia) {
  std::shared_ptr<InstanciaSecuencia> instancia_secuencia = std::dynamic_pointer_cast<InstanciaSecuencia>(instancia);
  if (instancia_secuencia->GetSecuencia().size() == 2 && (instancia_secuencia->GetElemento(0) > instancia_secuencia->GetElemento(1))) {
    std::vector<int> secuencia = instancia_secuencia->GetSecuencia();
    std::swap(secuencia[0], secuencia[1]);
    return std::make_shared<SolucionSecuencia>(secuencia);
  } 
  return std::make_shared<SolucionSecuencia>(instancia_secuencia->GetSecuencia());
}

std::pair<std::shared_ptr<Instancia>, std::shared_ptr<Instancia>> QuickSort::Divide(std::shared_ptr<Instancia> instancia) {
  std::shared_ptr<InstanciaSecuencia> instancia_secuencia = std::dynamic_pointer_cast<InstanciaSecuencia>(instancia);
  std::vector<int> secuencia = instancia_secuencia->GetSecuencia();

  int pivot = secuencia[secuencia.size() / 2];
  std::vector<int> menor, mayor;

  for (int num : secuencia) {
    if (num < pivot) {
      menor.push_back(num);
    } else if (num > pivot) {
      mayor.push_back(num);
    } else {
      if (menor.size() < mayor.size()) menor.push_back(num);
      else mayor.push_back(num);
    }
  }
  auto menor_solucion = std::make_shared<InstanciaSecuencia>(menor);
  auto mayor_solucion = std::make_shared<InstanciaSecuencia>(mayor);
  return {menor_solucion, mayor_solucion};
}

std::shared_ptr<Solucion> QuickSort::Combine(std::shared_ptr<Solucion> solucion_1, std::shared_ptr<Solucion> solucion_2) {
  std::shared_ptr<SolucionSecuencia> solucion_secuencia_1 = std::dynamic_pointer_cast<SolucionSecuencia>(solucion_1);
  std::shared_ptr<SolucionSecuencia> solucion_secuencia_2 = std::dynamic_pointer_cast<SolucionSecuencia>(solucion_2);
  if (!solucion_secuencia_1 || !solucion_secuencia_2) return nullptr;
  const std::vector<int> datos_secuencia_1 = solucion_secuencia_1->GetSolucion();
  const std::vector<int> datos_secuencia_2 = solucion_secuencia_2->GetSolucion();
  std::vector<int> secuencia_unida;
  secuencia_unida.reserve(datos_secuencia_1.size() + datos_secuencia_2.size());
  secuencia_unida.insert(secuencia_unida.end(), datos_secuencia_1.begin(), datos_secuencia_1.end());
  secuencia_unida.insert(secuencia_unida.end(), datos_secuencia_2.begin(), datos_secuencia_2.end());
  return std::make_shared<SolucionSecuencia>(secuencia_unida);
}