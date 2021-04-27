#include <iostream>
#include "suffix_tree.hpp"

using namespace std;
using namespace itis;

int main(int argc, char *argv[]) {
  for (int index = 0; index < argc; index++) {
    cout << index << ": " << argv[index] << endl;
  }
  SuffixTree suffixTree;
  string str = "aba";
  suffixTree.createTree(str);
  cout << suffixTree.getCountOfAllSubstr();
  return 0;
}