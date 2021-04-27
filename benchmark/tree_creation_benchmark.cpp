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

  // абсолютный путь до файла с настройками
  ifstream setting_file("/home/miguelius/CLionProjects/semester-work-suffix-tree-dan/benchmark/tree-creation-settings.txt");
  vector<string> settings;
  if (setting_file.is_open()) {
    string line;
    while (getline(setting_file, line)) {
      settings.push_back(line.substr(line.find('=') + 1, line.length()));
    }
  }

  const string absolute_input_path = settings[0];
  const string absolute_output_path = settings[1];
  // парсим названия файлов из документа с настройками
  vector<string> file_names;
  settings[2].erase(0, settings[2].find("=") + 1);
  int start = 0;
  string delim = ",";
  auto end = settings[2].find(delim);
  while (end != std::string::npos)
  {
    file_names.push_back(settings[2].substr(start, end - start));
    start = end + delim.length();
    end = settings[2].find(delim, start);
  }
  file_names.push_back(settings[2].substr(start, end - start));

  int count_of_test_repeat = stoi(settings[3]);
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
          for(int k = 0; k < count_of_test_repeat; k++){
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

