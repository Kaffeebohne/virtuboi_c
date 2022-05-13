cmake_minimum_required(VERSION 3.20)

include_directories(src inc)

file(GLOB H_FILES inc/*.h(pp)?)
file(GLOB SRC_FILES src/*.c(pp)?)
file(GLOB MAIN_FILE src/main.c)

add_executable(${PROJECT_NAME} ${MAIN_FILE} ${H_FILES} ${SRC_FILES})
