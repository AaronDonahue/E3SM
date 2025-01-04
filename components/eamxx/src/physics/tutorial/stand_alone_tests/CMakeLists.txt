include (ScreamUtils)

set (TEST_BASE_NAME tutorial_standalone)

# Create the test
CreateADUnitTest(${TEST_BASE_NAME}
  LABELS tutorial physics
  LIBS tutorial
  MPI_RANKS ${TEST_RANK_START} ${TEST_RANK_END}
)

# Set AD configurable options
SetVarDependingOnTestSize(NUM_STEPS 2 5 48)
set (ATM_TIME_STEP 1800)
set (RUN_T0 2021-10-12-45000)

# Ensure test input files are present in the data dir
set(EAMxx_tests_IC_FILE_72lev         "screami_unit_tests_ne2np4L72_20220822.nc")
set(EAMxx_tests_TOPO_FILE             "USGS-gtopo30_ne2np4pg2_x6t_20230331.nc")
GetInputFile(scream/init/${EAMxx_tests_IC_FILE_72lev})
GetInputFile(cam/topo/${EAMxx_tests_TOPO_FILE})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/input.yaml)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/output.yaml
               ${CMAKE_CURRENT_BINARY_DIR}/output.yaml)
