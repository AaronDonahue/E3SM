#include "catch2/catch.hpp"
#include "tutorial_functions.hpp"

namespace {

TEST_CASE("", "") {
  using namespace scream;
  using namespace tutorial;

  using TutorialFunc = tutorial::TutorialFunctions<Real, DefaultDevice>;
  TutorialFunc::hello_world();

  const int nx = 3;
  const int ny = 4;
  Kokkos::View<Real**> X("",nx,ny);
  Kokkos::View<Real**> Y("",nx,ny);
  Kokkos::deep_copy(X,2.0);
  Kokkos::deep_copy(Y,1.0);
  TutorialFunc::normalize(3,4,X,Y);
}

} // empty namespace
