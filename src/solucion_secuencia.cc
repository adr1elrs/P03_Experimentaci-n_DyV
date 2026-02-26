#include "../lib/solucion_secuencia.h"

void SolucionSecuencia::Print(std::ostream& os) const {
  os << "SolucionSecuencia: [";
  for (size_t i = 0; i < solucion_.size(); ++i) {
      os << solucion_[i] << (i < solucion_.size() - 1 ? ", " : "");
  }
  os << "]";
}