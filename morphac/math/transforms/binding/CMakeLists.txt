# Bindings
# -------------------------------------------------

# Src file that creates the python module.
set(TRANSFORMS_MODULE_FILE

  transforms.cc
)

# Individual binding files called by the src module file.
# They are split up into different files so that compilation is more efficient.
set(TRANSFORMS_BINDING_FILES

  transforms_binding.cc
)

# Prepending the directory to the files.
prepend_list(TRANSFORMS_BINDING_FILES
  ${TRANSFORMS_BINDING_SRC_DIR}/
  ${TRANSFORMS_BINDING_FILES}
)

# Adding the module as a library.
get_filename_component(module_name
  ${TRANSFORMS_MODULE_FILE} NAME_WE
)

## Get python target name. This is to prevent clashes with similar named cpp
## non binding targets.
get_python_target_name(python_target ${module_name})

pybind11_add_module(${python_target}
  SHARED
  ${TRANSFORMS_BINDING_DIR}/${TRANSFORMS_MODULE_FILE}
  ${TRANSFORMS_BINDING_FILES}
)

target_include_directories(${python_target}
  PUBLIC
  ${PYBIND11_INCLUDE_DIR}
  ${TRANSFORMS_BINDING_DIR}/include
)

# Adding library dependencies.
morphac_link_static_libraries(${python_target}
  transforms
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
  ${TRANSFORMS_PACKAGE_DIR}
  ${TRANSFORMS_SITE_PACKAGES_DIR}
  # Files
  ${TRANSFORMS_BINDING_DIR}/__init__.py
  ${TRANSFORMS_BINDING_BINARY_DIR}/${binding_install_file_name}
)



