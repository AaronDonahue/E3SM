set(TUTORIAL_SRCS
  eamxx_tutorial_process_interface.cpp
  tutorial.cpp
)

set(TUTORIAL_HEADERS
  eamxx_tutorial_process_interface.hpp
  tutorial_functions.hpp
  tutorial_main_impl.hpp
)

add_library(tutorial ${TUTORIAL_SRCS})
target_compile_definitions(tutorial PUBLIC EAMXX_HAS_TUTORIAL)
target_link_libraries(tutorial physics_share scream_share)
target_compile_options(tutorial PUBLIC)

# Add this library to eamxx_physics
target_link_libraries(eamxx_physics INTERFACE tutorial)

#include(ScreamUtils)
#CreateUnitTest(test_tutorial "tutorial_tests.cpp"
#	LIBS tutorial scream_share)

#add_subdirectory(stand_alone_tests)
