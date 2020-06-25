include(CTest)
enable_testing()

add_executable(flappybird main.m.cpp)

target_link_libraries(flappybird STATIC sfml)
