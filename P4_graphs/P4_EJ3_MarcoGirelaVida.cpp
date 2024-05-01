#include <iostream>
#include <queue>
#include <vector>
using namespace std;

enum movimiento {arriba, derecha, abajo, izquierda};
typedef vector<vector<char>> tablero;
typedef pair<size_t, size_t> posicion;

struct paso
{
    posicion pos;
    movimiento mov;
};

void mostrar_casillas_movibles(const queue<posicion> &casillas_movibles)
{
    queue<posicion> tmp = casillas_movibles;

    while (not tmp.empty())
    {
        cout << "\t\tCASILLA: " << "[" << tmp.front().first << "][" << tmp.front().second << "]" << endl;
        tmp.pop();
    }
}

void mostrar_pasos(const queue<paso> &pasos)
{
    queue<paso> tmp = pasos;
    size_t num_paso = 1;

    while (not tmp.empty())
    {
        cout << "PASO " << num_paso << ": " << endl;
        cout << "\t" << "fil: " << tmp.front().pos.first << endl; 
        cout << "\t" << "col: " << tmp.front().pos.second << endl;
        cout << "\t" << "movimiento: " << (int) tmp.front().mov << endl;
        cout << "--------------------" << endl << endl;

        ++num_paso;
        tmp.pop();
    }
}

template<typename T>
void vaciar_cola (queue<T> &cola)
{
    while (!cola.empty())
        cola.pop();
}

bool paso_valido(const paso &p, const tablero &t)
{
    switch (p.mov)
    {
    case arriba:
        return (p.pos.first > 1) and t[p.pos.first-1][p.pos.second] == 'B' and t[p.pos.first-2][p.pos.second] == 'V';
    case derecha:
        return (p.pos.second < t.size() - 2) and t[p.pos.first][p.pos.second+1] == 'B' and t[p.pos.first][p.pos.second+2] == 'V';
    case abajo:
        return (p.pos.first < t.size() - 2) and t[p.pos.first+1][p.pos.second] == 'B' and t[p.pos.first+2][p.pos.second] == 'V';
    case izquierda:
        return (p.pos.second > 1) and t[p.pos.first][p.pos.second-1] == 'B' and t[p.pos.first][p.pos.second-2] == 'V';
    default:
        cerr << "ERROR EN PASO_VÁLIDO" << endl;
        break;
    }

    return false;
}

tablero ejecutar_paso(const paso &p, const tablero &t)
{
    tablero resultado = t;

    if (paso_valido(p, t))
    {
        resultado[p.pos.first][p.pos.second] = 'V'; 
        switch (p.mov)
        {
        case arriba:
            resultado[p.pos.first-1][p.pos.second] = 'V'; resultado[p.pos.first-2][p.pos.second] = 'B';
            break;
        case derecha:
            resultado[p.pos.first][p.pos.second+1] = 'V'; resultado[p.pos.first][p.pos.second+2] = 'B';
            break;
        case abajo:
            resultado[p.pos.first+1][p.pos.second] = 'V'; resultado[p.pos.first+2][p.pos.second] = 'B';
            break;
        case izquierda:
            resultado[p.pos.first][p.pos.second-1] = 'V'; resultado[p.pos.first][p.pos.second-2] = 'B';
            break;
        }
    }

    return resultado;
}

queue<posicion> localizar_casillas_movibles (const tablero &t)
{
    queue<posicion> casillas_movibles;
    paso paso_aux;
    posicion casilla_i;
    for (size_t fil = 0; fil < t.size(); fil++) {
        for (size_t col = 0; col < t.size(); col++) {
            if (t[fil][col] == 'B')
            {
                casilla_i = paso_aux.pos = make_pair(fil, col);
                bool es_movible = false;

                for (size_t i = 0; i < 4 and not es_movible; i++)
                {
                    //cerr << "FIL: " << fil << endl;
                    //cerr << "COL: " << col << endl;
                    //cerr <<  endl;
                    paso_aux.mov = (movimiento) i;
                    if ((es_movible = paso_valido(paso_aux, t)))
                        casillas_movibles.push(casilla_i);
                }
            }
        }
    }
    return casillas_movibles;
}

