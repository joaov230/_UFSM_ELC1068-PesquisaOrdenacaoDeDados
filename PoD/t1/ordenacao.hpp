#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

/** ORDENAÇÃO INTERNA **/

void merge (int vet[], int init, int meio, int fim);

void mergeSort(int vet[], int init, int fim);



/** MANIPULAÇÃO DE ARQUIVOS **/

fstream openFile (string name);



/** ORDENAÇÃO EXTERNA **/
