#ifndef INGRESAR_LIBROS_H
#define INGRESAR_LIBROS_H

#include <iostream>
#include <libpq-fe.h>
#include <stdexcept>

using namespace std;

class Libro {
private:
    string titulo, autor, isbn, editorial, materia;
    string año_publicacion;
    PGconn *conn;

public:
    Libro(PGconn *conexion);

    void ingresarDatos();
    bool isbnExiste();
    void guardarEnDB();
};

#endif
