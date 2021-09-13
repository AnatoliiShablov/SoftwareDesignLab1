project(LRUCache LANGUAGES CXX)

add_library(LRUCache include/LRUCache.hpp source/LRUCache.cpp)
target_include_directories(LRUCache PRIVATE   include)
target_include_directories(LRUCache INTERFACE include)

