#include "ordenacao.hpp"

int main (void) {
  externalSort("teste.txt");

  fstream file;
  file.open("test.txt");
  file << "Hi, my name is Jon";
  file.close();

}
