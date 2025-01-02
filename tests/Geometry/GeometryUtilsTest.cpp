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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
