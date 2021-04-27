//
// Created by miguelius on 27.04.2021.
//
#include "iostream"
#include "suffix_tree.hpp"
using namespace itis;
using namespace std;
int main(){
  SuffixTree suffixTree;
  string example_str = "abacaba";
  suffixTree.createTree(example_str);
  cout << suffixTree.hasSubstring("aba") << endl;
  cout << suffixTree.getCountOfAllSubstr() << endl;
}