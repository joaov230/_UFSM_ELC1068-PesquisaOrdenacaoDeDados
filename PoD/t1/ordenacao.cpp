#include "ordenacao.hpp"


void paraInteiro (vector<int>& vet, string c);
void paraChar (vector<int> vet, string& c);
int verifica_menor(int vet[], int tamMax, ifstream& f1, ifstream& f2, ifstream& f3);
bool charValido(char c);

void resultado(void);
bool isEmpty(void);
void copiaProArquivo(void);


/**************** ORDENAÇÃO INTERNA ****************/

// Segundo vet aux (de meio+1 até fim)
// Segundo vet aux (de meio+1 até fim)
// Da merge dos dois sub vet no vet novamente

void merge (vector<int>& vet, int init, int meio, int fim) {
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
void mergeSort(vector<int>& vet, int init, int fim) {
  if (init < fim) {
    // Começa do init e vai pra metade do mesmo
    int meio = init+(fim-init)/2;

    mergeSort(vet, init, meio);
    mergeSort(vet, meio+1, fim);

    merge(vet, init, meio, fim);
  }
}

/**************** MANIPULAÇÃO DE ARQUIVOS ****************/


bool isEmpty(void) {

  fstream f1,f2;
  f1.open("out1.txt");
  f2.open("out2.txt");

  f1.seekg(0, f1.end);
  int tam1 = f1.tellg();
  f1.close();

  f2.seekg(0, f2.end);
  int tam2 = f2.tellg();
  f2.close();

  if (tam1 == 0 && tam2 == 0) {
    return true;
  } else {
    return false;
  }
}


void resultado(void) {
  char c;

  ifstream arq;
  arq.open("in0.txt");
  ofstream ffinal;
  ffinal.open("final.txt");

  cout << "\n\n\n\n\n C O P I O U    P R O     F I N A L \n\n\n\n\n";

  while(arq.get(c)) {
    cout << "\n" << " C = " << c << "\n";
    ffinal << c;
  }
}


void copiaProArquivo(void) {
  ifstream fout[3];
  ofstream fin[3];
  char c;

  fout[0].open("out0.txt");
  fout[1].open("out1.txt");
  fout[2].open("out2.txt");
  fin[0].open("in0.txt");
  fin[1].open("in1.txt");
  fin[2].open("in2.txt");

  // Primeiro arquivo
  while (fout[0].get(c)) {
    fin[0] << c;
  }
  // Segundo arquivo
  while (fout[1].get(c)) {
    fin[1] << c;
  }
  // Terceiro arquivo
  while (fout[2].get(c)) {
    fin[2] << c;
  }

  // Fecha os arquivos
  for (int i = 0; i < 3; i++) {
    fin[i].close();
    fout[i].close();
  }
}



/**************** ORDENAÇÃO EXTERNA ****************/

// Apaga o vetor pra recolocar os novos caracteres
// Pra botar nos arquivos
void paraInteiro (vector<int>& vet, string c) {
  vet.erase(vet.begin(), vet.end());
  int inteiro;
  for (unsigned int i = 0; i < c.length(); i++) {
    inteiro = (int) c[i];
    vet.push_back(inteiro);
  }
}


void paraChar (vector<int> vet, string& c) {
  c.clear();
  for (unsigned int i = 0; i < vet.size(); i++) {
    c += (char) vet[i];
  }
}


bool charValido(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}


// Verifica qual é o menor char entre os 3 arquivos
// Verifica se o caractere é válido
// Caso não for, ignora esse caractere
int verifica_menor(int vet[], int tamMax, ifstream& f1, ifstream& f2, ifstream& f3) {
  char a = f1.peek();
  if (!charValido(a)) {
    a = CHAR_MAX; // Definido no <climits>
  }
  if (vet[0] >= tamMax) {
    a = CHAR_MAX; // Definido no <climits>
  }

  char b = f2.peek();
  if (!charValido(b)) {
    b = CHAR_MAX; // Definido no <climits>
  }
  if (vet[1] >= tamMax) {
    b = CHAR_MAX; // Definido no <climits>
  }

  char c = f3.peek();
  if (!charValido(c)) {
    c = CHAR_MAX; // Definido no <climits>
  }
  if (vet[2] >= tamMax) {
    c = CHAR_MAX; // Definido no <climits>
  }

  if (a <= b && a <= c) {
    vet[0] += 1;
    return 0;
  }
  if (b <= a && b <= c) {
    vet[1] += 1;
    return 1;
  }
  if (c <= a && c <= b) {
    vet[2] += 1;
    return 2;
  }
  return 0;
}


// O Sort externo
void externalSort (string name) {
  fstream foriginal, fin[3];

  // Ler os caracteres por byte (char por char)
  // Limite: 10 bytes na memória INTERNA

  // Abre os arquivos
  foriginal.open(name);
  fin[0].open("in0.txt");
  fin[1].open("in1.txt");
  fin[2].open("in2.txt");

  // String de char (usada para coletar os char do arquivo)
  // Vet de inteiros baseado na tabela ascii (usado para fazer a ordenação)
  vector<int> vetInt;
  int controleDeArquivo = 0;

  int quantDeChar;
  char c;

  while (!foriginal.eof()) { // Escreve no vetor e muda o indice
    string strChar;
    quantDeChar = 0;
    if(controleDeArquivo >= 3) // Se chegou em 3 (máximo de arquivos) volta pra 0
      controleDeArquivo = 0;

    while (quantDeChar < 10) { // Lê char a char
      foriginal.get(c);
      if (charValido(c)) {
        strChar += c;
      }
      quantDeChar++;
    }


    paraInteiro(vetInt, strChar); // Transforma pra inteiro pra ordenar
    mergeSort(vetInt, 0, vetInt.size()-1); // Ordena
    paraChar(vetInt, strChar); // Bota o ordenado pra char pra escrever no arquivo de entrada

    // Botar no arquivo certo (usar controleDeArquivo)
    // Busca o final do arquivo
    fin[controleDeArquivo].seekg(0,fin[controleDeArquivo].end);

    // Começar botando no FINAL do arquivo atual
    // Escreve no arquivo
    fin[controleDeArquivo] << strChar;

    // Vai para o próximo arquivo
    controleDeArquivo++;
  }

  foriginal.close();


  // Ordenação aqui
  int cont=0, max=30;

  for (int i = 0; i < 3; i++) {
    fin[i].close();
  }

  ifstream fentrada[3];
  ofstream fout[3];

  int vet[3] = {0,0,0};
  int tamMax = 10;

  // Ordenação
  do {
    fentrada[0].open("in0.txt");
    fentrada[1].open("in1.txt");
    fentrada[2].open("in2.txt");

    remove("out0.txt");
    remove("out1.txt");
    remove("out2.txt");
    fout[0].open("out0.txt");
    fout[1].open("out1.txt");
    fout[2].open("out2.txt");

    // Quanto fin é a entrada e fout é a saída
    while(!(fentrada[0].eof() && fentrada[1].eof() && fentrada[2].eof())) {
      int k = verifica_menor(vet, tamMax, fentrada[0], fentrada[1], fentrada[2]);
      fentrada[k].get(c);

      if (cont < max){
        fout[0] << c;
      } else if (cont < max*2){
        fout[1] << c;
      } else if (cont < max*3){
        fout[2] << c;
      } else {
        fout[0] << c;
        cont = 0;
      }
      cont++;
      if (vet[0] >= tamMax && vet[1] >= tamMax && vet[2] >= tamMax) {
        for (int i = 0; i < 3; i++) {
          vet[i] = 0;
        }
      }
    }

    for (int i = 0; i < 3; i++) {
      vet[i] = 0;
    }

    cont = 0;
    tamMax = max;
    max *= 10;

    for (int i = 0; i < 3; i++) {
      fentrada[i].seekg(0, fentrada[i].beg);
      fentrada[i].close();
    }

    for (int i = 0; i < 3; i++){
      fout[i].close();
    }

    copiaProArquivo();

  } while (!(isEmpty()));

  resultado();

  // Fechando os arquivos
  for (int i = 0; i < 3; i++) {
    fentrada[i].close();
    fout[i].close();
  }

  return;
}
