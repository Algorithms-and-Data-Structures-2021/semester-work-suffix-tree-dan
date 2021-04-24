#include <string>
#include "suffix_tree.hpp"

// файл с определениями
using namespace std;
namespace itis {

  // здесь должны быть определения методов вашей структуры

  void SuffixTree::addSuffix(int const suffix_begin_index) {
    int suffix_compare_index = suffix_begin_index;
    Node *curr_node = &root_;
    bool isFinished = false;
    while (suffix_compare_index < static_cast<int>(str_.length()) && !isFinished) {
      int index_of_edge = findEdge(str_[suffix_compare_index], *curr_node);
      if (index_of_edge == -1) {
        curr_node->edges.push_back({suffix_compare_index, static_cast<int>(str_.length())});
        curr_node->chars.push_back(str_[suffix_compare_index]);
        curr_node->next_nodes.push_back(nullptr);
        break;
      }
      auto &edge = curr_node->edges[index_of_edge];
      int edge_compare_index = edge[0];
      for (; edge_compare_index < edge[1]; edge_compare_index++, suffix_compare_index++) {
        if (str_[suffix_compare_index] != str_[edge_compare_index]) {
          Node *new_node = new Node();
          nodes_.push_back(new_node);
          new_node->next_nodes.push_back(curr_node->next_nodes[index_of_edge]);
          curr_node->next_nodes[index_of_edge] = new_node;
          new_node->edges.push_back({edge_compare_index, edge[1]});
          new_node->chars.push_back(str_[edge_compare_index]);
          edge[1] = edge_compare_index;
          new_node->edges.push_back({suffix_compare_index, static_cast<int>(str_.length())});
          new_node->chars.push_back(str_[suffix_compare_index]);
          new_node->next_nodes.push_back(nullptr);
          isFinished = true;
        }
      }
      curr_node = curr_node->next_nodes[index_of_edge];
    }
  }
  void SuffixTree::createTree(string &input_str) {
    input_str.push_back('$');
    Node root;
    root_ = root;
    nodes_.push_back(&root_);
    str_ = input_str;
    root_.edges.push_back({0, static_cast<int>(str_.length())});
    root_.next_nodes.push_back(nullptr);
    root_.chars.push_back(str_[0]);
    for (int i = 1; i < static_cast<int>(str_.length() - 1); i++) {
      addSuffix(i);
    }
  }
  int SuffixTree::findEdge(char &ch, Node const &curr_node) {
    for (int i = 0; i < curr_node.chars.size(); i++) {
      if (ch == curr_node.chars[i]) {
        return i;
      }
    }
    return -1;
  }
  SuffixTree::~SuffixTree() {
    for (int i = 1; i < static_cast<int>(nodes_.size()); i++) {
      Node* node = nodes_[i];
      node->next_nodes.clear();
      node->chars.clear();
      node->edges.clear();
      delete node;
    }
    nodes_.clear();
  }
  SuffixTree::SuffixTree() = default;
}  // namespace itis