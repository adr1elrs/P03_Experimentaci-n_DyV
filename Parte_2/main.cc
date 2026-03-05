
#include <iostream>
#include "lib/instancia.h"
#include "lib/instancia_planificacion.h"
#include "lib/planificacion_dyv.h"

int main() {
  InstanciaPlanificacion instancia("./input/instance_horizon30_employees30_shifts20_001.json");
  std::cout << instancia << std::endl;
  return 0;
}
