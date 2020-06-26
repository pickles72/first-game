include(CTest)
enable_testing()

find_package(SFML COMPONENTS system window graphics REQUIRED)

add_executable(flappybird main.m.cpp Game.cpp)
target_link_libraries(flappybird sfml-graphics)
