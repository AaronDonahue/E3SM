set(TUTORIAL_SRCS
  eamxx_tutorial_process_interface.cpp
)

set(TUTORIAL_HEADERS
  eamxx_tutorial_process_interface.hpp
)

add_library(tutorial ${TUTORIAL_SRCS})
target_compile_definitions(tutorial PUBLIC EAMXX_HAS_TUTORIAL)
target_link_libraries(tutorial physics_share scream_share)
target_compile_options(tutorial PUBLIC)

# Add this library to eamxx_physics
target_link_libraries(eamxx_physics INTERFACE tutorial)

# Add test
CreateUnitTest(mustpass "test_mustpass.cpp"
	LIBS tutorial LABELS tutorial
	MPI_RANKS 1 ${SCREAM_TEST_MAX_RANKS}
)
