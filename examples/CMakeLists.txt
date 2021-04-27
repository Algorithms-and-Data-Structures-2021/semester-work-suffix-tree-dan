# Добавьте сюда исполняемые файлы с примерами работы со структурой данных
add_executable(examples examples.cpp)
set(PROJECT_NAME semester_work_suffix_tree_dan)
target_link_libraries(examples PRIVATE project_paths project_warnings ${PROJECT_NAME})