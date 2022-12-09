cmake_minimum_required(VERSION 3.5)
project(tawerna
        LANGUAGES CXX)

add_executable(tawerna
        main.cpp
        tawerna.h
        tawerna.cpp)

target_compile_features(tawerna PRIVATE cxx_std_20)

set_target_properties(tawerna PROPERTIES
<<<<<<< HEAD
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
=======
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
>>>>>>> e13346c005c485f32f20900d86f8f3869f979838
