# Bindings
# -------------------------------------------------

set(CONSTRUCTS_BINDING_FILE

  constructs.cc
)

get_filename_component(binding_name ${CONSTRUCTS_BINDING_FILE} NAME_WE)
pybind11_add_module(${binding_name} SHARED ${CONSTRUCTS_BINDING_DIR}/${CONSTRUCTS_BINDING_FILE})
target_include_directories(${binding_name} PRIVATE ${PYBIND11_INCLUDE_DIR})
# Setting binding target properties.
# Target prefix.
set_target_properties(${binding_name} PROPERTIES PREFIX ${PYTHON_BINDING_PREFIX})

# Adding library dependencies.
target_link_libraries(${binding_name}
  PUBLIC coordinate2D control_input pose velocity state)

# Get target suffix
get_target_property(binding_suffix ${binding_name} SUFFIX)

# Full name of the built target (.so file that needs to be installed).
set(binding_install_file_name
  ${PYTHON_BINDING_PREFIX}${binding_name}${binding_suffix}
)

# Install
# -------------------------------------------------

# Installing compiled bindings.
install(FILES
  ${CONSTRUCTS_BINDING_BINARY_DIR}/${binding_install_file_name}
  DESTINATION ${PYTHON_BINDING_INSTALL_DIR}/morphac/constructs
)

# Installing __init__ files.
install(FILES
  ${CONSTRUCTS_BINDING_DIR}/__init__.py
  DESTINATION ${PYTHON_BINDING_INSTALL_DIR}/morphac/constructs
)


