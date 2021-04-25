#include <string>
#include <queue>
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
    queue<Node *> queue;
    queue.push(&root_);
    while (!queue.empty()) {
      Node *curr_node = queue.front();
      for (Node *node : curr_node->next_nodes) {
        if (node != nullptr) {
          queue.push(node);
        }
      }
      curr_node->next_nodes.clear();
      curr_node->edges.clear();
      curr_node->chars.clear();
      if (curr_node != &root_) {
        delete curr_node;
      }
      queue.pop();
    }
  }
  int SuffixTree::hasSubstring(const string &str, bool needLast) {
    Node *curr_node = &root_;
    Node *previous_node = &root_;
    int string_compare_index = 0;
    int edge_number;
    while (string_compare_index < static_cast<int>(str.length())) {
      edge_number = findEdge(const_cast<char &>(str[string_compare_index]), *curr_node);
      if (edge_number == -1) {
        return 0;
      }
      for (int i = curr_node->edges[edge_number][0]; i < curr_node->edges[edge_number][1]; i++) {
        if (str_[i] != str[string_compare_index]) {
          return 0;
        }
        string_compare_index++;
        if (string_compare_index == static_cast<int>(str.length())) {
          break;
        }
      }
      previous_node = curr_node;
      curr_node = curr_node->next_nodes[edge_number];
    }
    if (needLast) {
      int last_entry;
      if (curr_node) {
        last_entry = curr_node->edges[0][1];
        for (int i = 1; i < curr_node->edges.size(); i++) {
          last_entry = max(last_entry, curr_node->edges[i][1]);
        }
      } else {
        last_entry = previous_node->edges[edge_number][1];
      }
      return last_entry - str.length() - 1;
    }
    return 1;
  }
  bool SuffixTree::hasSubstring(const string &str) {
    return hasSubstring(str, false) != 0;
  }
  int SuffixTree::findLastEntry(const string &substr) {
    return hasSubstring(substr, true);
  }
  SuffixTree::SuffixTree() = default;
}  // namespace itis