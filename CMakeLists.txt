cmake_minimum_required(VERSION 3.12)
project(PlagiarismCatcher)

set(CMAKE_CXX_STANDARD 14)

add_executable(PlagiarismCatcher Driver.cpp Hash.cpp Hash.h Sequencer.h)