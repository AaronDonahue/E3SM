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
target_compile_definitions(tutorial PUBLIC EAMXX_HAS_CLD_FRACTION)
target_link_libraries(tutorial physics_share scream_share)
target_compile_options(tutorial PUBLIC)

# Add this library to eamxx_physics
target_link_libraries(eamxx_physics INTERFACE tutorial)

# Cloud fraction does not yet have a set of unit tests or a BFB test comparing with the F90
# code.
# The cloud fraction stand alone test, in the /tests/ directory covers a range of property
# tests.
# The BFB test will require some amount of work, as the specific ice cloud fraction scheme
# here is just an option in a more involved F90 subroutine.  Furture work would be to
# include a BFB test with the F90 code, located in /components/eam/src/physics/cam/cldfrc2m.F90

include(ScreamUtils)
CreateUnitTest(test_tutorial "tutorial_tests.cpp"
	LIBS tutorial scream_share)
