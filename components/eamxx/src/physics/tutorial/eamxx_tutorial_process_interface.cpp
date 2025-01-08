#include "eamxx_tutorial_process_interface.hpp"
#include "share/property_checks/field_within_interval_check.hpp"

#include "ekat/ekat_assert.hpp"
#include "ekat/util/ekat_units.hpp"

#include <array>

namespace scream
{
  using namespace tutorial;
// =========================================================================================
Tutorial::Tutorial (const ekat::Comm& comm, const ekat::ParameterList& params)
  : AtmosphereProcess(comm, params)
{
  // Nothing to do here
}

// =========================================================================================
void Tutorial::set_grids(const std::shared_ptr<const GridsManager> grids_manager)
{
  using namespace ekat::units;
  using namespace ShortFieldTagsNames;

  // The units of mixing ratio Q are technically non-dimensional.
  // Nevertheless, for output reasons, we like to see 'kg/kg'.
  auto nondim = Units::nondimensional();

  m_grid = grids_manager->get_grid("Physics");
  const auto& grid_name = m_grid->name();
  m_num_cols = m_grid->get_num_local_dofs(); // Number of columns on this rank
  m_num_levs = m_grid->get_num_vertical_levels();  // Number of levels per column

  // Define the different field layouts that will be used for this process

  // Layout for 3D (2d horiz X 1d vertical) variable defined at mid-level and interfaces
  FieldLayout scalar3d_layout_mid { {COL,LEV}, {m_num_cols,m_num_levs} };

  // Set of fields used strictly as input
  add_field<Required>("T_mid", scalar3d_layout_mid, K, grid_name );

  // Set of fields that will used as input and output, i.e. updated by the process
  add_field<Updated>("T_norm_prev", scalar3d_layout_mid, K, grid_name );

  // Set of fields used strictly as output
  add_field<Computed>("T_normalized", scalar3d_layout_mid, nondim, grid_name);

  // Gather parameters for the normalization
  m_scale= m_params.get<double>("scaling_value",1.0);  // Default = 1.0
}

// =========================================================================================
void Tutorial::initialize_impl (const RunType /* run_type */)
{
  auto T_prev = get_field_out("T_norm_prev");
  T_prev.deep_copy(1.0);
  // Set property checks for fields in this process
}

// =========================================================================================
void Tutorial::run_impl (const double /* dt */)
{
  auto T_mid  = get_field_in("T_mid");
  auto T_prev = get_field_out("T_norm_prev");
  auto T_norm = get_field_out("T_normalized");
  
  auto T_mid_view  = T_mid.get_view<const Real**>();
  auto T_prev_view = T_prev.get_view<Real**>();
  auto T_norm_view = T_norm.get_view<Real**>();

  T_norm.deep_copy(T_mid);
  TutorialFunc::normalize(m_num_cols,m_num_levs,T_prev_view,T_norm_view); 
  T_norm.scale(m_scale);

  T_prev.deep_copy(T_mid);
}

// =========================================================================================
void Tutorial::finalize_impl()
{
  // Do nothing
}
// =========================================================================================

} // namespace scream
