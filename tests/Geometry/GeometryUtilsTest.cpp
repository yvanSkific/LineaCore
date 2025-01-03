#include "LineaCore/Geometry/GeometryUtils.hpp"
#include "LineaCore/Geometry/Point2D.hpp"
#include <gtest/gtest.h>
#include <cmath>

using namespace LineaCore::Geometry;

TEST(GeometryUtilsTest, BrentFunctionValue_FiniteInterval) {
    auto f = [](double x) { return x * x - 4; }; // Function f(x) = x^2 - 4
    Point2D result = GeometryUtils::BrentFunctionValue(0.0, 5.0, 0.0, 1.0, f, nullptr);
    EXPECT_NEAR(result.X, 2.0, 1E-10);
    EXPECT_NEAR(result.Y, 0.0, 1E-10);
}

TEST(GeometryUtilsTest, BrentFunctionValue_InfiniteInterval) {
    auto f = [](double x) { return x * x - 4; }; // Function f(x) = x^2 - 4
    Point2D result = GeometryUtils::BrentFunctionValue(0.0, std::numeric_limits<double>::infinity(), 0.0, 1.0, f, nullptr);
    EXPECT_NEAR(result.X, 2.0, 1E-10);
    EXPECT_NEAR(result.Y, 0.0, 1E-10);
}

TEST(GeometryUtilsTest, BrentFunctionValue_ByExcess) {
    auto f = [](double x) { return x * x - 4; }; // Function f(x) = x^2 - 4
    bool byExcess = true;
    Point2D result = GeometryUtils::BrentFunctionValue(0.0, 5.0, 0.0, 1.0, f, &byExcess);
    EXPECT_NEAR(result.X, 2.0, 1E-10);
    EXPECT_NEAR(result.Y, 0.0, 1E-10);
}

TEST(GeometryUtilsTest, BrentFunctionValue_ByDefault) {
    auto f = [](double x) { return x * x - 4; }; // Function f(x) = x^2 - 4
    bool byExcess = false;
    Point2D result = GeometryUtils::BrentFunctionValue(0.0, 5.0, 0.0, 1.0, f, &byExcess);
    EXPECT_NEAR(result.X, -2.0, 1E-10);
    EXPECT_NEAR(result.Y, 0.0, 1E-10);
}

TEST(GeometryUtilsTest, BrentFunctionValue_NoRoot) {
    auto f = [](double x) { return x * x + 4; }; // Function f(x) = x^2 + 4 (no real roots)
    Point2D result = GeometryUtils::BrentFunctionValue(0.0, 5.0, 0.0, 1.0, f, nullptr);
    EXPECT_TRUE(result.IsNaN());
}


// Test case for successful conversions
TEST(GeometryUtils, TryParseAsDouble_Success) {
    double value;

    EXPECT_TRUE(GeometryUtils::TryParseAsDouble("123.456", value));
    EXPECT_DOUBLE_EQ(value, 123.456);

    EXPECT_TRUE(GeometryUtils::TryParseAsDouble("   123.456   ", value));
    EXPECT_DOUBLE_EQ(value, 123.456);

    EXPECT_TRUE(GeometryUtils::TryParseAsDouble("INF", value));
    EXPECT_EQ(value, std::numeric_limits<double>::infinity());

    EXPECT_TRUE(GeometryUtils::TryParseAsDouble("   -INF   ", value));
    EXPECT_EQ(value, -std::numeric_limits<double>::infinity());
}

// Test case for failed conversions
TEST(GeometryUtils, TryParseAsDouble_Failure) {
    double value;

    EXPECT_FALSE(GeometryUtils::TryParseAsDouble("", value));
    EXPECT_TRUE(std::isnan(value));

    EXPECT_FALSE(GeometryUtils::TryParseAsDouble("   ", value));
    EXPECT_TRUE(std::isnan(value));

    EXPECT_FALSE(GeometryUtils::TryParseAsDouble("123.45abc", value));
    EXPECT_TRUE(std::isnan(value));

    EXPECT_FALSE(GeometryUtils::TryParseAsDouble("abc123.45", value));
    EXPECT_TRUE(std::isnan(value));

    EXPECT_FALSE(GeometryUtils::TryParseAsDouble("..123", value));
    EXPECT_TRUE(std::isnan(value));
}

// Test edge cases
TEST(GeometryUtils, TryParseAsDouble_EdgeCases) {
    double value;

    EXPECT_TRUE(GeometryUtils::TryParseAsDouble("0", value));
    EXPECT_DOUBLE_EQ(value, 0.0);

    EXPECT_TRUE(GeometryUtils::TryParseAsDouble("-0", value));
    EXPECT_DOUBLE_EQ(value, -0.0);

    EXPECT_TRUE(GeometryUtils::TryParseAsDouble("1e10", value));
    EXPECT_DOUBLE_EQ(value, 1e10);

    EXPECT_TRUE(GeometryUtils::TryParseAsDouble("-1e-10", value));
    EXPECT_DOUBLE_EQ(value, -1e-10);

    EXPECT_TRUE(GeometryUtils::TryParseAsDouble("1.7976931348623157e308", value));
    EXPECT_DOUBLE_EQ(value, std::numeric_limits<double>::max());

    EXPECT_TRUE(GeometryUtils::TryParseAsDouble("2.2250738585072014e-308", value));
    EXPECT_DOUBLE_EQ(value, std::numeric_limits<double>::min());
}

