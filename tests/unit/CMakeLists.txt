include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runUnitTests bookmark_model_spec.cpp)

target_link_libraries(runUnitTests gtest gtest_main)
target_link_libraries(runUnitTests src)
