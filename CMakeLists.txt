cmake_minimum_required(VERSION 3.10)
project(c-mandelbrot-arbitrary-precision C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_INSTALL_RPATH "/usr/local/lib")

file(GLOB EXTERNAL_CODE
        ${PROJECT_SOURCE_DIR}/external/unity/*.h
        ${PROJECT_SOURCE_DIR}/external/unity/*.c
        )

file(GLOB PRODUCTION_CODE
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/*.c
        )

file(GLOB TEST_CODE
        ${PROJECT_SOURCE_DIR}/tests/*.h
        ${PROJECT_SOURCE_DIR}/tests/*.c
        )

add_executable(
        mandelbrot-test
        src/main_test.c
        ${EXTERNAL_CODE}
        ${PRODUCTION_CODE}
        ${TEST_CODE}
        )

add_executable(
        mandelbrot
        src/main.c
        ${EXTERNAL_CODE}
        ${PRODUCTION_CODE}
        )

target_link_libraries(mandelbrot-test gmp mpfr flint arb)
target_link_libraries(mandelbrot gmp mpfr flint arb)