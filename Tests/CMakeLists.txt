project(Tests LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})

conan_cmake_configure(REQUIRES gtest/1.11.0
                      GENERATORS cmake_find_package)

conan_cmake_autodetect(settings)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conancenter
                    SETTINGS ${settings})

find_package(GTest REQUIRED)

add_executable(Tests tests.cpp)
target_link_libraries(Tests PRIVATE GTest::gtest GTest::gtest_main LRUCache)

add_test(Tests Tests)
