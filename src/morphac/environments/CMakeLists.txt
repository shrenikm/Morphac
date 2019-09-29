include_directories(include)
add_library(environment2D ${CMAKE_CURRENT_SOURCE_DIR}/src/environment2D.cc)
target_include_directories(environment2D PRIVATE include)
