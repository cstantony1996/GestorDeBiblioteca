#include <iostream>
#include <libpq-fe.h>

using namespace std;

int main()
{
    cout << "inicia programa de conexion db." << endl;
    const char *conninfo = "dbname=postgres user=postgres password=Myroot host=localhost port=5432";
    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK)
    {
        cerr << "Error de conexión: " << PQerrorMessage(conn) << endl;
        PQfinish(conn);
        return 1;
    }
    else
    {
        cout << "Conexión exitosa" << endl;

        PQfinish(conn);

        return 0;
    }
}