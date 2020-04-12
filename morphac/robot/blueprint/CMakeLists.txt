# Libraries
# -------------------------------------------------

set(BLUEPRINT_SRC

  footprint2D.cc
  robot2D.cc
)

foreach(file ${BLUEPRINT_SRC})
  get_filename_component(lib_name ${file} NAME_WE)
  get_header_name(header_name ${file})

  add_library(${lib_name}
    SHARED
    ${BLUEPRINT_SRC_DIR}/${file} ${BLUEPRINT_INCLUDE_DIR}/${header_name}
  )
  target_include_directories(${lib_name} PRIVATE ${BLUEPRINT_INCLUDE_DIR})
endforeach()

# Adding library dependencies.
target_link_libraries(robot2D input pose state velocity kinematic_model footprint2D)


# Tests
# -------------------------------------------------

# Blueprint tests source files.
set(BLUEPRINT_TEST_SRC

  footprint2D_test.cc
  robot2D_test.cc
)

# Creating the test executables.
foreach(file ${BLUEPRINT_TEST_SRC})
  get_filename_component(test_name ${file} NAME_WE)

  add_executable(${test_name} ${BLUEPRINT_TEST_DIR}/${file})
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# Linking depending libraries.
target_link_libraries(footprint2D_test gtest_main footprint2D)
target_link_libraries(robot2D_test gtest_main robot2D)

