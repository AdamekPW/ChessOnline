

# Dodajemy wszystkie pliki cpp z katalogu src
file(GLOB_RECURSE SHARED_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(shared_lib STATIC ${SHARED_SRC})  # Możesz zmienić STATIC na SHARED, jeśli potrzebujesz biblioteki dynamicznej

# Ustawiamy ścieżkę do folderu include
target_include_directories(shared_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
