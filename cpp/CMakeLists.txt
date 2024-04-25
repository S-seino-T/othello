cmake_minimum_required(VERSION 3.14)

project(othello_cpp CXX)

add_executable(othello main.cpp board.cpp game.cpp play.cpp AI.cpp heap.cpp)

target_compile_options(othello PUBLIC -O2 -Wall)

target_compile_features(othello PUBLIC cxx_std_17)