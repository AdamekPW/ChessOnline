

# Dodajemy wszystkie pliki cpp z katalogu src
file(GLOB_RECURSE SHARED_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(shared_lib STATIC ${SHARED_SRC})  # Możesz zmienić STATIC na SHARED, jeśli potrzebujesz biblioteki dynamicznej


find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(shared_lib sfml-graphics sfml-window sfml-system)
target_include_directories(shared_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)