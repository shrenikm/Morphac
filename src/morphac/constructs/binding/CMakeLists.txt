# Bindings
# -------------------------------------------------

set(CONSTRUCTS_BINDING_FILE

  constructs.cc
)

get_filename_component(binding_name ${CONSTRUCTS_BINDING_FILE} NAME_WE)
pybind11_add_module(${binding_name} SHARED ${CONSTRUCTS_BINDING_DIR}/${CONSTRUCTS_BINDING_FILE})
target_include_directories(${binding_name} PRIVATE ${PYBIND11_INCLUDE_DIR})
# Setting binding target properties
# prefix
set_target_properties(${binding_name} PROPERTIES PREFIX ${PYTHON_BINDING_PREFIX})

# Adding library dependencies.
target_link_libraries(${binding_name}
  PUBLIC coordinate2D control_input pose velocity state)

