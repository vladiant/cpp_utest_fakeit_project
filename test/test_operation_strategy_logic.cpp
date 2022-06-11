#include <utest/utest.h>
#include <cstdint>
#include <fakeit/fakeit.hpp>
#include <i_warper.hpp>
#include <limits>
#include <operation_strategy.hpp>
#include <memory>

namespace {
using fakeit::Mock;
using fakeit::When;
}  // namespace

namespace vva {

struct MockedOperationStrategyTest {
  std::unique_ptr<fakeit::Mock<IOperationWarper>> mockWarper_;
};

UTEST_F_SETUP(MockedOperationStrategyTest) {
  utest_fixture->mockWarper_ = std::make_unique<fakeit::Mock<IOperationWarper>>();
}

UTEST_F_TEARDOWN(MockedOperationStrategyTest) {
}

UTEST_F(MockedOperationStrategyTest, MockOperationStrategy_Arg_Result) {
  constexpr int16_t first_arg = 6;
  constexpr int16_t second_arg = 2;
  constexpr int16_t operation_result = 4;

  constexpr int16_t first_stage_result = 8;
  constexpr int16_t second_stage_result = 16;
  constexpr int16_t third_stage_result = 4;

  When(Method(*(utest_fixture->mockWarper_), addition).Using(first_arg, second_arg))
      .Return(first_stage_result);
  When(Method(*(utest_fixture->mockWarper_), multiplication).Using(first_stage_result, 2))
      .Return(second_stage_result);
  When(Method(*(utest_fixture->mockWarper_), subtraction).Using(first_arg, second_arg))
      .Return(third_stage_result);
  When(Method(*(utest_fixture->mockWarper_), division)
           .Using(second_stage_result, third_stage_result))
      .Return(operation_result);

  OperationStrategy test_strategy((utest_fixture->mockWarper_)->get());

  EXPECT_EQ(test_strategy(first_arg, second_arg), operation_result);
}

}  // namespace vva
