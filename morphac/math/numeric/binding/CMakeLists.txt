# Bindings
# -------------------------------------------------

# Src file that creates the python module.
set(NUMERIC_MODULE_FILE

  numeric.cc
)

# Individual binding files called by the src module file.
# They are split up into different files so that compilation is more efficient.
set(NUMERIC_BINDING_FILES

  integrator_binding.cc
  euler_integrator_binding.cc
  mid_point_integrator_binding.cc
  rk4_integrator_binding.cc
)

# Prepending the directory to the files.
prepend_list(NUMERIC_BINDING_FILES
  ${NUMERIC_BINDING_SRC_DIR}/
  ${NUMERIC_BINDING_FILES}
)

# Adding the module as a library.
get_filename_component(module_name
  ${NUMERIC_MODULE_FILE} NAME_WE
)

## Get python target name. This is to prevent clashes with similar named cpp
## non binding targets.
get_python_target_name(python_target ${module_name})

pybind11_add_module(${python_target}
  SHARED
  ${NUMERIC_BINDING_DIR}/${NUMERIC_MODULE_FILE}
  ${NUMERIC_BINDING_FILES}
)

target_include_directories(${python_target}
  PUBLIC
  ${PYBIND11_INCLUDE_DIR}
  ${NUMERIC_BINDING_DIR}/include
)

# Adding library dependencies.
morphac_link_static_libraries(${python_target}
  integrator
  euler_integrator
  mid_point_integrator
  rk4_integrator
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
  ${NUMERIC_PACKAGE_DIR}
  ${NUMERIC_SITE_PACKAGES_DIR}
  # Files
  ${NUMERIC_BINDING_DIR}/__init__.py
  ${NUMERIC_BINDING_BINARY_DIR}/${binding_install_file_name}
)

