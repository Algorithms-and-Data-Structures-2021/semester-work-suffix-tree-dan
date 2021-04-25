#pragma once

// Заголовочный файл с объявлением структуры данных

#include <vector>
#include <string>
namespace itis {

  // Tip 1: объявите здесь необходимые структуры, функции, константы и прочее

  // Пример: объявление константы времени компиляции в заголовочном файле
  inline constexpr auto kStringConstant = "Hello, stranger!";

  // Пример: объявление структуры с полями и методами
  struct Node {
   public:
    std::vector<Node*> next_nodes;
    std::vector<char> chars;
    std::vector<std::vector<int>> edges;
    // Tip 2: На начальном этапе разработки структуры данных можете определения методов задавать в
    // заголовочном файле, как только работа будет завершена, можно будет оставить здесь только объявления.
  };

  struct SuffixTree {
    SuffixTree();
    virtual ~SuffixTree();
    bool hasSubstring(std::string const &);
    int findLastEntry(std::string const &);
   private:
    int hasSubstring(std::string const &, bool needLast);
    Node root_;
    void addSuffix(int const);
    std::string str_;
    int findEdge(char &, Node const&);
   public:
    void createTree(std::string &);
  };
}  // namespace itis