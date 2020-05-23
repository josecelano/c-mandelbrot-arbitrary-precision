cmake_minimum_required(VERSION 3.10)
project(c-mandelbrot-arbitrary-precision C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_INSTALL_RPATH "/usr/local/lib")

file(GLOB EXTERNAL_CODE
        tests/lib/unity/*.h
        tests/lib/unity/*.c
        )

file(GLOB PRODUCTION_CODE
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/application/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/application/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/domain/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/domain/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/infrastructure/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/infrastructure/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/presentation/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/presentation/*.c
        )

file(GLOB TEST_CODE
        ${PROJECT_SOURCE_DIR}/tests/lib/*.h
        ${PROJECT_SOURCE_DIR}/tests/lib/*.c
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/*.h
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/*.c
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/application/*.h
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/application/*.c
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/domain/*.h
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/domain/*.c
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/infrastructure/*.h
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/infrastructure/*.c
        )

add_executable(
        mandelbrot-test
        tests/main_test.c
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