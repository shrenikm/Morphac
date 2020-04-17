# Directories
# -------------------------------------------------

set(NUMERIC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(NUMERIC_SRC_DIR ${NUMERIC_DIR}/src)
set(NUMERIC_INCLUDE_DIR ${NUMERIC_DIR}/include)
set(NUMERIC_TEST_DIR ${NUMERIC_DIR}/test)
set(NUMERIC_BINDING_DIR ${NUMERIC_DIR}/binding)
set(NUMERIC_BINDING_INCLUDE_DIR ${NUMERIC_BINDING_DIR}/include)
set(NUMERIC_BINDING_SRC_DIR ${NUMERIC_BINDING_DIR}/src)
set(NUMERIC_BINARY_DIR ${NUMERIC_BINARY_DIR}/models)
set(NUMERIC_BINDING_BINARY_DIR ${NUMERIC_BINARY_DIR}/binding)
set(NUMERIC_BINDING_INSTALL_DIR
  ${MATH_BINDING_INSTALL_DIR}/integration
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


