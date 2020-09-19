# Modules
# -------------------------------------------------

# Different modules within constants. Even though we bind all the cpp bindings under
# "constants", in order to keep it consistent with the pure python constants modules,
# we separate the imports into different modules. This is done by installing
# different __init__ files into the individual module directories.
set(CONSTANTS_MODULES
  environment_constants
  mechanics_constants
)


# Installing
# -------------------------------------------------

# Installing the individual __init__ files into the proper directories.
foreach(module ${CONSTANTS_MODULES})
  morphac_package_files(
    ${CONSTANTS_PACKAGE_DIR}/${module}
    ${CONSTANTS_SITE_PACKAGES_DIR}/${module}
    # Files
    ${CONSTANTS_BINDING_MODULES_DIR}/${module}/__init__.py
  )
endforeach()