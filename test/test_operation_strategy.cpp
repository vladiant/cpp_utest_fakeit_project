#include <utest/utest.h>

#include <basic_warper.hpp>
#include <checked_warper.hpp>
#include <clamped_warper.hpp>
#include <cstdint>
#include <memory>
#include <operation_strategy.hpp>

namespace vva {

struct TestIndexedFixture {
  IOperationWarper* i;
};

UTEST_I_SETUP(TestIndexedFixture) {
  switch (utest_index) {
    case 0:
      utest_fixture->i = new BasicOperationWarper;
      break;
    case 1:
      utest_fixture->i = new CheckedOperationWarper;
      break;
    case 2:
      utest_fixture->i = new ClampedOperationWarper;
      break;
    default:
      ASSERT_TRUE(0);
      break;
  }
}

UTEST_I_TEARDOWN(TestIndexedFixture) {
  static_cast<void>(utest_result);
  static_cast<void>(utest_index);
  delete utest_fixture->i;
}

UTEST_I(TestIndexedFixture, OperationWarper, 3) {
  OperationStrategy test_strategy(*(utest_fixture->i));

  EXPECT_EQ(test_strategy(6, 2), 4);
}

}  // namespace vva
