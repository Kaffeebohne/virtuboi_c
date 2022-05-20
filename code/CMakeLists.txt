cmake_minimum_required(VERSION 3.20)

include_directories(src inc)

file(GLOB H_FILES inc/*.h)
file(GLOB SRC_FILES src/*.c)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
#if CMAKE_BUILD_TYPE == Debug || CMAKE_BUILD_TYPE == RelWithDebInfo
add_definitions(-DDEBUGGING_ON=1)
#endif

add_executable(${PROJECT_NAME} ${MAIN_FILE} ${H_FILES} ${SRC_FILES})
