# # Określenie minimalnej wersji CMake i nazwy projektu
# cmake_minimum_required(VERSION 3.10)
# project(ChessServer)

# # Ustawienie standardu C++
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED True)




# file(GLOB SOURCES "src/*.cpp")


# add_executable(ChessServer ${SOURCES})

# target_include_directories(ChessServer PUBLIC include)
# target_link_libraries(ChessServer PRIVATE pthread)



# Server/CMakeLists.txt

# Dodajemy wszystkie pliki cpp z katalogu src
file(GLOB_RECURSE SERVER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(server ${SERVER_SRC})

# Dodajemy bibliotekę współdzieloną
target_link_libraries(server PRIVATE shared_lib)

# Ustawiamy ścieżki do folderów include
target_include_directories(server PRIVATE
    ${CMAKE_SOURCE_DIR}/Shared/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
