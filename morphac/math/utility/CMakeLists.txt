# Directories
# -------------------------------------------------

set(UTILITY_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(UTILITY_SRC_DIR ${UTILITY_DIR}/src)
set(UTILITY_INCLUDE_DIR ${UTILITY_DIR}/include)
set(UTILITY_TEST_DIR ${UTILITY_DIR}/test)
set(UTILITY_BINDING_DIR ${UTILITY_DIR}/binding)
set(UTILITY_BINDING_INCLUDE_DIR ${UTILITY_BINDING_DIR}/include)
set(UTILITY_BINDING_SRC_DIR ${UTILITY_BINDING_DIR}/src)
set(UTILITY_BINARY_DIR ${UTILITY_BINARY_DIR}/numeric)
set(UTILITY_BINDING_BINARY_DIR ${UTILITY_BINARY_DIR}/binding)
set(UTILITY_BINDING_INSTALL_DIR
  ${MATH_BINDING_INSTALL_DIR}/utility
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


