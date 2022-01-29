#include <gtest/gtest.h>

// Função definida em um outro arquivo
int Sum(int a, int b)
{
	return a + b;
}

// Expect não interrompe a testagem, já o Assert interrompe.
TEST(SumTestSuite, TestSum_Simple)
{
	EXPECT_EQ(Sum(2, 2), 4);
	EXPECT_EQ(Sum(2, -2), 0);
	EXPECT_EQ(Sum(2, -8), -6);
}

TEST(SumTestSuite, TestSum_Zero)
{
	EXPECT_EQ(Sum(0, 0), 0);
	EXPECT_EQ(Sum(0, -0), 0);
	EXPECT_EQ(Sum(-0, -0), 0);
}

TEST(SumTestSuite, TestSum_Large)
{
	constexpr int maxInt = std::numeric_limits<int>::max();
	constexpr int minInt = std::numeric_limits<int>::min();

	EXPECT_EQ(Sum(maxInt, 1), minInt);
	EXPECT_EQ(Sum(minInt, -1), maxInt);
}