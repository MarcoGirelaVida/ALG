#include <chrono>
#include <iostream>
#include <algorithm>
#include <random>
#include <fstream> // Para usar ficheros

#include "tuercas_tornillos.hpp"
using namespace std;

// Hecho por chatgpt
void shuffleArray(int* arr, int size) {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(arr, arr + size, rng);
}

int* copia_profunda(int* originalArray, size_t tamanio) {
    int* array_copia = new int[tamanio];
    
    for (int i = 0; i < tamanio; ++i)
        array_copia[i] = originalArray[i];
    
    return array_copia;
}

size_t ejecutar_funcion(void (*func)(int*, int*, int, int),int tuercas[], int tornillos[], size_t n)
{
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
	func(tuercas, tornillos, 0, n);
	tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
	
	return std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
}

int main(int argc, char *argv[])
{
	ofstream fsalida;
	size_t tejecucion_divide, tejecucion_fbruta;

	if (argc < 4)
	{
		cerr << endl;
		cerr << "Error: El programa se debe ejecutar de la siguiente forma." << endl << endl;;
		cerr << argv[0] << "nombre_fichero mostrar_contenidos(1 si, 0 no) tamCaso1 tamCaso2 ... n" << endl << endl;;
		return 0;
	}

	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}

	// Cogemos el tamaño del caso
	bool mostrar_contenidos = atoi(argv[2]);

	// Pasamos por cada tamaño de caso
	for (size_t arg= 3; arg < argc; arg++)
	{		
		size_t n = atoi(argv[arg]);
		
		// Reservamos memoria para el vector
		int *tuercas= new int[n];
		int *tornillos= new int[n];
		
		// Llenamos ambos vectores con n elementos ordenados
		for (size_t i = 0; i < n; i++){
			tuercas[i]= i;
			tornillos[i]= i;
		}
		
		// Desordenamos los vectores
		shuffleArray(tuercas, n);
		shuffleArray(tornillos, n);

		// Los copio para poder usar el mismo vector en fuerza bruta y que estén en igualdad de condiciones
		int *copia_tuercas = copia_profunda(tuercas, n);
		int *copia_tornillos = copia_profunda(tornillos, n);


		cout << endl << "------- TAMANIO " << n << " --------" << endl;
		if (mostrar_contenidos && n < 15)
		{
			cout << "Elementos desordenados: " << endl;
			serializar_contenidos(tuercas, tornillos, n);
		}
		//--------------------------------------------------------------------------//
		cout << "Ejecutando Solución al problema con divide y venceras: " << endl;
		tejecucion_divide = ejecutar_funcion(tuercas_tornillos, tuercas, tornillos, n);
		cout << "\tTiempo de ejec. (us): " <<  tejecucion_divide << " con divide y vecenceras" << endl;

		if (mostrar_contenidos && n < 15)
		{
			cout << "Elementos ordenados con divide y venceras: " << endl;
			serializar_contenidos(tuercas, tornillos, n);
		}
		
		//--------------------------------------------------------------------------//
		cerr << "Ejecutando Solución al problema con fuerza bruta: " << endl;
		tejecucion_fbruta = ejecutar_funcion(tuercas_tornillos_fuerza_bruta, copia_tuercas, copia_tornillos, n);
		cout << "\tTiempo de ejec. (us): " << tejecucion_fbruta << " con fuerza bruta" << endl;

		if (mostrar_contenidos && n < 15)
		{
			cout << "Elementos ordenados con fuerza bruta: " << endl;
			serializar_contenidos(copia_tuercas, copia_tornillos, n);
		}

		//--------------------------------------------------------------------------//
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida << n << ", " << tejecucion_divide << ", " << tejecucion_fbruta << endl;

		// Liberamos memoria del vector
		delete [] tuercas, tornillos, copia_tuercas, copia_tornillos;
	}

	// Cerramos fichero de salida
	fsalida.close();

	return 0;
}
