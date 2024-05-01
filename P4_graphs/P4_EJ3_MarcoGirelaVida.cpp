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

void mostrar_casillas_movibles(const queue<posicion> &casillas_movibles);
void mostrar_paso(const tablero &t, const queue<posicion> &casillas_movibles, const paso &paso_hijo);
void mostrar_pasos(const queue<paso> &pasos, const tablero &t);
queue<paso> buscar_solucion (tablero &t);
bool paso_valido(const paso &p, const tablero &t);
tablero ejecutar_paso(const paso &p, const tablero &t);
queue<posicion> localizar_casillas_movibles (const tablero &t);
void algoritmo_backtraking(queue<paso> &solucion, tablero &t);

void mostrar_casillas_movibles(const queue<posicion> &casillas_movibles)
{
    queue<posicion> tmp = casillas_movibles;

    while (not tmp.empty())
    {
        cout << "[" << tmp.front().first << "][" << tmp.front().second << "]" << endl;
        tmp.pop();
    }
}

void mostrar_paso(const tablero &t, const queue<posicion> &casillas_movibles, const paso &paso_hijo)
{
    queue<posicion> c_tmp = casillas_movibles;
    tablero t_tmp = t;
    while (not c_tmp.empty())
    {
        t_tmp[c_tmp.front().first][c_tmp.front().second] = 'O';
        c_tmp.pop();
    }

    switch (paso_hijo.mov)
    {
    case arriba: t_tmp[paso_hijo.pos.first][paso_hijo.pos.second] = '^';      break;
    case derecha: t_tmp[paso_hijo.pos.first][paso_hijo.pos.second] = '>';     break;
    case abajo: t_tmp[paso_hijo.pos.first][paso_hijo.pos.second] = 'V';       break;
    case izquierda: t_tmp[paso_hijo.pos.first][paso_hijo.pos.second] = '<';   break;
    }


    cout << endl;
    cout << "------ NUEVO PASO ------" << endl;
    cout << "\t" << "fil: " << paso_hijo.pos.first << endl; 
    cout << "\t" << "col: " << paso_hijo.pos.second << endl;
    cout << "\t" << "movimiento: ";
    switch (paso_hijo.mov)
    {
    case arriba:        cout << "arriba" << endl;       break;
    case derecha:       cout << "derecha" << endl;      break;
    case abajo:         cout << "abajo" << endl;        break;
    case izquierda:     cout << "izquierda" << endl;    break;
    }

    cout << endl << "\t";
    for (size_t fil = 0; fil < t_tmp.size(); fil++) {
        for (size_t col = 0; col < t_tmp.size(); col++) {
            cout << "|" << t_tmp[fil][col];
        }
        cout << "|" << endl << "\t";
    }
    cout << endl;
    cout << "------------------------" << endl << endl;
}

void mostrar_pasos(const queue<paso> &pasos, const tablero &t)
{
    queue<paso> tmp = pasos;
    size_t num_paso = 1;
    queue<posicion> foo;
    tablero tablero_actual = t;

    while (not tmp.empty())
    {
        cout << "NUM[" << num_paso << "]" << endl;
        mostrar_paso(tablero_actual, foo, tmp.front());
        tablero_actual = ejecutar_paso(tmp.front(), tablero_actual);
        tmp.pop();
        num_paso++;
    }
}

bool paso_valido(const paso &p, const tablero &t)
{
    switch (p.mov)
    {
    case arriba:
        return (p.pos.first > 1) and t[p.pos.first-1][p.pos.second] == 'B' and t[p.pos.first-2][p.pos.second] == '-';
    case derecha:
        return (p.pos.second < t.size() - 2) and t[p.pos.first][p.pos.second+1] == 'B' and t[p.pos.first][p.pos.second+2] == '-';
    case abajo:
        return (p.pos.first < t.size() - 2) and t[p.pos.first+1][p.pos.second] == 'B' and t[p.pos.first+2][p.pos.second] == '-';
    case izquierda:
        return (p.pos.second > 1) and t[p.pos.first][p.pos.second-1] == 'B' and t[p.pos.first][p.pos.second-2] == '-';
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
        resultado[p.pos.first][p.pos.second] = '-'; 
        switch (p.mov)
        {
        case arriba:
            resultado[p.pos.first-1][p.pos.second] = '-'; resultado[p.pos.first-2][p.pos.second] = 'B';
            break;
        case derecha:
            resultado[p.pos.first][p.pos.second+1] = '-'; resultado[p.pos.first][p.pos.second+2] = 'B';
            break;
        case abajo:
            resultado[p.pos.first+1][p.pos.second] = '-'; resultado[p.pos.first+2][p.pos.second] = 'B';
            break;
        case izquierda:
            resultado[p.pos.first][p.pos.second-1] = '-'; resultado[p.pos.first][p.pos.second-2] = 'B';
            break;
        }
    }

    return resultado;
}

