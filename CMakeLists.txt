cmake_minimum_required(VERSION 3.16)
project(Pirmoji_uzduotis LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Bendri projekto failai (BE main ir BE Catch) ----
add_library(pirmoji_core STATIC
    ivestis.cpp
    generatorius.cpp
    formatas.cpp
    skaiciavimas.cpp
    v03_api.cpp
    bench_runner.cpp
)

target_include_directories(pirmoji_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ---- Pagrindine programa (atskiras .exe) ----
add_executable(Pirmoji_uzduotis
    Pirmoji-uzduotis.cpp
)

target_link_libraries(Pirmoji_uzduotis PRIVATE pirmoji_core)
target_include_directories(Pirmoji_uzduotis PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ---- Unit testai (atskiras .exe) ----
add_executable(Pirmoji_uzduotis_tests
    unit_tests.cpp
    catch_amalgamated.cpp
)

target_link_libraries(Pirmoji_uzduotis_tests PRIVATE pirmoji_core)
target_include_directories(Pirmoji_uzduotis_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
