#include "add.h"
#include "gtest/gtest.h"

TEST(TestAdd, add1)
{
    ASSERT_EQ(3, add(1,2));
}

