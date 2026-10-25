cmake_minimum_required(VERSION 3.15)
project(smart_home_pract LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем, где искать заголовочные файлы
include_directories(core/include)
include_directories(app/include)

# Создаем исполняемый файл из наших .cpp
add_executable(smart_home_app
    core/src/EventBus.cpp
    app/src/main.cpp
)