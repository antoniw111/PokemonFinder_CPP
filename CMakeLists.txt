cmake_minimum_required(VERSION 3.16)

# Nazwa projektu i wersja
project(PokemonFinder VERSION 1.0.1 LANGUAGES CXX)

# Standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatyzacja Qt (MOC, UIC, RCC)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Znajdowanie bibliotek Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

# Dołączanie folderu nagłówków
include_directories(include)

# --- OPCJA A: Warunkowa kompilacja ---

if(WIN32)
    # WINDOWS: Dodajemy flagę WIN32.
    # Sprawia ona, że system traktuje to jako aplikację GUI (WinMain),
    # a nie konsolową (main), dzięki czemu czarne okno znika.
    add_executable(PokemonFinder WIN32
        src/main.cpp
        src/PokemonFinder.cpp
        src/AssetManager.cpp
        include/PokemonFinder.h
        include/AssetManager.h
    )
else()
    # LINUX / MACOS: Standardowa kompilacja.
    # Tutaj flaga WIN32 nie jest potrzebna (choć CMake by ją zignorował).
    add_executable(PokemonFinder
        src/main.cpp
        src/PokemonFinder.cpp
        src/AssetManager.cpp
        include/PokemonFinder.h
        include/AssetManager.h
    )
endif()

# --- Koniec sekcji warunkowej ---

# Linkowanie bibliotek Qt do pliku wykonywalnego
target_link_libraries(PokemonFinder PRIVATE Qt6::Widgets Qt6::Network)