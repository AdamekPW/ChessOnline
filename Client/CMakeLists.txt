# # Określenie minimalnej wersji CMake i nazwy projektu
# cmake_minimum_required(VERSION 3.10)
# project(ChessClient)

# # Ustawienie standardu C++
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)


# file(GLOB SOURCES "src/*.cpp")


# add_executable(ChessClient ${SOURCES})

# target_include_directories(ChessClient PUBLIC include)
# target_link_libraries(ChessClient PRIVATE pthread)



# Client/CMakeLists.txt

# Dodajemy wszystkie pliki cpp z katalogu src
file(GLOB_RECURSE CLIENT_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(client ${CLIENT_SRC})

# Dodajemy bibliotekę współdzieloną
target_link_libraries(client PRIVATE shared_lib)



# Ustawiamy ścieżki do folderów include
target_include_directories(client PRIVATE
    ${CMAKE_SOURCE_DIR}/Shared/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
