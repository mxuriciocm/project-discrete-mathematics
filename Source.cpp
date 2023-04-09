#include <iostream>
#include "Header.h"
using namespace std;

int main() {
    int opcion;

    do {
        cout << "===== Menu =====" << endl;
        cout << "1. Producto Carteasiano" << endl;
        cout << "2. Salir" << endl;

        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Ha elegido la opcion 1." << endl;
            producto_cartesiano();
            break;
        case 2:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
            break;
        }
    } while (opcion != 2);

    return 0;
}