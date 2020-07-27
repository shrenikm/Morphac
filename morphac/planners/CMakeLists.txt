# Directories
# -------------------------------------------------

set(PLANNERS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PLANNERS_BINARY_DIR ${MORPHAC_BINARY_DIR}/planners)
set(PLANNERS_BINDING_BINARY_DIR ${PLANNERS_BINARY_DIR}/binding)
set(PLANNERS_BINDING_INSTALL_DIR ${PYTHON_BINDING_INSTALL_DIR}/planners)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(base)


# Installing
# -------------------------------------------------

# Installing __init__ files.
install(FILES
  ${PLANNERS_DIR}/__init__.py
  DESTINATION
  ${PLANNERS_BINDING_INSTALL_DIR}
)
