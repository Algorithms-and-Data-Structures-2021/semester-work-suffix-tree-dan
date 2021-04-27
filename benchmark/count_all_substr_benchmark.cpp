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
  // абсолютный путь до файла с настройками
  ifstream setting_file("/home/miguelius/CLionProjects/semester-work-suffix-tree-dan/benchmark/count-all-substr-settings.txt");
  vector<string> settings;
  if (setting_file.is_open()) {
    string line;
    while (getline(setting_file, line)) {
      settings.push_back(line.substr(line.find('=') + 1, line.length()));
    }
  }
  // абсолютный путь до папки с тестовыми данными
  const string absolute_input_path = settings[0];
  // абсолютнуй путь до папки, в которую хотим сохранить результаты тестов
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
  // проходимся по всем файлам поочередно
  for(int i = 0; i < 12; i++){
    string file_name = file_names[i];
    // будем писать результаты в файл, с тем же названием, что и тестовый набор данных
    ofstream output_file(absolute_output_path + "/" + file_name, ios::app);
    // проходимся по всем директориям, дабы записать в один файл результаты по всем наборам
    for (int j = 1; j < 11; j++){
      output_file << to_string(j) + "-й набор данных" << endl;
      string path = absolute_input_path + "/" + to_string(j) + "/" + file_name;
      // получаем тестовые данные
      ifstream input_file(path);
      if (input_file.is_open()){
        string test_str;
        // для строки создаем дерево, замеряем время создания, записываем результат в файл
        while (getline(input_file, test_str)){
          SuffixTree suffixTree;
          suffixTree.createTree(test_str);
          // чтобы быть более точными, для одного набора проводим тест count_of_test_repeat раз
          for(int k = 0; k < count_of_test_repeat; k++){
            const auto time_point_before = chrono::high_resolution_clock::now();
            suffixTree.getCountOfAllSubstr();
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