queue<posicion> localizar_casillas_movibles (const tablero &t)
{
    queue<posicion> casillas_movibles;
    paso paso_hijo;
    posicion casilla_i;
    for (size_t fil = 0; fil < t.size(); fil++) {
        for (size_t col = 0; col < t.size(); col++) {
            if (t[fil][col] == 'B')
            {
                casilla_i = paso_hijo.pos = make_pair(fil, col);
                bool es_movible = false;

                for (size_t i = 0; i < 4 and not es_movible; i++)
                {
                    paso_hijo.mov = (movimiento) i;
                    if ((es_movible = paso_valido(paso_hijo, t)))
                        casillas_movibles.push(casilla_i);
                }
            }
        }
    }
    return casillas_movibles;
}

void algoritmo_backtraking(queue<paso> &solucion, tablero &t)
{
    queue<paso> cola_vacia, solucion_base = solucion;
    queue<posicion> casillas_movibles, copia_cm;
    casillas_movibles = copia_cm = localizar_casillas_movibles(t);

    // CASO BASE (no tiene hijos)
    if (casillas_movibles.empty())
    {
        if(solucion.size() < 31)
        {
            //cout << "HAS PERDIDO" << endl;
            solucion = cola_vacia;
        }
        else
            cout << "SOLUCION ENCONTRADA!!" << endl;

        return;
    }

    // ------------------------------------------------------------
    // EN CASO DE QUE TENGA HIJOS
    paso paso_hijo;
    tablero tablero_hijo;

    // Mientras siga habiendo hijos sin explorar y no haya encontrado la solución, sigue escaneando hijos
    while (solucion.size() < 31 and !casillas_movibles.empty())
    {
        paso_hijo.pos = casillas_movibles.front();

        for (int mov_i = 0; mov_i < 4 and solucion.size() < 31; mov_i++)
        {
            paso_hijo.mov = (movimiento) mov_i;
            if (paso_valido(paso_hijo, t))
            {
                solucion = solucion_base;
                //mostrar_paso(t, copia_cm, paso_hijo);

                tablero_hijo = ejecutar_paso(paso_hijo, t);
                solucion.push(paso_hijo);


                algoritmo_backtraking(solucion, tablero_hijo);
            }
        }
        casillas_movibles.pop();
    }
    
}

queue<paso> buscar_solucion (tablero &t)
{
    queue<paso> solucion, cola_vacia;
    queue<posicion> casillas_movibles, copia_cm;
    casillas_movibles = copia_cm = localizar_casillas_movibles(t);
    tablero tablero_hijo;
    paso paso_hijo;

    while (solucion.size() < 31 and !casillas_movibles.empty())
    {
        paso_hijo.pos = casillas_movibles.front();

        // Para cada bola movible busco sus posibles movimientos y les aplico el algoritmo de backtraking
        // Si tras ejecutar el algoritmo encuentra una solución para y sale, sino busa su siguient posible movimiento
        for (int mov_i = 0; mov_i < 4 and solucion.size() < 31; mov_i++)
        {
            paso_hijo.mov = (movimiento) mov_i;
            if (paso_valido(paso_hijo, t))
            {
                solucion = cola_vacia;

                //mostrar_paso(t, copia_cm, paso_hijo);

                tablero_hijo = ejecutar_paso(paso_hijo, t);
                solucion.push(paso_hijo);

                algoritmo_backtraking(solucion, tablero_hijo);
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
        {'B', 'B', 'B', '-', 'B', 'B', 'B'},
        {'B', 'B', 'B', 'B', 'B', 'B', 'B'},
        {'X', 'X', 'B', 'B', 'B', 'X', 'X'},
        {'X', 'X', 'B', 'B', 'B', 'X', 'X'}
    };

    queue<paso> solucion = buscar_solucion(tablero_inicial);
    cerr << "FIN EJECUCION" << endl;
    cerr << "Tamaño solución: " << solucion.size() << endl;
    mostrar_pasos(solucion, tablero_inicial);

    return 0;
}