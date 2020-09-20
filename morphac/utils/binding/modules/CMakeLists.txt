# Modules
# -------------------------------------------------

# Different modules within utils. Even though we bind all the cpp bindings under
# "utils", in order to keep it consistent with the pure python utils modules,
# we separate the imports into different modules. This is done by installing
# different __init__ files into the individual module directories.
set(UTILS_MODULES

  angle_utils
  integrator_utils
  numeric_utils
  points_utils
)


# Installing
# -------------------------------------------------

# Installing the individual __init__ files into the proper directories.
foreach(module ${UTILS_MODULES})
  morphac_package_files(
    ${UTILS_PACKAGE_DIR}/${module}
    ${UTILS_SITE_PACKAGES_DIR}/${module}
    # Files
    ${UTILS_BINDING_MODULES_DIR}/${module}/__init__.py
  )
endforeach()
