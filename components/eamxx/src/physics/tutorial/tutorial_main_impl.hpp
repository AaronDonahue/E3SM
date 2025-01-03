#ifndef TUTORIAL_MAIN_IMPL_HPP
#define TUTORIAL_MAIN_IMPL_HPP

#include "physics/tutorial/tutorial_functions.hpp"
#include "ekat/kokkos/ekat_subview_utils.hpp"

namespace scream {
namespace tutorial {

/*-----------------------------------------------------------------*/
template <typename S, typename D>
void TutorialFunctions<S,D>
::normalize(
  const int nx,
  const int ny,
  const view_2d<const Real>& X,
  const view_2d<Real>& Y)
{
  using KT = KokkosTypes<DefaultDevice>;
  using ExeSpace = typename KT::ExeSpace;
  using ESU = ekat::ExeSpaceUtils<ExeSpace>;
  using MemberType = typename KT::MemberType;

  /*
   * Define a functor to pass to the Kokkos parallel_for loop below.
   */
  auto f_norm = KOKKOS_LAMBDA(const MemberType& team) {
    int m = team.league_rank();
    auto normalize = [&] (int n) {
      Y(m,n) /= X(m,n);
    };
    Kokkos::parallel_for(TeamVectorRange(team,nx),normalize);
    team.team_barrier();
  };

  /*
   * Actual normalization call.
   */
  const auto policy = ESU::get_default_team_policy(nx,ny);
  Kokkos::parallel_for("",policy, f_norm);
} // normalize

/*-----------------------------------------------------------------*/

} // namespace tutorial
} // namespace scream

#endif // TUTORIAL_MAIN_IMPL_HPP
