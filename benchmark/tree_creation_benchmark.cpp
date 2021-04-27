//
// Created by miguelius on 24.04.2021.
//
#include "suffix_tree.hpp"
#include <chrono>
#include "iostream"
#include "fstream"
#include "string"
using namespace std;
using namespace itis;
int main(int /*argc*/, char ** /*argv*/) {
  // все то же самое, что и в других тестах. За информацией идите в count_all_substr_benchmark.cpp
  const string absolute_input_path = "/home/miguelius/CLionProjects/semester-work-suffix-tree-dan/dataset/data/tree_creation";
  const string absolute_output_path = "/home/miguelius/CLionProjects/semester-work-suffix-tree-dan/benchmark/results/tree_creation";
  string *file_names = new string[12]{"100.csv",   "500.csv",    "1000.csv",   "5000.csv",   "10000.csv",  "25000.csv",
                                    "50000.csv", "100000.csv", "250000.csv", "500000.csv", "750000.csv", "1000000.csv"};
  for(int i = 0; i < 12; i++){
    string file_name = file_names[i];
    ofstream output_file(absolute_output_path + "/" + file_name, ios::app);
    for (int j = 1; j < 11; j++){
      output_file << to_string(j) + "-й набор данных" << endl;
      string path = absolute_input_path + "/" + to_string(j) + "/" + file_name;
      ifstream input_file(path);
      if (input_file.is_open()){
        string test_str;
        while (getline(input_file, test_str)){
          for(int k = 0; k < 10; k++){
            SuffixTree suffixTree;
            const auto time_point_before = chrono::high_resolution_clock::now();
            suffixTree.createTree(test_str);
            const auto time_point_after = chrono::high_resolution_clock::now();
            const auto time_diff = time_point_after - time_point_before;
            const long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();
            if (output_file.is_open()){
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

