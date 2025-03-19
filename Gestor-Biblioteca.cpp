#include "Connection.h"
#include "Ingresar_libros.h"
#include <iostream>

using namespace std;

int main() {
    try {
        PGconn *conn = conectarDB();
        if (!conn)
            throw runtime_error("No se pudo establecer conexión con la base de datos.");

        Libro libro(conn);
        libro.ingresarDatos();
        libro.guardarEnDB();

        PQfinish(conn);
    } catch (const exception &e) {
        cerr << "Error crítico: " << e.what() << endl;
    }

    cout << "Presiona Enter para salir..." << endl;
    cin.get();
    return 0;
}
