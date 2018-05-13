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


// O Sort externo
void externalSort (string name) {
  fstream foriginal, fin[3], fout[3];

  // Ler os caracteres por byte (char por char)
  // Limite: 10 bytes na memória INTERNA

  // Abre os arquivos
  foriginal.open(name);
  for (int i = 0; i < 3; i++) {

    string str;
    str = "in" + ('0'+i); // Nome do arquivo de entrada
    str+=".txt";
    fin[i].open(str);

    str = "out" + ('0'+i); // Nome do arquivo de saída
    str+=".txt";
    fout[i].open(str);
  }

  // String de char (usada para coletar os char do arquivo)
  string strChar;
  // Vet de inteiros baseado na tabela ascii (usado para fazer a ordenação)
  vector<int> vetInt;
  int controleDeArquivo = 0;

  // Encapsular isso {
  int quantDeChar = 0;
  char c;
  // }

  while (!foriginal.eof()) { // Escreve no vetor e muda o indice
    if(controleDeArquivo >= 3) // Se chegou em 3 (máximo de arquivos) volta pra 0
      controleDeArquivo = 0;

    // Encapsular junto na mesma função
    while (!foriginal.eof() && quantDeChar < 10) { // Lê char a char
      do { // Lê enquanto não for um caractere válido
        foriginal.get(strChar[quantDeChar]);
        c = strChar[quantDeChar];
      } while ((!foriginal.eof()) && ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z')));
      quantDeChar++;
    }
    strChar[quantDeChar] = '\0';
    quantDeChar = 0;
    // }

    // Botar no arquivo certo (usar controleDeArquivo)
    fin[controleDeArquivo].seekg(0,fin[controleDeArquivo].end);

    // Começar botando no FINAL do arquivo atual
    fin[controleDeArquivo] << strChar;
    // fin[controleDeArquivo].write(strChar, strChar.length());

    // Vai para o próximo arquivo
    controleDeArquivo++;
  }


  // Ordenação aqui

  // Na hora de ordenar:
  // char -> int
	for (int i = 0; i < strChar.length(); i++){
		int x = INT strChar[i];
		vetInt.push_back(x);
	}
  
  // ordena com int
  mergeSort(vetInt, 0, vetInt.length() - 1);
  
  // int -> char
  string saida;
	for (int i = 0; i < vetInt.length(); i++){
		char c = CHAR vetInt[i] ;
		saida.push_back(c);
	}
  
  // char -> arquivo de saída

}
