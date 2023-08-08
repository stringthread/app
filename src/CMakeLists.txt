cmake_minimum_required(VERSION 3.13)
project(wavelet_tree CXX)
add_executable(wavelet_tree
  main.cpp
  ExBitVector.cpp
  WaveletTree.cpp
  WaveletTreeNode.cpp
)
target_include_directories(wavelet_tree
  PRIVATE ${PROJECT_SOURCE_DIR}/../lib
  PRIVATE ${PROJECT_SOURCE_DIR}
)
target_link_directories(wavelet_tree
  PRIVATE ${PROJECT_SOURCE_DIR}/../lib
)
target_link_libraries(wavelet_tree
  PRIVATE libsuccinct_bv.a
)
