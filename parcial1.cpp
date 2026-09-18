#include <iostream>
using namespace std;

struct PuntoTrayectoria {
    int identificador;
    int nombre;
    float coordenada_x;
    float coordenada_y;
    float coordenada_z;
    };
PuntoTrayectoria trayectoria[10];
void registrarPuntos() {
    for (int i = 0; i < 10; i++) {
        trayectoria[i].identificador = i + 1;
        trayectoria[i].nombre = i + 1;
        trayectoria[i].coordenada_x = 0.0f;
        trayectoria[i].coordenada_y = 0.0f;
        trayectoria[i].coordenada_z = 0.0f;
    }
}
int main() {
    registrarPuntos();  
    return 0;
}