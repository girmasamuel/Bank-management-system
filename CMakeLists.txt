cmake_minimum_required(VERSION 3.10)
project(Bank-management-system)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g") #debugging flags if needed

add_executable(start_system
  main.cpp
  src/graphics.cpp
  src/bank_system.cpp
  src/binary_tree.cpp
  src/transaction_stack.cpp

)

#target for cleaning
add_custom_target(clean_build COMMAND ${CMAKE_COMMAND} -E remove_directory build)

