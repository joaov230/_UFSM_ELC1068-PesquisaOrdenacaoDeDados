#include "ordenacao.hpp"



/**************** ORDENAÇÃO INTERNA ****************/


// Usar merge para ordenação interna


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
