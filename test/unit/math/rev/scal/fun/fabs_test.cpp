#include <stan/math/rev/scal.hpp>
#include <gtest/gtest.h>
#include <test/unit/math/rev/scal/fun/nan_util.hpp>
#include <test/unit/math/rev/scal/util.hpp>
#include <limits>

TEST(AgradRev, fabs_var) {
  AVAR a = 0.68;
  AVAR f = fabs(a);
  EXPECT_FLOAT_EQ(0.68, f.val());

  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x, g);
  EXPECT_FLOAT_EQ(1.0, g[0]);
}

TEST(AgradRev, fabs_var_2) {
  AVAR a = -0.68;
  AVAR f = fabs(a);
  EXPECT_FLOAT_EQ(0.68, f.val());

  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x, g);
  EXPECT_FLOAT_EQ(-1.0, g[0]);
}

TEST(AgradRev, fabs_var_3) {
  AVAR a = 0.0;
  AVAR f = fabs(a);
  EXPECT_FLOAT_EQ(0.0, f.val());

  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x, g);
  EXPECT_FLOAT_EQ(0.0, g[0]);
}

struct fabs_fun {
  template <typename T0>
  inline T0
  operator()(const T0& arg1) const {
    return fabs(arg1);
  }
};

TEST(AgradRev, fabs_NaN) {
  fabs_fun fabs_;
  test_nan(fabs_, false, true);
}

TEST(AgradRev, check_varis_on_stack) {
  AVAR a = 0.68;
  test::check_varis_on_stack(stan::math::fabs(a));
}
