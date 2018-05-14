#include "ordenacao.hpp"


// Problemas:
// - Limpar arquivos quando for usa-los como SAÍDA (resolvido logo abaixo, só falta implementar)
// - COMO ENVIAR VETOR DE ARQUIVO COMO PARÂMETRO?


// Quando for usar fin de entrada, fechar fout e abrir assim:
// fs.open("test.txt", std::fstream::out | std::fstream::trunc);
// Quando for usar fout de entrada, fechar fin e abrir da mesma maneira


void paraInteiro (vector<int>& vet, string c);
void paraChar (vector<int> vet, string& c);
int verifica_menor(fstream f[3], char a, char b, char c);
bool charValido(char c);

void resultado(fstream& arq, fstream& ffinal);
bool isEmpty(fstream& f);
void clearFile(fstream& f);


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


// Limpa um arquivo (talvez precise do nome do arquivo)
// Para limpar, pode colocar caracteres que não estejam entre 'a' e 'z'
// Mudar todo o tipo de verificação pra ver se está vazio usando charValido (char c)
void clearFile(fstream& f) {

}


bool isEmpty(fstream& f) {
  // Vai para a posição inicial
  f.seekg(0, f.beg);

  char c;
  while (f.get(c)) {
    if (charValido(c))
      return false;
  }

  // Volta pra posição inicial
  f.seekg(0, f.beg);
  return true;
}


void resultado(fstream& arq, fstream& ffinal) {
  char c;
  int cont = 0;
  for (cont = 0; arq.get(c); cont++) {
    if(charValido(c))
      ffinal << c;
    if (cont == 30)
      ffinal << '\n';
  }
}


/**************** ORDENAÇÃO EXTERNA ****************/

// Apaga o vetor pra recolocar os novos caracteres
// Pra botar nos arquivos
void paraInteiro (vector<int>& vet, string c) {
  vet.erase(vet.begin(), vet.end());
  int inteiro;
  for (int i = 0; i < c.length(); i++) {
    inteiro = (int) c[i];
    vet.push_back(inteiro);
  }
}


void paraChar (vector<int> vet, string& c) {
  c.clear();
  for (int i = 0; i < vet.size(); i++) {
    c += (char) vet[i];
  }
}


bool charValido(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

//
//
//
//
//
//
// REVISAR ESSA FUNCAO
int verifica_menor(fstream f[3], char a, char b, char c) {
  if (a <= b && a <= c){
    if (charValido(a)) {
      return 0;
    }
    f[0].ignore();
  }
  if (b <= a && b <= c && charValido(b)) {
    if (charValido(b)) {
      return 1;
    }
    f[1].ignore();
  }
  if (c <= a && c <= b && charValido(c)) {
    if (charValido(c)) {
      return 2;
    }
    f[2].ignore();
  }
  // Se C for o menor, mas não for válido:
  if (a <= b) {
    if (charValido(a)) {
      return 0;
    }
    f[0].ignore();
  }
  if (b <= a){ // Se A for o menor e não for válido
    if (charValido(b)) {
      return 1;
    }
    f[1].ignore();
  } else { // Vai o B mesmo
    return 0;
  }
}
// REVISAR ESSA FUNCAO
//
//
//
//
//
//


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
  fstream ffinal;
  ffinal.open("final.txt");
  int cont=0, max=30;

  for (int i = 0; i < 3; i++) {
    fin[i].seekg(0, fin[i].beg);
    fout[i].seekg(0, fout[i].beg);
  }

  while (!(isEmpty(fin[1]) && isEmpty(fin[2]))) {

    // Limpa o fout (dica de como fazer isso no inicio desse arquivo)

    while(!(fin[0].eof() && fin[1].eof() && fin[2].eof())) {
      char c;
      // Como envia um vetor de arquivos?
      int k = verifica_menor(fin, fin[0].peek(), fin[1].peek(), fin[2].peek());
      fin[k].get(c);
      if (cont  < max){
        fout[0].seekg(0, fout[0].end);
        fout[0] << c;
      }else if (cont < max*2){
        fout[1].seekg(0, fout[1].end);
        fout[1] << c;
      }else{
        fout[2].seekg(0, fout[2].end);
        fout[2] << c;
      }
      cont++;
    }
    for (int i = 0; i < 3; i++){
      fin[i].flush();
      fout[i].flush();
    }

    if (isEmpty(fout[1]) && isEmpty(fout[2])){
      resultado(fout[0], ffinal);
      return;
    }

    cont = 0;
    max *= 3;

    // Limpa o fin (dica de como fazer isso no inicio desse arquivo)

    while(!(fout[0].eof() && fout[1].eof() && fout[2].eof())){
      char c;
      // Como envia um vetor de arquivos?
      int k = verifica_menor(fout, fout[0].peek(), fout[1].peek(), fout[2].peek());
      fout[k].get(&c,1);
      if (cont  < max){
        fin[0].seekg(0, fin[0].end);
        fin[0] << c;
      }else if (cont < max*2){
        fin[1].seekg(0, fin[1].end);
        fin[1] << c;
      }else{
        fin[2].seekg(0, fin[2].end);
        fin[2] << c;
      }
      cont++;
    }
    for (int i = 0; i < 3; i++){
      fin[i].flush();
      fout[i].flush();
    }
    cont =  0;
    max *= 3;
  }

  resultado(fin[0], ffinal);

  // Fechando os arquivos
  for (int i = 0; i < 3; i++) {
    fin[i].close();
    fout[i].close();
  }
  ffinal.close();

  return;
}
