cmake_minimum_required(VERSION 3.10)
project(ForestSurvivalSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Zbierz źródła i nagłówki
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# Wyszukaj SFML
# Dodaj ścieżkę do folderu SFML/cmake
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}")
set(SFML_DIR "C:/SFML/lib/cmake/SFML")

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

# Dodaj plik wykonywalny
add_executable(ForestSurvivalSimulator ${SOURCES} ${HEADERS})

# Linkowanie z SFML
target_link_libraries(ForestSurvivalSimulator sfml-graphics sfml-window sfml-system)

# Dołącz nagłówki
target_include_directories(ForestSurvivalSimulator PRIVATE ${CMAKE_SOURCE_DIR}/include)

# (opcjonalnie) kopiuj assets jeśli potrzebne
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# Skopiuj folder assets do katalogu build/
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
# Skopiuj folder assets do katalogu budowania
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
# Kopiowanie katalogu assets do katalogu budowy
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})



