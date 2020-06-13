cmake_minimum_required(VERSION 3.10)
project(c-mandelbrot-arbitrary-precision C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_INSTALL_RPATH "/usr/local/lib")

file(GLOB EXTERNAL_CODE
        tests/lib/unity/*.h
        tests/lib/unity/*.c
        )

file(GLOB PRODUCTION_CODE
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/application/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/application/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/domain/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/domain/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/domain/ascii_graph/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/domain/ascii_graph/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/domain/image/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/domain/image/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/domain/optimisation/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/domain/optimisation/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/infrastructure/user_interface/console/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/infrastructure/user_interface/console/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/infrastructure/user_interface/console/commands/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/infrastructure/user_interface/console/commands/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/infrastructure/user_interface/files/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/infrastructure/user_interface/files/*.h
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/presentation/*.c
        ${PROJECT_SOURCE_DIR}/src/mandelbrot/presentation/*.h
        )

file(GLOB TEST_CODE
        ${PROJECT_SOURCE_DIR}/tests/cycle-detection/*.c
        ${PROJECT_SOURCE_DIR}/tests/lib/*.c
        ${PROJECT_SOURCE_DIR}/tests/lib/*.h
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/*.c
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/*.h
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/application/*.c
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/application/*.h
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/domain/*.c
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/domain/*.h
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/infrastructure/user_interface/console/*.c
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/infrastructure/user_interface/console/*.h
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/infrastructure/user_interface/console/commands/*.c
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/infrastructure/user_interface/console/commands/*.h
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/infrastructure/user_interface/files/*.c
        ${PROJECT_SOURCE_DIR}/tests/mandelbrot/infrastructure/user_interface/files/*.h
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

add_executable(
        mandelbrot-orbit
        src/mandelbrot_orbit.c
        ${EXTERNAL_CODE}
        ${PRODUCTION_CODE}
)

target_link_libraries(mandelbrot-test gmp mpfr flint arb)
target_link_libraries(mandelbrot gmp mpfr flint arb)
target_link_libraries(mandelbrot-orbit gmp mpfr flint arb)