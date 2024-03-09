/*
Marco Girela Vida 2ºB3

Implementación de quicksort en C++

Inspirada en la implementación de este video de geeksforgeeks donde se explica bastante
bien su funcionamiento: https://www.geeksforgeeks.org/videos/quick-sort-sde-sheet/
*/

#include "quicksort.hpp"

// Función para intercambiar 
void swap(int * pos1, int * pos2)
{
    int tmp = *pos1;
    *pos1 = *pos2;
    *pos2 = tmp;
}

// Función que organiza los elementos a la izquierda (si son menores)
// o derecha (si son mayores) del pivote
// Será la función que se repita por cada iteración recursiva.
// arr: Vector donde se aplica la función.
// low: Punto de inicio de la partición que se quiere particionar.
// high: Punto de fin de dicha partición.
// En esta implementación se elige como pivote el último elemento.
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int insertion_point = (low - 1);

    for (int i = low; i < high; i++)
    {
        if (arr[i] <= pivot)
        {
            insertion_point++;
            swap(&arr[insertion_point], &arr[i]);
        }
    }

    swap(&arr[insertion_point + 1], &arr[high]);

    return (insertion_point + 1);
}

// Función principal recursiva.
// Hasta que no se llegue al caso base (el vector está ordenado)
// se particiona el vector en la sección dada y se aplica de nuevo
// la función en las subsecciones restantes
void quicksort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}