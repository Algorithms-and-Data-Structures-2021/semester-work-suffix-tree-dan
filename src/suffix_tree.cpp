#include <string>
#include <queue>
#include "suffix_tree.hpp"

// файл с определениями
using namespace std;
namespace itis {

  /*
   * Краткое описание работы метода addSuffix: идём по дереву и сверяем символы суффикса с имеющимися. Когда находим несовпадение,
   * есть два случая:
   * 1. Из узла нет ребра, нужного для продолжения(нет начального символа, сопадающего с начальным символом оставшейся
   * части суффикса). Тогда мы из данного узла пускаем ребро, помеченное оставшейся частью суффикса
   * 2. Несовпадение пришлось на ребро. Тогда нам нужно в месте несовпадения создать узел. Таким образом, мы фактически
   * делим ребро этим узлом. Чтобы соблюсти изначальное состояние, мы в данный узел направляем часть ребра до несовпадения,
   * а из него пускаем оставшуюся часть ребра. Также, мы добавляем новое исходящее ребро, помеченное оставшейся частью
   * суффикса
   *
   */

  void SuffixTree::addSuffix(int const suffix_begin_index) {
    int suffix_compare_index = suffix_begin_index;
    Node *curr_node = &root_;
    bool isFinished = false;
    // сверяем символы суффикса пока он не закончится или же пока не найдется несовпадения
    while (suffix_compare_index < static_cast<int>(str_.length()) && !isFinished) {
      // получаем индекс ребра, по которому нужно идти, сравнивая символы
      int index_of_edge = findEdge(str_[suffix_compare_index], *curr_node);
      // если такого ребра нет, добавляем оставшуюся часть суффикса в виде нового ребра. Так появляется лист
      if (index_of_edge == -1) {
        curr_node->edges.push_back({suffix_compare_index, static_cast<int>(str_.length())});
        curr_node->chars.push_back(str_[suffix_compare_index]);
        curr_node->next_nodes.push_back(nullptr);
        break;
      }
      auto &edge = curr_node->edges[index_of_edge];
      int edge_compare_index = edge[0];
      /* ребро для сравнения есть, значит пора пройтись по нему и сравнить с суффиксом. Прерываемся, если ребро/суффикс
       * закончились, или же было найдено несовпадение*/
      for (; edge_compare_index < edge[1]; edge_compare_index++, suffix_compare_index++) {
        // найдено несовпадение - нужно поделить ребро
        if (str_[suffix_compare_index] != str_[edge_compare_index]) {
          // создаем новый узел
          Node *new_node = new Node();
          // старый узел мог ссылаться на какой-то другой, значит новый тоже должен, чтобы сохранить структуру
          new_node->next_nodes.push_back(curr_node->next_nodes[index_of_edge]);
          // старый теперь ссылается на наш новый
          curr_node->next_nodes[index_of_edge] = new_node;
          // добавляем оставшуюся часть ребра в наш новый узел
          new_node->edges.push_back({edge_compare_index, edge[1]});
          new_node->chars.push_back(str_[edge_compare_index]);
          // теперь метка старого узла изменилась - ребро идет до несовпадающего символа
          edge[1] = edge_compare_index;
          // добавляем оставшуюся часть суффикса в новый узел
          new_node->edges.push_back({suffix_compare_index, static_cast<int>(str_.length())});
          new_node->chars.push_back(str_[suffix_compare_index]);
          // так узел ссылается на лист, ставим nullptr, так как в моей реализации листов в виде узлов нет
          new_node->next_nodes.push_back(nullptr);
          // говорим программе, что работа по добавлению суффикса завершена
          isFinished = true;
        }
      }
      // если ребро закончилось, нужно перейти к узлу, к которому ведёт данное ребро и повторить алгоритм
      curr_node = curr_node->next_nodes[index_of_edge];
    }
  }
  // Описание алгоритма создания дерева: добавляем к строке символ страж $, создаем корневой узел,
  // добавляем все суффиксы в порядке уменьшения их длины, начиная с самого большого
  void SuffixTree::createTree(string &input_str) {
    input_str.push_back('$');
    Node root;
    root_ = root;
    str_ = input_str;
    // на первом шаге есть одно ребро - вся строка. Добавляем его
    root_.edges.push_back({0, static_cast<int>(str_.length())});
    root_.next_nodes.push_back(nullptr);
    root_.chars.push_back(str_[0]);
    // поочередно добавляем суффиксы
    for (int i = 1; i < static_cast<int>(str_.length() - 1); i++) {
      addSuffix(i);
    }
  }
  int SuffixTree::findEdge(char &ch, Node const &curr_node) {
    // поочередно проверяем все начальные символы исходящих из узла ребер
    for (int i = 0; i < curr_node.chars.size(); i++) {
      if (ch == curr_node.chars[i]) {
        return i;
      }
    }
    return -1;
  }

