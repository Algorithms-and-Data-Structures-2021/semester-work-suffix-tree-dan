# Здесь вы можете создавать свои исполняемые файлы (executables)
# исполянемый файл = контрольный тест

# Пример создания контрольного теста (исполняемого файла) под названием demo_benchmark.
# Исходный код предоставлен в файле demo_benchmark.cpp текущей директории.
add_executable(demo_benchmark tree_creation_benchmark.cpp)

# Примечание: Не забываем подключить (прилинковать) библиотеку ${PROJECT_NAME} с реализацией структуры данных.
set(PROJECT_NAME semester_work_suffix_tree_dan)
target_link_libraries(demo_benchmark PRIVATE project_paths project_warnings ${PROJECT_NAME})
