#include <iostream>
#include <libpq-fe.h>

int main()
{
    std::cout << "inicia programa de conexion db." << std::endl;
    const char *conninfo = "dbname=postgres user=postgres password=Myroot host=localhost port=5432";
    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK)
    {
        std::cerr << "Error de conexión: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return 1;
    }
    else
    {
        std::cout << "Conexión exitosa" << std::endl;

        PQfinish(conn);

        return 0;
    }
}