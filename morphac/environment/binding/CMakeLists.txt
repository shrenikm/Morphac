# Bindings
# -------------------------------------------------

# Src file that creates the python module.
set(ENVIRONMENT_MODULE_FILE

  environment.cc
)

# Individual binding files called by the src module file.
# They are split up into different files so that compilation is more efficient.
set(ENVIRONMENT_BINDING_FILES

  map_binding.cc
)

# Prepending the directory to the files.
prepend_list(ENVIRONMENT_BINDING_FILES
  ${ENVIRONMENT_BINDING_SRC_DIR}/
  ${ENVIRONMENT_BINDING_FILES}
)

# Adding the module as a library.
get_filename_component(module_name
  ${ENVIRONMENT_MODULE_FILE} NAME_WE
)

## Get python target name. This is to prevent clashes with similar named cpp
## non binding targets.
get_python_target_name(python_target ${module_name})

pybind11_add_module(${python_target}
  SHARED
  ${ENVIRONMENT_BINDING_DIR}/${ENVIRONMENT_MODULE_FILE}
  ${ENVIRONMENT_BINDING_FILES}
)

target_include_directories(${python_target}
  PUBLIC
  ${PYBIND11_INCLUDE_DIR}
  ${ENVIRONMENT_BINDING_DIR}/include
)

# Adding library dependencies.
morphac_link_static_libraries(${python_target}
  map
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

morphac_package_files(
  ${ENVIRONMENT_PACKAGE_DIR}
  ${ENVIRONMENT_SITE_PACKAGES_DIR}
  # Files
  ${ENVIRONMENT_BINDING_DIR}/__init__.py
  ${ENVIRONMENT_BINDING_BINARY_DIR}/${binding_install_file_name}
)




