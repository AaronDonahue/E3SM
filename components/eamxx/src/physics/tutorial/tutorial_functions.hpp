#ifndef TUTORIAL_FUNCTIONS_HPP
#define TUTORIAL_FUNCTIONS_HPP

#include "share/scream_types.hpp"

#include "ekat/ekat_pack_kokkos.hpp"
#include "ekat/ekat_workspace.hpp"

namespace scream {
namespace tutorial {

template <typename ScalarT, typename DeviceT>
struct TutorialFunctions
{

  //
  // ------- Types --------
  //

  using Scalar = ScalarT;
  using Device = DeviceT;

  using KT = KokkosTypes<Device>;
  using MemberType = typename KT::MemberType;

  template <typename S>
  using view_1d = typename KT::template view_1d<S>;
  template <typename S>
  using view_2d = typename KT::template view_2d<S>;

  static void normalize(
    const Int nx, 
    const Int ny,
    const view_2d<const Real>& X,
    const view_2d<Real>&       Y); 

  static void hello_world() {printf("hello world\n");}
}; // struct Functions

} // namespace tutorial
} // namespace scream

#endif // TUTORIAL_FUNCTIONS_HPP
