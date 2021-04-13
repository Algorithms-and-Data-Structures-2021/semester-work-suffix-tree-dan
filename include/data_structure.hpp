#pragma once

// Заголовочный файл с объявлением структуры данных

#include <unordered_map>
#include <vector>
namespace itis {

  // Tip 1: объявите здесь необходимые структуры, функции, константы и прочее

  // Пример: объявление константы времени компиляции в заголовочном файле
  inline constexpr auto kStringConstant = "Hello, stranger!";

  // Пример: объявление структуры с полями и методами
  struct Node {
   public:
    Node* next_node;
    std::unordered_map<char, int*> edges;
    // Tip 2: На начальном этапе разработки структуры данных можете определения методов задавать в
    // заголовочном файле, как только работа будет завершена, можно будет оставить здесь только объявления.
  };

  struct SuffixTree {
    SuffixTree(std::string &);

   private:
    std::vector<Node> nodes;
    void addSuffix(int const);
    std::string str;
    int* findEdge(char &, Node const&);
   public:
    void createTree(std::string &);
  };
}  // namespace itis