//
// Created by miguelius on 25.04.2021.
//
#include "suffix_tree.hpp"
#include <chrono>
#include "iostream"
#include "fstream"
#include "string"
using namespace std;
using namespace itis;
int main(int /*argc*/, char ** /*argv*/) {
  // абсолютный путь до папки с тестовыми данными
  const string absolute_input_path =
      "/home/miguelius/CLionProjects/semester-work-suffix-tree-dan/dataset/data/has_substr";
  // абсолютнуй путь до папки, в которую хотим сохранить результаты тестов
  const string absolute_output_path =
      "/home/miguelius/CLionProjects/semester-work-suffix-tree-dan/benchmark/results/has_substr";
  // считываем тестовую строку, из которой получились все эти подстроки
  ifstream test_str_file(
      "/home/miguelius/CLionProjects/semester-work-suffix-tree-dan/dataset/data/has_substr/test-string.csv");
  string test_str;
  if (test_str_file.is_open()) {
    getline(test_str_file, test_str);
  }
  string *file_names =
      new string[12]{"100.csv",   "500.csv",    "1000.csv",   "5000.csv",   "10000.csv",  "25000.csv",
                     "50000.csv", "100000.csv", "250000.csv", "500000.csv", "750000.csv", "1000000.csv"};
  SuffixTree suffixTree;
  suffixTree.createTree(test_str);
  // алгоритм тот же, если вы хотите понять, что тут происходит, посмотрите комментарии в файле
  // count_all_substr_benchmark.cpp
  for (int i = 0; i < 12; i++) {
    string file_name = file_names[i];
    ofstream output_file(absolute_output_path + "/" + file_name, ios::app);
    for (int j = 1; j < 11; j++) {
      output_file << to_string(j) + "-й набор данных" << endl;
      string path = absolute_input_path + "/" + to_string(j) + "/" + file_name;
      ifstream input_file(path);
      if (input_file.is_open()) {
        string test_substr;
        while (getline(input_file, test_substr)) {
          for (int k = 0; k < 10; k++) {
            const auto time_point_before = chrono::high_resolution_clock::now();
            suffixTree.hasSubstring(test_substr.substr(0, test_substr.length() - 1));
            const auto time_point_after = chrono::high_resolution_clock::now();
            const auto time_diff = time_point_after - time_point_before;
            const long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();
            if (output_file.is_open()) {
              output_file << time_elapsed_ns << endl;
            }
          }
        }
      }
      input_file.close();
      output_file << endl << endl;
    }
  }
  return 0;
}