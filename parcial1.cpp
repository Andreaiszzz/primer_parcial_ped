#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int kMaxPuntos = 10;


struct PuntoTrayectoria {
  int id;
  string nombre;
  float coordenadas[3];
  float distanciaOrigen;
  string clasificacion;
};

void registrarPunto(PuntoTrayectoria &punto);
float calcularDistancia(PuntoTrayectoria *punto);
void clasificarPunto(PuntoTrayectoria &punto);
PuntoTrayectoria* obtenerPuntoMasAlejado(PuntoTrayectoria puntos[], int cantidad);
void corregirCoordenadas(PuntoTrayectoria &punto, float desplazamientoX,
                         float desplazamientoY, float desplazamientoZ);
void generarInforme(PuntoTrayectoria puntos[], int cantidad);

void mostrarEncabezado();
void mostrarPunto(const PuntoTrayectoria &punto);
void procesarTodos(PuntoTrayectoria puntos[], int cantidad);
int leerEntero(const string &mensaje, int minimo, int maximo);
float leerFlotante(const string &mensaje);
string floatATexto(float valor);
string rellenarDerecha(const string &texto, int ancho);
string rellenarIzquierda(const string &texto, int ancho);

void registrarPunto(PuntoTrayectoria &punto) {
  punto.id = leerEntero("  Identificador: ", -1000000, 1000000);

  cout << "  Nombre o descripcion: ";
  getline(cin, punto.nombre);
  if (punto.nombre.empty()) {
    punto.nombre = "SIN NOMBRE";
  }

  punto.coordenadas[0] = leerFlotante("  Coordenada X: ");
  punto.coordenadas[1] = leerFlotante("  Coordenada Y: ");
  punto.coordenadas[2] = leerFlotante("  Coordenada Z: ");

  punto.distanciaOrigen = 0.0f;
  punto.clasificacion = "SIN CLASIFICAR";
}

float calcularDistancia(PuntoTrayectoria *punto) {
  float x = punto->coordenadas[0];
  float y = punto->coordenadas[1];
  float z = punto->coordenadas[2];

  float distancia = sqrt((x * x) + (y * y) + (z * z));

  punto->distanciaOrigen = distancia;
  return distancia;
}

void clasificarPunto(PuntoTrayectoria &punto) {
  if (punto.distanciaOrigen <= 5.0f) {
    punto.clasificacion = "CERCANO";
  } else if (punto.distanciaOrigen <= 10.0f) {
    punto.clasificacion = "INTERMEDIO";
  } else if (punto.distanciaOrigen <= 20.0f) {
    punto.clasificacion = "LEJANO";
  } else {
    punto.clasificacion = "EXTREMO";
  }
}
void procesarTodos(PuntoTrayectoria puntos[], int cantidad) {
  for (PuntoTrayectoria *p = puntos; p < puntos + cantidad; p++) {
    calcularDistancia(p);
    clasificarPunto(*p);
  }
}

PuntoTrayectoria* obtenerPuntoMasAlejado(PuntoTrayectoria puntos[], int cantidad) {
  if (cantidad <= 0) {
    return NULL;
  }

  PuntoTrayectoria *mas_alejado = &puntos[0];

  for (int i = 1; i < cantidad; i++) {
    if (puntos[i].distanciaOrigen > mas_alejado->distanciaOrigen) {
      mas_alejado = &puntos[i];
    }
  }

  return mas_alejado;
}

void corregirCoordenadas(PuntoTrayectoria &punto, float desplazamientoX,
                         float desplazamientoY, float desplazamientoZ) {
  punto.coordenadas[0] = punto.coordenadas[0] + desplazamientoX;
  punto.coordenadas[1] = punto.coordenadas[1] + desplazamientoY;
  punto.coordenadas[2] = punto.coordenadas[2] + desplazamientoZ;
}

