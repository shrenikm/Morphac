# Bindings
# -------------------------------------------------

# If BUILD_PYTHON_BINDINGS is OFF, we don't need to proceed.
if(NOT BUILD_PYTHON_BINDINGS)
  return()
endif()

# Src file that creates the python module.
set(CONTROLLERS_BASIC_MODULE_FILE

  controllers_basic.cc
)

# Individual binding files called by the src module file.
# They are split up into different files so that compilation is more efficient.
set(CONTROLLERS_BASIC_BINDING_FILES

  constant_controller_binding.cc
  zero_controller_binding.cc
)

# Prepending the directory to the files.
prepend_list(CONTROLLERS_BASIC_BINDING_FILES
  ${CONTROLLERS_BASIC_BINDING_SRC_DIR}/
  ${CONTROLLERS_BASIC_BINDING_FILES}
)

# Adding the module as a library.
get_filename_component(module_name
  ${CONTROLLERS_BASIC_MODULE_FILE} NAME_WE
)

## Get python target name. This is to prevent clashes with similar named cpp
## non binding targets.
get_python_target_name(python_target ${module_name})

pybind11_add_module(${python_target}
  SHARED
  ${CONTROLLERS_BASIC_BINDING_DIR}/${CONTROLLERS_BASIC_MODULE_FILE}
  ${CONTROLLERS_BASIC_BINDING_FILES}
)

target_include_directories(${python_target}
  PUBLIC
  ${PYBIND11_INCLUDE_DIR}
  ${CONTROLLERS_BASIC_BINDING_DIR}/include
)

# Adding library dependencies.
morphac_link_static_libraries(${python_target}
  constant_controller
  zero_controller
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

morphac_install_python_package(
  ${CONTROLLERS_BASIC_PACKAGES_INSTALL_DIR}
  ${CONTROLLERS_BASIC_SITE_PACKAGES_INSTALL_DIR}
  # Files
  ${CONTROLLERS_BASIC_BINDING_DIR}/__init__.py
  ${CONTROLLERS_BASIC_BINDING_BINARY_DIR}/${binding_install_file_name}
)