void algoritmo_backtraking(queue<paso> &solucion, tablero &t)
{
    queue<paso> cola_vacia;
    queue<posicion> casillas_movibles = localizar_casillas_movibles(t);

    cout << "\tCASILLAS MOVIBLES: " << endl;
    mostrar_casillas_movibles(casillas_movibles);
    cout << "--------------------" << endl << endl;

    paso paso_aux;
    tablero tablero_hijo;

    while (solucion.empty() and !casillas_movibles.empty())
    {
        paso_aux.pos = casillas_movibles.front();

        for (int mov_i = 0; mov_i < 4 and solucion.empty(); mov_i++)
        {
            paso_aux.mov = (movimiento) mov_i;
            if (paso_valido(paso_aux, t))
            {
                cout << "------ NUEVO PASO ------" << endl;
                cout << "\t" << "fil: " << paso_aux.pos.first << endl; 
                cout << "\t" << "col: " << paso_aux.pos.second << endl;
                cout << "\t" << "movimiento: " << (int) paso_aux.mov << endl;

                tablero_hijo = ejecutar_paso(paso_aux, t);
                solucion.push(paso_aux);
                algoritmo_backtraking(solucion, tablero_hijo);

                // Si no es una solución válida (resultado), vacío la solución
                if (solucion.size() < 31) solucion = cola_vacia;
            }
        }
        casillas_movibles.pop();
    }
}

queue<paso> buscar_solucion (tablero &t)
{
    queue<paso> solucion, cola_vacia;
    queue<posicion> casillas_movibles = localizar_casillas_movibles(t);
    cout << "CASILLAS MOVIBLES INICIALES: " << endl;
    mostrar_casillas_movibles(casillas_movibles);
    tablero tablero_hijo;
    paso paso_aux;

    while (solucion.empty() and !casillas_movibles.empty())
    {
        paso_aux.pos = casillas_movibles.front();

        // Para cada bola movible busco sus posibles movimientos y les aplico el algoritmo de backtraking
        // Si tras ejecutar el algoritmo encuentra una solución para y sale, sino busa su siguient posible movimiento
        for (int mov_i = 0; mov_i < 4 and solucion.empty(); mov_i++)
        {
            paso_aux.mov = (movimiento) mov_i;
            if (paso_valido(paso_aux, t))
            {
                cout << "---- NUEVO PASO INICIAL ----" << endl;
                cout << "\t" << "fil: " << paso_aux.pos.first << endl; 
                cout << "\t" << "col: " << paso_aux.pos.second << endl;
                cout << "\t" << "movimiento: " << (int) paso_aux.mov << endl;

                tablero_hijo = ejecutar_paso(paso_aux, t);
                solucion.push(paso_aux);
                algoritmo_backtraking(solucion, tablero_hijo);

                // Si no es una solución válida (resultado), vacío la solución
                if (solucion.size() < 31) solucion = cola_vacia;
            }
        }

        casillas_movibles.pop();
    }
    
    return solucion;
}

int main()
{
    tablero tablero_inicial = 
    {
        {'X', 'X', 'B', 'B', 'B', 'X', 'X'},
        {'X', 'X', 'B', 'B', 'B', 'X', 'X'},
        {'B', 'B', 'B', 'B', 'B', 'B', 'B'},
        {'B', 'B', 'B', 'V', 'B', 'B', 'B'},
        {'B', 'B', 'B', 'B', 'B', 'B', 'B'},
        {'X', 'X', 'B', 'B', 'B', 'X', 'X'},
        {'X', 'X', 'B', 'B', 'B', 'X', 'X'}
    };

    queue<paso> solucion = buscar_solucion(tablero_inicial);

    mostrar_pasos(solucion);

    return 0;
}