void generarInforme(PuntoTrayectoria puntos[], int cantidad) {
  int cercanos = 0;
  int intermedios = 0;
  int lejanos = 0;
  int extremos = 0;
  float suma_distancias = 0.0f;

  cout << "\n INFORME DE TRAYECTORIA "
          \n";
  mostrarEncabezado();

  for (int i = 0; i < cantidad; i++) {
    mostrarPunto(puntos[i]);

    suma_distancias = suma_distancias + puntos[i].distanciaOrigen;

    if (puntos[i].clasificacion == "CERCANO") {
      cercanos++;
    } else if (puntos[i].clasificacion == "INTERMEDIO") {
      intermedios++;
    } else if (puntos[i].clasificacion == "LEJANO") {
      lejanos++;
    } else if (puntos[i].clasificacion == "EXTREMO") {
      extremos++;
    }
  }


  cout << "Puntos CERCANOS    : " << cercanos << "\n";
  cout << "Puntos INTERMEDIOS : " << intermedios << "\n";
  cout << "Puntos LEJANOS     : " << lejanos << "\n";
  cout << "Puntos EXTREMOS    : " << extremos << "\n";

  if (cantidad > 0) {
    float promedio = suma_distancias / cantidad;
    cout << "Distancia promedio : " << floatATexto(promedio) << "\n";
  }

string rellenarDerecha(const string &texto, int ancho) {
  string resultado = texto;
  while ((int)resultado.length() < ancho) {
    resultado = resultado + " ";
  }
  return resultado;
}

string rellenarIzquierda(const string &texto, int ancho) {
  string resultado = texto;
  while ((int)resultado.length() < ancho) {
    resultado = " " + resultado;
  }
  return resultado;
}

string floatATexto(float valor) {
  bool negativo = valor < 0.0f;
  if (negativo) {
    valor = -valor;
  }

  long centesimas = (long)round(valor * 100.0f);
  long parteEntera = centesimas / 100;
  long parteDecimal = centesimas % 100;

  string textoDecimal = to_string(parteDecimal);
  if (parteDecimal < 10) {
    textoDecimal = "0" + textoDecimal;
  }

  string resultado = to_string(parteEntera) + "." + textoDecimal;
  if (negativo) {
    resultado = "-" + resultado;
  }
  return resultado;
}

void mostrarEncabezado() {
  cout << rellenarDerecha("ID", 6) << rellenarDerecha("NOMBRE", 20)
       << rellenarIzquierda("X", 10) << rellenarIzquierda("Y", 10)
       << rellenarIzquierda("Z", 10) << rellenarIzquierda("DISTANCIA", 12)
       << "   " << "CLASIFICACION" << "\n";


void mostrarPunto(const PuntoTrayectoria &punto) {
  cout << rellenarDerecha(to_string(punto.id), 6)
       << rellenarDerecha(punto.nombre, 20)
       << rellenarIzquierda(floatATexto(punto.coordenadas[0]), 10)
       << rellenarIzquierda(floatATexto(punto.coordenadas[1]), 10)
       << rellenarIzquierda(floatATexto(punto.coordenadas[2]), 10)
       << rellenarIzquierda(floatATexto(punto.distanciaOrigen), 12)
       << "   " << punto.clasificacion << "\n";
}

int leerEntero(const string &mensaje, int minimo, int maximo) {
  int valor = 0;
  bool valido = false;

  while (!valido) {
    cout << mensaje;
    cin >> valor;

    if (cin.fail() || valor < minimo || valor > maximo) {
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "  Valor invalido. Debe estar entre " << minimo << " y "
           << maximo << ".\n";
    } else {
      cin.ignore(10000, '\n');
      valido = true;
    }
  }

  return valor;
}

float leerFlotante(const string &mensaje) {
  float valor = 0.0f;
  bool valido = false;

  while (!valido) {
    cout << mensaje;
    cin >> valor;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "  Valor invalido. Ingrese un numero.\n";
    } else {
      cin.ignore(10000, '\n');
      valido = true;
    }
  }

  return valor;
}
int main() {
  PuntoTrayectoria puntos[kMaxPuntos];
  int cantidad = 0;
  bool registrados = false;
  int opcion = 0;


  cout << "   ANALISIS DE TRAYECTORIA - ROBOT AUTONOMO\n";


  do {
    cout << "\n--------------- MENU ---------------\n";
    cout << "1. Registrar puntos de trayectoria\n";
    cout << "2. Calcular distancias y clasificar\n";
    cout << "3. Mostrar el punto mas alejado\n";
    cout << "4. Corregir coordenadas de un punto\n";
    cout << "5. Generar informe de trayectoria\n";
    cout << "6. Salir\n";
    cout << "------------------------------------\n";

    opcion = leerEntero("Seleccione una opcion: ", 1, 6);

    if (opcion == 1) {
      cantidad = leerEntero("\nCantidad de puntos a registrar (1-10): ", 1,
                            kMaxPuntos);

      for (int i = 0; i < cantidad; i++) {
        cout << "\n--- Punto " << (i + 1) << " de " << cantidad << " ---\n";
        registrarPunto(puntos[i]);
      }

      registrados = true;
      cout << "\nRegistro completado correctamente.\n";

    } else if (opcion == 2) {
      if (!registrados) {
        cout << "\nPrimero debe registrar los puntos (opcion 1).\n";
      } else {
        procesarTodos(puntos, cantidad);

        cout << "\n--- DISTANCIAS Y CLASIFICACIONES ---\n";
        mostrarEncabezado();
        for (int i = 0; i < cantidad; i++) {
          mostrarPunto(puntos[i]);
        }
      }

    } else if (opcion == 3) {
      if (!registrados) {
        cout << "\nPrimero debe registrar los puntos (opcion 1).\n";
      } else {
        procesarTodos(puntos, cantidad);

        PuntoTrayectoria *mas_alejado = obtenerPuntoMasAlejado(puntos, cantidad);

        if (mas_alejado != NULL) {
          cout << "\n--- PUNTO MAS ALEJADO DEL ORIGEN ---\n";
          cout << "ID            : " << mas_alejado->id << "\n";
          cout << "Nombre        : " << mas_alejado->nombre << "\n";
          cout << "Coordenada X  : " << floatATexto(mas_alejado->coordenadas[0]) << "\n";
          cout << "Coordenada Y  : " << floatATexto(mas_alejado->coordenadas[1]) << "\n";
          cout << "Coordenada Z  : " << floatATexto(mas_alejado->coordenadas[2]) << "\n";
          cout << "Distancia     : " << floatATexto(mas_alejado->distanciaOrigen) << "\n";
          cout << "Clasificacion : " << mas_alejado->clasificacion << "\n";
        }
      }

    } else if (opcion == 4) {
      if (!registrados) {
        cout << "\nPrimero debe registrar los puntos (opcion 1).\n";
      } else {
        cout << "\n--- CORRECCION DE COORDENADAS ---\n";
        for (int i = 0; i < cantidad; i++) {
          cout << (i + 1) << ") ID " << puntos[i].id << " - "
               << puntos[i].nombre << "\n";
        }

        int seleccion = leerEntero("Seleccione el punto a corregir: ", 1,
                                   cantidad);
        int indice = seleccion - 1;

        float dx = leerFlotante("  Desplazamiento X: ");
        float dy = leerFlotante("  Desplazamiento Y: ");
        float dz = leerFlotante("  Desplazamiento Z: ");

        corregirCoordenadas(puntos[indice], dx, dy, dz);

        calcularDistancia(&puntos[indice]);
        clasificarPunto(puntos[indice]);

        cout << "\n--- NUEVOS RESULTADOS ---\n";
        mostrarEncabezado();
        mostrarPunto(puntos[indice]);
      }

    } else if (opcion == 5) {
      if (!registrados) {
        cout << "\nPrimero debe registrar los puntos (opcion 1).\n";
      } else {
        procesarTodos(puntos, cantidad);
        generarInforme(puntos, cantidad);
      }

    } else if (opcion == 6) {
      cout << "\nSaliendo del programa. Hasta luego.\n";
    }

  } while (opcion != 6);

  return 0;
}
