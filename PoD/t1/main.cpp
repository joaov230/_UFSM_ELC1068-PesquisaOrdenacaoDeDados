#include "ordenacao.hpp"

int main (void) {
  // externalSort("teste.txt");
  fstream f;
  f.open("out0.txt");
  char c;
  if (!f.eof()) {
    // c = f.peek();
    f.get(c);
    cout << "\n\n" << c << "\n\n";
  }

}
