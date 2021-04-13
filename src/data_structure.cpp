#include <string>
#include "data_structure.hpp"

// файл с определениями
using namespace std;
namespace itis {

  // здесь должны быть определения методов вашей структуры

  void SuffixTree::addSuffix(int const suffix_begin_index) {
    //1 случай - строка полностью совпадает с каким-то ребром
    int suffix_compare_index = suffix_begin_index;
    Node curr_node = nodes[0];
    bool isFinished = false;
    while (suffix_compare_index < static_cast<int>(str.length()) && !isFinished) {
      int *edge = findEdge(str[suffix_compare_index], curr_node);
      if (edge == nullptr){
        int* arr = new int[2]{suffix_compare_index, static_cast<int> (str.length())};
        curr_node.edges.insert({str[suffix_compare_index], arr});
        break;
      }
      int edge_compare_index = edge[0];
      bool isMatch = true;
      for (; edge_compare_index < edge[1]; edge_compare_index++, suffix_compare_index++) {
        if (str[suffix_compare_index] != str[edge_compare_index]) {
          Node new_node{curr_node.next_node};
          curr_node.next_node = &new_node;
          int* arr = new int[2]{edge_compare_index, edge[1]};
          new_node.edges.insert({str[edge_compare_index], arr});
          edge[1] = edge_compare_index;
          arr[0] = suffix_compare_index;
          arr[1] = static_cast<int> (str.length());
          new_node.edges.insert({str[edge_compare_index], arr});
          isFinished = true;
        }
      }
    }
  }
  SuffixTree::SuffixTree(string &string) {
    Node root{nullptr};
    int *arr = new int[2]{0, static_cast<int>(string.length())};
    root.edges.insert({string[0], arr});
    nodes.push_back(root);
    str = string;
  }
  void SuffixTree::createTree(string &input_str) {
    input_str.push_back('$');
    SuffixTree suffixTree(input_str);
    for (int i = 1; i < static_cast<int>(str.length()); i++) {
      suffixTree.addSuffix(i);
    }
  }
  int *SuffixTree::findEdge(char &ch, Node const &curr_node) {
    for (auto iterator = curr_node.edges.begin(); iterator != curr_node.edges.end(); iterator++) {
      if (iterator->first == ch) {
        return iterator->second;
      }
    }
    return nullptr;
  }
}  // namespace itis