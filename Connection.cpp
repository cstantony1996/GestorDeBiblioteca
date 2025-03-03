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

        std::string nombre, direccion, nit;
        std::cout << "Ingrese nombre: ";
        std::getline(std::cin, nombre);
        std::cout << "Ingrese dirección: ";
        std::getline(std::cin, direccion);
        std::cout << "Ingrese NIT: ";
        std::getline(std::cin, nit);

        // insert de valores
        const char *paramValues[3] = {nombre.c_str(), direccion.c_str(), nit.c_str()};
        const char *insertQuery = "INSERT INTO clientes (nombre, direccion, nit) VALUES ($1, $2, $3)";
        //const char *insertQuery = "INSERT INTO clientes (nombre, direccion, nit) VALUES ('Juan Peres', 'Reforma 12', '12345678')";

        //PGresult *insertRes = PQexec(conn, insertQuery);
        PGresult *insertRes = PQexecParams(conn, insertQuery, 3, NULL, paramValues, NULL, NULL, 0);


        if (PQresultStatus(insertRes) != PGRES_COMMAND_OK)
        {
            std::cerr << "Error al insertar datos: " << PQerrorMessage(conn) << std::endl;
            PQclear(insertRes);
            PQfinish(conn);
            return 1;
        }
        else
        {
            std::cout << "valores insertados en la DB correctamente" << std::endl;
        }

        const char *query = "SELECT * FROM clientes";
        PGresult *res = PQexec(conn, query);

        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
            std::cerr << "Error en la consulta: " << PQerrorMessage(conn) << std::endl;
            PQclear(res);
            PQfinish(conn);
            return 1;
        }

        int nrows = PQntuples(res);
        int ncols = PQnfields(res);

        // Mostrar los nombres de las columnas
        for (int j = 0; j < ncols; ++j)
        {
            std::cout << PQfname(res, j) << "\t";
        }
        std::cout << std::endl;

        // Mostrando los datos.
        for (int i = 0; i < nrows; ++i)
        {
            for (int j = 0; j < ncols; ++j)
            {
                std::cout << PQgetvalue(res, i, j) << "\t";
            }
            std::cout << std::endl;
        }

        PQclear(res);
        PQfinish(conn);

        return 0;
    }
}