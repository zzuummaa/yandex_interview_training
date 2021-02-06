cmake_minimum_required(VERSION 3.17)
project(yandex_interview_training)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(articles)
add_subdirectory(basics)
add_subdirectory(codeforce_beta_round_9)
add_subdirectory(contest)
add_subdirectory(leetcode)
add_subdirectory(other)

#add_executable(yandex_contest src/rock_and_decoration/main.cpp)