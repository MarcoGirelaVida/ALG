/*
Marco Girela Vida 2ºB3

Implementación de quicksort en C++

Hecha a partir de la explicación del algortimo (bastante buena) de este video
de geeksforgeeks: https://www.geeksforgeeks.org/videos/quick-sort-sde-sheet/

Con la variación de que se escoge el pivote como el medio del primero, mediano
y último que está extraida de la sección "Implementation Issues" de la
wikipediaen inglés: https://en.wikipedia.org/wiki/Quicksort
*/
#include "tuercas_tornillos.hpp"

void serializar_contenidos(int tuercas[], int tornillos[], size_t n)
{
	cerr << "Elementos tuercas:   ";
	for (size_t i = 0; i < n; i++)
		cerr << tuercas[i] << " ";
	cerr << endl;

	cerr << "Elementos tornillos: ";
	for (size_t i = 0; i < n; i++)
		cerr << tornillos[i] << " ";
	cerr << endl;
}

// Función para intercambiar 
void swap(int * pos1, int * pos2)
{
    int tmp = *pos1;
    *pos1 = *pos2;
    *pos2 = tmp;
}

int particionar_tuneado(int array1[], int array2[], int start, int end)
{
    int pivot = array1[end]; 
    int insertion_point = start;

    for (int i = start; i < end; i++){
        if (array2[i] == pivot)
            swap(&array2[i], &array2[end]);
        
        if (array2[i] <= pivot){
            swap(&array2[insertion_point], &array2[i]);
            insertion_point++;
        }
    }
    return insertion_point;
}

void tuercas_tornillos (int array1[], int array2[], int start, int end)
{
    if (start < end){
        particionar_tuneado(array1, array2, start, end);
        int ubicacion_pivote = particionar_tuneado(array2, array1, start, end);
        swap(&array2[ubicacion_pivote], &array2[end]);
        swap(&array1[ubicacion_pivote], &array1[end]);
        
        tuercas_tornillos(array1, array2, start, ubicacion_pivote - 1);
        tuercas_tornillos(array1, array2, ubicacion_pivote + 1, end);
    }
}

void tuercas_tornillos_fuerza_bruta (int array1[], int array2[], int start, int end)
{
    for (size_t i = 0; i < end; i++)
        for (size_t j = 0; j < end; j++)
            if (array1[i] == array2[j])
                swap(&array2[i], &array2[j]);
}