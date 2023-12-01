cmake_minimum_required(VERSION 3.26)
project(ByteAdditionDiscreteMath C)

set(SOURCES
src/reader.c
src/base_struct.c
src/operations_with_line.c
src/main.c
)

include_directories(include)

add_executable(ByteAdditionDiscreteMath ${SOURCES})
