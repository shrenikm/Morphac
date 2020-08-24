# Bindings
# -------------------------------------------------

# If BUILD_PYTHON_BINDINGS is OFF, we don't need to proceed.
if(NOT BUILD_PYTHON_BINDINGS)
  return()
endif()

# Src file that creates the python module.
set(UTILS_MODULE_FILE

  utils.cc
)

# Individual binding files called by the src module file.
# They are split up into different files so that compilation is more efficient.
set(UTILS_BINDING_FILES

  angle_utils_binding.cc
  geometry_utils_binding.cc
  integrator_utils_binding.cc
  numeric_utils_binding.cc
  transforms_utils_binding.cc
)

# Prepending the directory to the files.
prepend_list(UTILS_BINDING_FILES
  ${UTILS_BINDING_SRC_DIR}/
  ${UTILS_BINDING_FILES}
)

# Adding the module as a library.
get_filename_component(module_name
  ${UTILS_MODULE_FILE} NAME_WE
)

## Get python target name. This is to prevent clashes with similar named cpp
## non binding targets.
get_python_target_name(python_target ${module_name})

pybind11_add_module(${python_target}
  SHARED
  ${UTILS_BINDING_DIR}/${UTILS_MODULE_FILE}
  ${UTILS_BINDING_FILES}
)

target_include_directories(${python_target}
  PUBLIC
  ${PYBIND11_INCLUDE_DIR}
  ${UTILS_BINDING_DIR}/include
)

# Adding library dependencies.
target_link_libraries(${python_target}
  PUBLIC
  angle_utils
  geometry_utils
  integrator_utils
  numeric_utils
  transforms_utils
)

# Setting binding target properties.
# Target prefix.
set_target_properties(${python_target}
  PROPERTIES
  PREFIX ${PYTHON_BINDING_PREFIX}
)


# Installing
# -------------------------------------------------

# Get target suffix
get_target_property(binding_suffix
  ${python_target} SUFFIX
)

# Full name of the built target (.so file that needs to be installed).
set(binding_install_file_name
  ${PYTHON_BINDING_PREFIX}${python_target}${binding_suffix}
)

# Installing compiled bindings.
install(FILES
  ${UTILS_BINDING_BINARY_DIR}/${binding_install_file_name}
  DESTINATION ${UTILS_BINDING_INSTALL_DIR}
)

# Installing __init__ files.
install(FILES
  ${UTILS_BINDING_DIR}/__init__.py
  DESTINATION ${UTILS_BINDING_INSTALL_DIR}
)
