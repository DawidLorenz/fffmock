#include <gtest/gtest.h>
#include "fffmock.hpp"

extern "C" {
#include "../src/print.h"
#include "../src/hmi.h"
FAKE_VALUE_FUNC(double, HMI_NewtonSecondLawOfMontion, int, int);
FAKE_VALUE_FUNC(double, HMI_KineticEnergyEquation, int, int);

#include "../src/math.h"
FAKE_VALUE_FUNC(double, MATH_Add, int, int);
FAKE_VALUE_FUNC(double, MATH_Multiplication, int, int);
FAKE_VALUE_FUNC(double, MATH_Division, int, int);
}

DEFINE_FFF_GLOBALS

TEST(TestMain, CallCount_FFF) {
  int ret = printAll();

  EXPECT_EQ(ret, 0);
  EXPECT_EQ(MATH_Add_fake.call_count, 2);
  EXPECT_EQ(MATH_Multiplication_fake.call_count, 1);
  EXPECT_EQ(MATH_Division_fake.call_count, 3);
  EXPECT_EQ(HMI_NewtonSecondLawOfMontion_fake.call_count, 1);
  EXPECT_EQ(HMI_KineticEnergyEquation_fake.call_count, 1);

  RESET_FAKE(MATH_Add);
  RESET_FAKE(MATH_Multiplication);
  RESET_FAKE(MATH_Division);
  RESET_FAKE(HMI_NewtonSecondLawOfMontion);
  RESET_FAKE(HMI_KineticEnergyEquation);
}

TEST(TestMain, CallCount_FFFMOCK) {
  // Mock
  MOCK_FFF_EXPECT_CALL(m_math_add, MATH_Add).Times(2);

  // Check
  int ret = printAll();

  // Then
  EXPECT_EQ(ret, 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
