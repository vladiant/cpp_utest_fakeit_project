#include <basic_warper.hpp>
#include <utest/utest.h>
#include <checked_warper.hpp>
#include <clamped_warper.hpp>
#include <cstdint>
#include <memory>
#include <operation_strategy.hpp>

namespace vva {

struct TestIndexedFixture{
  std::unique_ptr<IOperationWarper> i;
};

UTEST_I_SETUP(TestIndexedFixture) {
  switch (utest_index)
  {
  case 0:
    (utest_fixture->i).reset(new BasicOperationWarper);
    break;
  case 1:
    (utest_fixture->i).reset(new CheckedOperationWarper);
    break;
  case 2:
    (utest_fixture->i).reset(new ClampedOperationWarper);
    break;
  default:
    ASSERT_TRUE(0);
    break;
  }
}

UTEST_I_TEARDOWN(TestIndexedFixture) {
}

UTEST_I(TestIndexedFixture, BasicOperationWarper, 0) {
  OperationStrategy test_strategy(*(utest_fixture->i));

  EXPECT_EQ(test_strategy(6, 2), 4);
}

UTEST_I(TestIndexedFixture, CheckedOperationWarper, 1) {
  OperationStrategy test_strategy(*(utest_fixture->i));

  EXPECT_EQ(test_strategy(6, 2), 4);
}

UTEST_I(TestIndexedFixture, ClampedOperationWarper, 2) {
  OperationStrategy test_strategy(*(utest_fixture->i));

  EXPECT_EQ(test_strategy(6, 2), 4);
}

}  // namespace vva
