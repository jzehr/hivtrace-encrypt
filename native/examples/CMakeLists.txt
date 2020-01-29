# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT license.

cmake_minimum_required(VERSION 3.12)

project(SEALExamples VERSION 3.4.5 LANGUAGES CXX)

# Executable will be in ../bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SEALExamples_SOURCE_DIR}/../bin)

add_executable(sealexamples examples.cpp)
target_sources(sealexamples
    PRIVATE
        1_bfv_basics.cpp
        2_encoders.cpp
        3_levels.cpp
        4_ckks_basics.cpp
        5_rotation.cpp
        6_performance.cpp
)

## this will create a new executable, called 'first argument' in tuple, based off file from second argument in tuple ##
#add_executable(temp_blah temp_examples.cpp)
#add_executable(CKKS_test CKKS.cpp)
#add_executable(sub_test t.cpp)
#add_executable(compare_test compare.cpp)
#add_executable(pairwise_CKKS_test pairwise_CKKS.cpp)
add_executable(pairwise_CKKS_temp pairwise_CKKS_temp.cpp)
add_executable(pairwise_BFV_test pairwise_BFV.cpp)
#add_executable(matrix_test matrix_test.cpp)
add_executable(BFV_encryptor BFV_encryptor.cpp)
add_executable(site_A site_A_encrypt.cpp)
add_executable(site_B site_B_encrypt.cpp)
add_executable(read_in_hamming read_in_hamming.cpp)
#add_executable(compare_A_B compare_A_B.cpp)
add_executable(t_compare test_compare.cpp)


# Import Microsoft SEAL
<<<<<<< HEAD
find_package(SEAL 3.2.0 EXACT REQUIRED)
set(SEAL_DEBUG 1)
=======
find_package(SEAL 3.4.5 EXACT REQUIRED
    # Providing a path so this can be built without installing Microsoft SEAL
    PATHS ${SEALExamples_SOURCE_DIR}/../src/cmake
)
>>>>>>> 9fc376c19488be2bfd213780ee06789754f4b2c2

# Link Microsoft SEAL
target_link_libraries(sealexamples SEAL::seal)

## link the libraries between your executable and SEAL ##
#target_link_libraries(temp_blah SEAL::seal)
#target_link_libraries(CKKS_test SEAL::seal)
#target_link_libraries(sub_test SEAL::seal)
#target_link_libraries(compare_test SEAL::seal)
#target_link_libraries(pairwise_CKKS_test SEAL::seal)
target_link_libraries(pairwise_BFV_test SEAL::seal)
#target_link_libraries(matrix_test SEAL::seal)
target_link_libraries(pairwise_CKKS_temp SEAL::seal)
target_link_libraries(BFV_encryptor SEAL::seal)
target_link_libraries(site_A SEAL::seal)
target_link_libraries(site_B SEAL::seal)
target_link_libraries(read_in_hamming SEAL::seal)
#target_link_libraries(compare_A_B SEAL::seal)
target_link_libraries(t_compare SEAL::seal)
