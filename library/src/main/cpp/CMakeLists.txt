cmake_minimum_required(VERSION 3.22.1)
project("pygmalion")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/dobby/Includes"
)

file(GLOB_RECURSE SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/*.c"
    "${PROJECT_SOURCE_DIR}/**/*.c"
    "${PROJECT_SOURCE_DIR}/*.cc"
    "${PROJECT_SOURCE_DIR}/**/*.cc"
    "${PROJECT_SOURCE_DIR}/*.cpp"
    "${PROJECT_SOURCE_DIR}/**/*.cpp"
)
file(GLOB_RECURSE IMPORTED_LIBS
    ${PROJECT_SOURCE_DIR}/**/${ANDROID_ABI}/*.a
)

add_library(${CMAKE_PROJECT_NAME} SHARED
    "${SOURCE_FILES}"
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        log
        ${IMPORTED_LIBS}
)