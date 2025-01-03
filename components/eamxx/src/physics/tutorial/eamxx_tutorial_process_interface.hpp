#ifndef SCREAM_TUTORIAL_HPP
#define SCREAM_TUTORIAL_HPP

#include "share/atm_process/atmosphere_process.hpp"

#include <string>

namespace scream
{

/*
 * The class object is part of the EAMxx Tutorial and is not intended for production runs.
 *
 * The AD should store exactly ONE instance of this class stored
 * in its list of subcomponents (the AD should make sure of this).
*/

class Tutorial : public AtmosphereProcess
{
public:

  // Constructors
  Tutorial (const ekat::Comm& comm, const ekat::ParameterList& params);

  // The type of subcomponent
  AtmosphereProcessType type () const { return AtmosphereProcessType::Physics; }

  // The name of the subcomponent
  std::string name () const { return "atm. process for tutorial"; }

  // Set the grid
  void set_grids (const std::shared_ptr<const GridsManager> grids_manager);

protected:

  // The three main overrides for the subcomponent
  void initialize_impl (const RunType run_type);
  void run_impl        (const double dt);
  void finalize_impl   ();

  // Keep track of field dimensions and the iteration count
  Int m_num_cols; 
  Int m_num_levs;

  std::shared_ptr<const AbstractGrid> m_grid;
}; // class CldFraction

} // namespace scream

#endif // SCREAM_TUTORIAL_HPP
