#include "ordenacao.hpp"



/**************** ORDENAÇÃO INTERNA ****************/

// Segundo vet aux (de meio+1 até fim)
// Segundo vet aux (de meio+1 até fim)
// Da merge dos dois sub vet no vet novamente

void merge (int vet[], int init, int meio, int fim) {
  int pt1 = 1 + meio - init;
  int pt2 = fim - meio;

  int aux1[pt1], aux2[pt2];

  for (int i = 0; i < pt1; i++) {
    aux1[i] = vet[init + i];
  }
  for (int j = 0; j < pt2; j++) {
    aux2[j] = vet[j + meio + 1];
  }

  // Da merge ja ordenando os vetores
  // k -> pos do primeiro vet original
  // i -> pos do primeiro vet aux
  // j -> pos do segundo vet aux
  int k = init, i = 0, j = 0;

  while (i < pt1 && j < pt2) {
    if (aux1[i] <= aux2[j]) {
      vet[k] = aux1[i];
      i++;
    } else {
      vet[k] = aux2[j];
      j++;
    }
    k++;
  }

  // Termina de passar os elementos de aux1 pra vet
  // Termina de passar os elementos de aux2 pra vet
  while (i < pt1) {
    vet[k] = aux1[i];
    i++;
    k++;
  }
  while (j < pt2) {
    vet[k] = aux2[j];
    j++;
    k++;
  }
}


// init = primeira metade do vet
// fim = segunda metade do vet
// Ordena as duas metades
void mergeSort(int vet[], int init, int fim) {
  if (init < fim) {
    // Começa do init e vai pra metade do mesmo
    int meio = init+(fim-init)/2;

    mergeSort(vet, init, meio);
    mergeSort(vet, meio+1, fim);

    merge(vet, init, meio, fim);
  }
}


/**************** MANIPULAÇÃO DE ARQUIVOS ****************/


fstream openFile (string name) {
  fstream f;
  f.open(name);
  if (!f.is_open()) {
    cout << "\n\n-- ERRO AO ABRIR ARQUIVO --\n\n";
    exit(1);
  }
  return f;
}



/**************** ORDENAÇÃO EXTERNA ****************/


void externalSort (string name) {
  fstream foriginal, fin[3], fout[3];

  // Ler os caracteres por byte (char por char)
  // Limite: 10 bytes na memória INTERNA

  // Passar de char pra int -> mergeSort
  // mergeSort -> int para char
  // Escreve no arquivo de ENTRADA
  // Repete até chegar no fim do arquivo principal

  // Aqui começa a verdadeira ordenação externa
  // Fazer função auxiliar recursiva (ou num laço até estar tudo ordenado?)
  // Merge entre arquivos de entrada -> arquivos de saída
  // Repete invertendo os arquivos de entrada com os de saída

  // Se for verificar se tá tudo ordenado, verificar o arquivo inteiro de saída pra ver se
  // está ordenado

}
