cmake_minimum_required(VERSION 2.8)

project(Reference_counter)
add_executable(${PROJECT_NAME} "main.c" "memoryVM.c" "memoryVMObject.c" "memoryVMTests.c")
