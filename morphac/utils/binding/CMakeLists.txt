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

pybind11_add_module(${module_name}
  SHARED
  ${UTILS_BINDING_DIR}/${UTILS_MODULE_FILE}
  ${UTILS_BINDING_FILES}
)

target_include_directories(${module_name}
  PUBLIC
  ${PYBIND11_INCLUDE_DIR}
  ${UTILS_BINDING_DIR}/include
)

# Adding library dependencies.
target_link_libraries(${module_name}
  PUBLIC
  angle_utils
)

# Setting binding target properties.
# Target prefix.
set_target_properties(${module_name}
  PROPERTIES
  PREFIX ${PYTHON_BINDING_PREFIX}
)


# Installing
# -------------------------------------------------

# Get target suffix
get_target_property(binding_suffix
  ${module_name} SUFFIX
)

# Full name of the built target (.so file that needs to be installed).
set(binding_install_file_name
  ${PYTHON_BINDING_PREFIX}${module_name}${binding_suffix}
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