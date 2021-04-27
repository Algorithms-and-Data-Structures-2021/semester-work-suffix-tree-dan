#pragma once

// Заголовочный файл с объявлением структуры данных

#include <vector>
#include <string>
namespace itis {


  /*
   * Структура Node - узел суффиксного дерева
   *
   * next_nodes - массив узлов, исходящих из данного. Если узел ведёт к листу, то в массиве будет nullptr
   * chars - начальные символы ребер, исходящих из данного узла
   * edges - массив индексов всех ребер, исходящих их данного узла.
   *         Два индекса ребра указывают на индексы подстроки, которым оно помечено.
   *
   * Поскольку для каждого ребра информацией является и пометка, и следующий узел, и начальный символ,
   * в этих массивах под одинаковыми индексами хранится информация об одном и том же ребре.
   *
   * В моей реализации листья не представлены узлами, поэтому для того, чтобы индексация была правильной,
   * при добавлении ребра, ведущего к листу, следующим узлом под индексом данного ребра в массиве next_nodes
   * является nullptr.
   *
   */
  struct Node {
   public:
    std::vector<Node*> next_nodes;
    std::vector<char> chars;
    std::vector<std::vector<int>> edges;
  };

  /*
   * Стуктура SuffixTree - само суффиксное дерево
   * public:
   * - bool hasSubstring(std::string const &) - метод, отвечающий за проверку наличия подстроки в строке,
   *   по которому было построено данное суффиксное дерево. На вход подаётся подстрока, ответ даётся в виде bool:
   *   0 - не содержит, 1 - содержит
   *   Данная операция занимает T = O(m), где m - длина подстроки. Это с учетом того, что суффиксное дерево уже построено
   *
   * - void createTree(std::string &) - построение суффиксного дерева. Принимает на вход строку, по которой будет
   *   строиться дерево. Построение занимает T = O(n^2) и M = O(n), где n - длина строки
   *
   * - int getCountOfAllSubstr() - подсчет количества всех различных подстрок строки, по которой было построено
   *   суффиксное дерево. Возвращает число - искомое количество. Занимает T = O(n), где n - для строки, по которой
   *   было построено дерево.
   *
   * private:
   *  Methods:
   *    - void addSuffix(int const) - добавляет к текущему суффиксному дереву ещё один суффикс. Занимает T = O(m),
   *      где m - длина суффикса. Метод принимает индекс начала суффикса в исходной строке
   *    - int findEdge(char &, Node const&) - метод проверяет, исходит ли из данного узла ребро, начинающееся на
   *      заданный символ. Метод принимает на вход символ и узел, для которого нужно совершить проверку. Возвращает
   *      индекс искомого ребра во внутренних массивах данного узла(структуры Node, посмотрите её описание). Если такого
   *      ребра нет, возвращает -1. Занимает T = O(1)
   *  Fields:
   *    - Node root_ - корневой узел дерева
   *    - std::string str_ - строка, для которой строится/было построено суффиксное дерево
   *
   *  Подробное описание того, как работают основные методы, написано в файле с реализацией suffix_tree.cpp
   */

  struct SuffixTree {
   private:
    Node root_;
    void addSuffix(int const);
    std::string str_;
    int findEdge(char &, Node const&);
   public:
    SuffixTree();
    virtual ~SuffixTree();
    bool hasSubstring(std::string const &);
    int getCountOfAllSubstr();
    void createTree(std::string &);
  };
}  // namespace itis