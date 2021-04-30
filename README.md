# Суффиксное дерево

[![CMake](https://github.com/Algorithms-and-Data-Structures-2021/semester-work-suffix-tree-dan/actions/workflows/cmake.yml/badge.svg)](https://github.com/Algorithms-and-Data-Structures-2021/semester-work-suffix-tree-dan/actions/workflows/cmake.yml)



  В данном проекте реализуется структура данных под названием суффиксное дерево.
- **Суффиксное дерево для строки s** – это минимальное по числу вершин дерево, каждое ребро которого помечено непустой подстрокой s таким образом, что каждый суффикс s[i..n-1] может быть прочитан на пути из корня до какого-нибудь листа и, наоборот, каждая строка, прочитанная на пути из корня до какого-нибудь листа, является суффиксом s.
- Суффиксное дерево часто используют в задачах со строками: поиск подстроки, наибольшей общей подстроки двух строк, подсчет количества различных подстрок в строке и т.д.
- В суффиксном дереве самом по себе есть только одна операция - построение. В данном проекте используются ещё две - проверка наличия подстроки и подсчет количества различных подстрок.
- Построение дерева выполняется за T = O(n) и M = O(n), где n - длина строки. Поиск подстроки - T = O(m), где m - длина подстроки, подсчёт количества подстрок - O(n).

## Команда "Odin's bless"


| Фамилия Имя   | Вклад (%) | Настоящее имя              |
| :---          |   ---:    |  ---:                 |
| Галеев Даниль   | 100       |  Мигель               |

**Девиз команды**

О́ди́н в поле воин!

## Структура проекта

Проект состоит из следующих частей:

- [`src`](src)/[`include`](include) - реализация структуры данных (исходный код и заголовочные файлы);
- [`benchmark`](benchmark) - контрольные тесты производительности структуры данных (операции добавления, удаления,
  поиска и пр.);
- [`examples`](examples) - примеры работы со структурой данных;
- [`dataset`](dataset) - наборы данных для запуска контрольных тестов и их генерация;
- [`graphics`](graphics) - скрипты для визуализации данных, если захотите. Там же лежит csv файл, по которому эти графики строятся

## Требования (Prerequisites)

Рекомендуемые требования:

1. С++ компилятор c поддержкой стандарта C++17.
2. Система автоматизации сборки _CMake_ (версия _3.15.x_ и выше).
3. Интерпретатор _Python_ (версия _3.7.x_ и выше).
4. Рекомендуемый объем оперативной памяти - не менее 8 ГБ.
5. Свободное дисковое пространство объемом ~ 0.5 ГБ (набор данных для контрольных тестов).

## Сборка и запуск



### Пример

#### Сборка проекта

Зайдите на [главную страницу](https://github.com/Algorithms-and-Data-Structures-2021/semester-work-suffix-tree-dan) проекта и нажмите кнопку code, показанную  на рисунке снизу


![clone](https://user-images.githubusercontent.com/70788419/116008429-26ca8100-a61d-11eb-8d58-9a2f5ff2394b.png)
 
 Либо вы можете склонировать себе проект в локальный репозиторий с помощью консольной команды:
```shell
git clone https://github.com/Algorithms-and-Data-Structures-2021/semester-work-suffix-tree-dan
```


Для автоматичекой сборки зайдите в IDE (у меня это CLion) и нажмите на кнопку сборки проекта (в моем случае зеленый молоток)


![build](https://user-images.githubusercontent.com/70788419/116302645-1dbaea80-a7aa-11eb-91aa-088a8bd0fd16.png)



#### Генерация тестовых данных

Для того, чтобы сгенерировать тестовые данные, вам нужно в консоли перейти в папку dataset, поскольку именно там хранятся скрипты, которые позволят
вам сгенерировать данные

Генерация тестового набора данных в
формате [comma-seperated values (CSV)](https://en.wikipedia.org/wiki/Comma-separated_values):

```shell
# переход в папку генерации набора данных
cd dataset

# запуск Python-скрипта
python generate_csv_dataset.py
python substring_generator.py
```

Для удобства запуска контрольных тестов данные организованы в директориях:

```shell
dataset/data/
  tree-creation/
    01/
      100.csv
      ...
      1000000.csv
    02/ ...
    03/ ...
    ...
    10/ ...
  has-substring/
    01/
      100.csv
      ...
      5000000.csv
    ...
    10/ ...
  ...
```

По названию директории `/dataset/data/tree-creation` можно понять, что здесь хранятся наборы данных для контрольных тестов по
**построению дерева**. Названия файлов `100.csv`. `1000000.csv` и т.д. хранят информацию о размере набора данных (т.е. длина строки). 
Советую для подсчета различных подстрок использовать те же самые наборы данных, что и для построения дерева, дабы не делать лишних ненужных шагов. При большом желании, можете все-таки сгенерировать отдельные данные для данной операции.

#### Контрольные тесты (benchmarks)

Для запуска контрольных тестов для начала перейдите в папку benchmarks. Там вы увидите три текстовых файла с настройками для каждого теста
Там всё предельно просто, но во избежании ошибочных действий, давайте разберём, что же там находится
```
absolute path to the dataset directory=/home/miguelius/CLionProjects/semester-work-suffix-tree-dan/dataset/data/tree-creation
absolute path to the directory, where you want to store results of benchmarks=/home/miguelius/CLionProjects/semester-work-suffix-tree-dan/benchmark/results/test
file names=100.csv,500.csv,1000.csv,5000.csv,10000.csv,25000.csv,50000.csv,100000.csv,250000.csv,500000.csv,750000.csv,1000000.csv
count of one data tests=10
```
Как вы можете видеть, здесь сначала идёт описание, потом идёт значение, которое нужно установить.
1. Абсолютный путь до папки с тестовыми данными
2. Абсолютный путь к папке, в которую выхотите записать файлы с результатами тестирования
3. Имя файлов, с которых вы будете читать данные. Таким образом, вы можете выбирать, какие данные вы будете тестировать
4. Количество повторных запусков для каждого набора данных

Для построения дерева и подсчета количества различных подстрок одинаковы, но в файле для проверки наличия подстрки есть дополнительная строка
~~~
absolute path to the test string=/home/miguelius/CLionProjects/semester-work-suffix-tree-dan/dataset/data/has_substr/test-string.csv
~~~
Это абсолютный путь до вашей тестовой строки, из который были сгенерированы ваши подстроки. Не переживайте, скрипт python сделает всё за вас, самое главное увидеть нужный файл, что не должно составить большого труда

Мои тестовые наборы данных на [Google Drive](https://drive.google.com/drive/folders/1z4UfDpzZL1zoXR3qEMbdqXa6PhhhvMZR?usp=sharing).

##### Список контрольных тестов

| Название                  | Описание                                | Метрики         |
| :---                      | ---                                     | :---            |
| `tree_creation_benchmark`    | создание суффиксного дерева             | _время_         |
| `has_substring_benchmark`    | добавление элементов в структуру данных | _время_|
| `count_all_substr_benchmark` | подсчет кол-ва различных подстрок       | _время_             |

##### Примеры запуска

Не забудьте перед запуском **поменять файл настроек**, иначе тест **не будет работать**!

```shell
# в параметрах запуска нужно указать абсолютный путь до настроек для запускаемого теста
./tree_creation_benchmark /home/miguelius/CLionProjects/semester-work-suffix-tree-dan/benchmark/tree-creation-settings.txt
```
##### Визуализация для особо интересующихся

Вы уже видели в структуре проекта, что скрипты находятся в папке graphics. Вам нужно перейти туда. 

Для начала разберемся с тем, по каким данным строятся графики. Вы можете увидеть файл data.csv. Давайте откроем  его!


![csv-example](https://user-images.githubusercontent.com/70788419/116384011-1afadc80-a820-11eb-84b3-cda4b6f21308.png)

В принципе все и так понятно, но все равно распишем.
- В первом столбце хранятся длины строк, на которых проводилось тестирование
- Остальные столбцы хранят значения результатов теста в наносекундах(советую использовать средние значения, подсчитанные из результатов тестов по всем наборам данных)
- Если хотите построить графики для своих значений, поменяйте их в этом файле

Теперь, когда в файле лежат нужные данные, построим графики
```shell
cd /your/path/to/the/directory/graphics
python count_substr.py
python has_substr.py
python tree_creation.py
```

Теперь в папке со скриптами у вас появятся картники с графиками. Вот и всё!

## Источники
1. [Вики](https://ru.wikipedia.org/wiki/%D0%A1%D1%83%D1%84%D1%84%D0%B8%D0%BA%D1%81%D0%BD%D0%BE%D0%B5_%D0%B4%D0%B5%D1%80%D0%B5%D0%B2%D0%BE)
2. [Хабр](https://habr.com/ru/post/258121/)
3. [Подробная лекция по суффиксному дереву и алгоритму Укконена](https://www.youtube.com/watch?v=zAA7jNv3e2E)

