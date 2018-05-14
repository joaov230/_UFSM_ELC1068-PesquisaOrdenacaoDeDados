#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

/** ORDENAÇÃO INTERNA **/

void merge (int vet[], int init, int meio, int fim);

void mergeSort(int vet[], int init, int fim);



/** MANIPULAÇÃO DE ARQUIVOS **/

// void arquivoParaVetores (fstream f, string strChar, vector<int> vetInt);



/** ORDENAÇÃO EXTERNA **/

void externalSort (string name);
