#include "ordenacao.hpp"


/**************** ORDENAÇÃO INTERNA ****************/

// Segundo vet aux (de meio+1 até fim)
// Segundo vet aux (de meio+1 até fim)
// Da merge dos dois sub vet no vet novamente

void merge (vector<int> vet, int init, int meio, int fim) {
  int pt1 = 1 + meio - init;
  int pt2 = fim - meio;

  vector<int> aux1, aux2;

  for (int i = 0; i < pt1; i++) {
    aux1.push_back(vet[init + i]);
  }
  for (int j = 0; j < pt2; j++) {
    aux2.push_back(vet[j + meio + 1]);
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
void mergeSort(vector<int> vet, int init, int fim) {
  if (init < fim) {
    // Começa do init e vai pra metade do mesmo
    int meio = init+(fim-init)/2;

    mergeSort(vet, init, meio);
    mergeSort(vet, meio+1, fim);

    merge(vet, init, meio, fim);
  }
}


/**************** MANIPULAÇÃO DE ARQUIVOS ****************/

/** ISSO NÃO TÁ DANDO CERTO **/

// Lê de um arquivo e bota pra uma string
// Transforma a string pra vetor de inteiros (baseado na tabela ascii)
// void arquivoParaVetores (fstream f, string strChar, vector<int> vetInt) {
//   int quantDeChar = 0;
//   char c;
//
//   while (!f.eof() && quantDeChar < 10) { // Lê char by char
//     do { // Continua lendo com o mesmo índice enquanto não for um caractere válido
//       f.get(strChar[quantDeChar]);
//       c = strChar[quantDeChar];
//     } while ((!f.eof()) && ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')));
//     quantDeChar++; // Vai para o prox caractere
//   }
//   strChar[quantDeChar] = '\0';
//
//   // Se o programa precisar, já passa para inteiro tambem
//   paraInteiro(vetInt, strChar);
// }

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

void paraChar (vector<int> vet, string c) {
  for (int i = 0; i < vet.size(); i++) {
    c[i] = (char) vet[i];
  }
}


// O Sort externo
void externalSort (string name) {
  fstream foriginal, fin[3], fout[3];

  // Ler os caracteres por byte (char por char)
  // Limite: 10 bytes na memória INTERNA

  // Abre os arquivos
  foriginal.open(name);
  fin[0].open("in0.txt");
  fin[1].open("in1.txt");
  fin[2].open("in2.txt");
  fout[0].open("in0.txt");
  fout[1].open("in1.txt");
  fout[2].open("in2.txt");


  // String de char (usada para coletar os char do arquivo)
  string strChar;
  // Vet de inteiros baseado na tabela ascii (usado para fazer a ordenação)
  vector<int> vetInt;
  int controleDeArquivo = 0;

  int quantDeChar = 0;
  char c;

  while (!foriginal.eof()) { // Escreve no vetor e muda o indice
    strChar.clear();
    if(controleDeArquivo >= 3) // Se chegou em 3 (máximo de arquivos) volta pra 0
      controleDeArquivo = 0;

    while ((foriginal.get(c)) && quantDeChar++ < 10) { // Lê char a char
      if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        strChar += c;
      }
    }

    std::cout << "\n - ANTES DE ORDENAR: " << strChar << endl;

    paraInteiro(vetInt, strChar); // Transforma pra inteiro pra ordenar
    mergeSort(vetInt, 0, vetInt.size()); // Ordena
    paraChar(vetInt, strChar); // Bota o ordenado pra char pra escrever no arquivo de entrada
    quantDeChar = 0;

    std::cout << "\n - DEPOIS DE ORDENAR: " << strChar << endl;

    // Botar no arquivo certo (usar controleDeArquivo)
    // Busca o final do arquivo
    fin[controleDeArquivo].seekg(0,fin[controleDeArquivo].end);

    // Começar botando no FINAL do arquivo atual
    // Escreve no arquivo
    fin[controleDeArquivo] << strChar;

    // Vai para o próximo arquivo
    controleDeArquivo++;
  }

  // Ordenação aqui



}
