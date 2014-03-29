#include "dollar.h"
#include "gtest/gtest.h"

TEST(Dollar, test1)
{
	Dollar five = Dollar(5);
	five.times(2);
	ASSERT_EQ(10, five.m_amount);
}
