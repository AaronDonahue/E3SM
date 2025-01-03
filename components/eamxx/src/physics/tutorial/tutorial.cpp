#include "physics/tutorial/tutorial_main_impl.hpp"
#include "share/scream_types.hpp"

namespace scream {
namespace tutorial {

/*
 * Explicit instantiation for doing main on Reals using the
 * default device.
 */

template struct TutorialFunctions<Real,DefaultDevice>;

} // namespace tutorial
} // namespace scream
