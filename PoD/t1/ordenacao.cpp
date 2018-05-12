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

void arquivoParaVetores (fstream f, string strChar, vector<int> vetInt) {
  
}

/**************** ORDENAÇÃO EXTERNA ****************/

// Apaga o vetor pra recolocar os novos caracteres
// Pra botar nos arquivos
void paraInteiro (vector<int> vet, string c) {
  vet.erase(vet.begin(), vet.end());
  int inteiro;
  for (int i = 0; i < c.length(); i++) {
    inteiro = (int) c[i];
    vet.push_back(inteiro);
  }
}


// O Sort externo
void externalSort (string name) {
  fstream foriginal, fin[3], fout[3];

  // Ler os caracteres por byte (char por char)
  // Limite: 10 bytes na memória INTERNA

  // Abre os arquivos
  foriginal.open(name);
  for (int i = 0; i < 3; i++) {
    string str = "in" + ('0'+i) + ".txt"; // Nome do arquivo de entrada
    fin[i].open(str);
    str = "out" + ('0'+i) + ".txt"; // Nome do arquivo de saída
    fout[i].open(str);
  }


  string strChar;
  vector<int> vetInt;
  int controleDeArquivo = 0;

  // Encapsular junto com a leitura do arquivo {
  int quantDeChar = 0;
  char c;
  // }

  while (!foriginal.eof()) { // Escreve no vetor e muda o indice
    if(controleDeArquivo >= 3) // Se chegou em 3 (máximo de arquivos) volta pra 0
      controleDeArquivo = 0;

    // Encapsular isso {
    while (!foriginal.eof() && quantDeChar < 10) { // Lê char a char
      do { // Lê enquanto não for um caractere válido
        foriginal.getchar(&strChar[quantDeChar]);
        c = strChar[quantDeChar];
      } while ((!foriginal.eof()) && ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')));
      quantDeChar++;
    }
    strChar[quantDeChar] = '\0';
    quantDeChar = 0;
    // }

    // Botar no arquivo certo (usar controleDeArquivo)
    // Começar botando no FINAL do arquivo atual
    fin[controleDeArquivo].seekg(0,fin[controleDeArquivo].end());
    fin[controleDeArquivo].write(strChar, strChar.length());
    controleDeArquivo++;
  }


  // Ordenação aqui

  // Na hora de ordenar:
  // char -> int
  // ordena com int
  // int -> char
  // char -> arquivo de saída

}
