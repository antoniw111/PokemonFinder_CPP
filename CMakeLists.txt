cmake_minimum_required(VERSION 3.16)

# Nazwa projektu i wersja standardu C++
project(PokemonFinder VERSION 1.0 LANGUAGES CXX)

# Wymagamy C++17 (nowoczesny standard, choć Qt6 lubi nawet C++20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Włączamy automatyczne generowanie kodu przez Qt (MOC, UIC, RCC)
# To magia Qt, która pozwala na działanie Sygnałów i Slotów
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Szukamy biblioteki Qt6 w systemie
# COMPONENTS: Widgets (GUI), Network (do pobierania z API)
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

# Dodajemy pliki do projektu
# INCLUDE_DIRECTORIES mówi kompilatorowi, gdzie szukać plików .h
include_directories(include)

# Definiujemy plik wykonywalny i pliki źródłowe
add_executable(PokemonFinder
    src/main.cpp
    src/PokemonFinder.cpp
    src/AssetManager.cpp
    include/PokemonFinder.h
    include/AssetManager.h
)

# Linkujemy biblioteki Qt do naszego pliku wykonywalnego
target_link_libraries(PokemonFinder PRIVATE Qt6::Widgets Qt6::Network)