  /*
   * Деструктор данной структуры. Для того, чтобы удалить все узлы, используется алгоритм обхода в ширину. Для его
   * реализации используется очередь. Алгоритм запускается с корня. T = O(n), n - длина строки
   */
  SuffixTree::~SuffixTree() {
    queue<Node *> queue;
    // добавляем корень
    queue.push(&root_);
    // пока очередь не пустая - есть узлы, которые нужно удалить
    while (!queue.empty()) {
      Node *curr_node = queue.front();
      // добавляем очередь всех детей
      for (Node *node : curr_node->next_nodes) {
        if (node != nullptr) {
          queue.push(node);
        }
      }
      // очищаем массивы с ребрами, символами и следующими узлами
      curr_node->next_nodes.clear();
      curr_node->edges.clear();
      curr_node->chars.clear();
      // поскольку у корня тип Node, а не Node*, удалить оператором delete мы его не можем
      if (curr_node != &root_) {
        delete curr_node;
      }
      // узел удален, убираем его из очереди
      queue.pop();
    }
  }
  /*
   * Алгоритм проверки наличия подстроки очень прост - идем по суффиксному дереву и сравниваем символы подстроки.
   * Нашли несовпадение - подстроки нет, подстрока закончилась - все символы совпали -> подстрока есть
   * Данный алгоритм работает, так как любая подстрока является префиксом какого-то суффикса, значит в суффиксном дереве
   * она должна быть.
   * Проверка происходит точно по тому же принципу, что и проверка суффикса при его добавлении в дерево.
   */
  bool SuffixTree::hasSubstring(const string &str) {
    Node *curr_node = &root_;
    int string_compare_index = 0;
    while (string_compare_index < static_cast<int>(str.length())) {
      int edge_number = findEdge(const_cast<char &>(str[string_compare_index]), *curr_node);
      if (edge_number == -1) {
        return false;
      }
      for (int i = curr_node->edges[edge_number][0]; i < curr_node->edges[edge_number][1]; i++) {
        if (str_[i] != str[string_compare_index]) {
          return false;
        }
        string_compare_index++;
        if (string_compare_index == static_cast<int>(str.length())) {
          break;
        }
      }
      curr_node = curr_node->next_nodes[edge_number];
    }
    return true;
  }
  /*
   * Каждая подстрока является префиксом какого-то суффикса строки, либо им самим. Исходя из нашего построения суффиксного
   * дерева следует, что каждой позиции ребра соответствует префикс суффикса. Поскольку в нашем дереве есть все суффиксы,
   * это означает, что есть и все префиксы всех суффиксов. Чтобы посчитать все префиксы суффикса, нужно посчитать длины
   * всех ребер на пути, который мы пройдем по дереву, чтобы получить суффикс. Таким образом, задача сводится к тому,
   * чтобы просуммировать длины всех ребёр.
   * Поскольку у ребер, ведущих к листьям, в пометке присутствует символ страж $, длину таких ребер мы будем
   * брать на 1 меньше
   */
  int SuffixTree::getCountOfAllSubstr() {
    queue<Node *> nodes;
    nodes.push(&root_);
    int count = 0;
    while (!nodes.empty()) {
      Node *curr_node = nodes.front();
      for (int i = 0; i < curr_node->edges.size(); i++) {
        count += curr_node->edges[i][1] - curr_node->edges[i][0];
        if (curr_node->next_nodes[i] == nullptr) {
          count--;
        } else {
          nodes.push(curr_node->next_nodes[i]);
        }
      }
      nodes.pop();
    }
    return count;
  }
  SuffixTree::SuffixTree() = default;
}