
#include <iostream>
#include "lib/utilidades_main.h"


int main() {
  int modo;
  std::cout << "Elija modo (1: Normal/Comparativa, 2: Debug): ";
  std::cin >> modo;

  auto merge_sort = std::make_shared<MergeSort>();
  auto quick_sort = std::make_shared<QuickSort>();

  if (modo == 1) {
    std::vector<int> tamanos = {100, 500, 1000, 5000, 10000, 100000};
    std::vector<double> tiempos_merge, tiempos_quick;

    for (int n : tamanos) {
      auto instancia = std::make_shared<InstanciaSecuencia>(n);
  
      // Medimos MergeSort
      tiempos_merge.push_back(MedirTiempo(merge_sort, instancia));
      
      // Medimos QuickSort
      tiempos_quick.push_back(MedirTiempo(quick_sort, instancia));
    }

    MostrarTablaComparativa(tamanos, tiempos_merge, tiempos_quick);
  } else if (modo == 2) {
    int n;
    std::cout << "Tamaño de instancia para debug: ";
    std::cin >> n;

    auto instancia = std::make_shared<InstanciaSecuencia>(n);
    std::cout << "\n--- INSTANCIA ORIGINAL ---\n" << *instancia << "\n";

    auto sol_merge = merge_sort->solve(instancia);
    std::cout << "\n--- SOLUCIÓN MERGESORT ---\n" << *sol_merge << "\n";

    auto sol_quick = quick_sort->solve(instancia);
    std::cout << "\n--- SOLUCIÓN QUICKSORT ---\n" << *sol_quick << "\n";
  }

  return 0;
}
