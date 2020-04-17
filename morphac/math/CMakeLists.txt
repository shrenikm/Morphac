# Directories
# -------------------------------------------------

set(MATH_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(MATH_BINARY_DIR ${MORPHAC_BINARY_DIR}/math)
set(MATH_BINDING_BINARY_DIR ${MATH_BINARY_DIR}/binding)
set(MATH_BINDING_INSTALL_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/morphac/math
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(numeric)


# Installing
# -------------------------------------------------

# Installing __init__ files.
install(FILES
  ${MATH_DIR}/__init__.py
  DESTINATION
  ${MATH_BINDING_INSTALL_DIR}
)
