cmake_minimum_required(VERSION 3.15)
project(smart_home_pract LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Подключаем папки с заголовочными файлами
include_directories(core/include)
include_directories(app/include)

# Создаем исполняемый файл (ТОЛЬКО ОДИН РАЗ!)
add_executable(smart_home_app
    core/src/EventBus.cpp
    core/src/Rule.cpp
    core/src/RuleEngine.cpp
    app/src/main.cpp
)