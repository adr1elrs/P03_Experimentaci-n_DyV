

#include "../lib/instancia_secuencia.h"

InstanciaSecuencia::InstanciaSecuencia(int n) {
  secuencia_.reserve(n);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 10000);
  for (int i = 0; i < n; ++i) {
    secuencia_.push_back(dis(gen));
  }
}


InstanciaSecuencia::InstanciaSecuencia(std::string nombre_fichero) {
  std::ifstream fichero(nombre_fichero);
  if (!fichero.is_open()) {
    std::cerr << "Error al abrir el archivo: " << nombre_fichero << std::endl;
    return;
  }

  int numero_elementos;
  fichero >> numero_elementos;

  for (int i = 0; i < numero_elementos; ++i) {
    int elemento;
    fichero >> elemento;
    secuencia_.push_back(elemento);
  }

  fichero.close();
}

void InstanciaSecuencia::Print(std::ostream& os) const {
  os << "InstanciaSecuencia: [";
  for (size_t i = 0; i < secuencia_.size(); ++i) {
      os << secuencia_[i] << (i < secuencia_.size() - 1 ? ", " : "");
  }
  os << "]";
}