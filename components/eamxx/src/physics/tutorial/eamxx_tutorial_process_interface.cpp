#include "eamxx_tutorial_process_interface.hpp"

namespace scream
{
// =========================================================================================
Tutorial::Tutorial (const ekat::Comm& comm, const ekat::ParameterList& params)
  : AtmosphereProcess(comm, params)
{
  // Nothing to do here
}

// =========================================================================================
void Tutorial::set_grids(const std::shared_ptr<const GridsManager> grids_manager)
{
  m_grid = grids_manager->get_grid("Physics");
  const auto& grid_name = m_grid->name();
  m_num_cols = m_grid->get_num_local_dofs(); // Number of columns on this rank
  m_num_levs = m_grid->get_num_vertical_levels();  // Number of levels per column
}

// =========================================================================================
void Tutorial::initialize_impl (const RunType /* run_type */)
{
  // Do nothing
}

// =========================================================================================
void Tutorial::run_impl (const double /* dt */)
{
  // Do nothing
}

// =========================================================================================
void Tutorial::finalize_impl()
{
  // Do nothing
}
// =========================================================================================

} // namespace scream
