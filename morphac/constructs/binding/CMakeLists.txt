# Bindings
# -------------------------------------------------

# If BUILD_PYTHON_BINDINGS is OFF, we don't need to proceed.
if(NOT BUILD_PYTHON_BINDINGS)
  return()
endif()

# Src file that creates the python module.
set(CONSTRUCTS_MODULE_FILE

  constructs.cc
)

# Individual binding files called by the src module file.
# They are split up into different files so that compilation is more efficient.
set(CONSTRUCTS_BINDING_FILES

  coordinate2D_binding.cc
  control_input_binding.cc
  pose_binding.cc
  velocity_binding.cc
  state_binding.cc
)
# Prepending the directory to the files.
prepend_list(CONSTRUCTS_BINDING_FILES ${CONSTRUCTS_BINDING_SRC_DIR}/ ${CONSTRUCTS_BINDING_FILES})

# Adding the module as a library.
get_filename_component(module_name ${CONSTRUCTS_MODULE_FILE} NAME_WE)
pybind11_add_module(
  ${module_name}
  SHARED
  ${CONSTRUCTS_BINDING_DIR}/${CONSTRUCTS_MODULE_FILE} ${CONSTRUCTS_BINDING_FILES}
)

target_include_directories(
  ${module_name}
  PRIVATE
  ${PYBIND11_INCLUDE_DIR} ${CONSTRUCTS_BINDING_DIR}/include
)

# Adding library dependencies.
target_link_libraries(${module_name}
  PUBLIC coordinate2D control_input pose velocity state)

# Setting binding target properties.
# Target prefix.
set_target_properties(${module_name} PROPERTIES PREFIX ${PYTHON_BINDING_PREFIX})


# Installing
# -------------------------------------------------

# Get target suffix
get_target_property(binding_suffix ${module_name} SUFFIX)

# Full name of the built target (.so file that needs to be installed).
set(binding_install_file_name
  ${PYTHON_BINDING_PREFIX}${module_name}${binding_suffix}
)

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

