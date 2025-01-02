#include <gtest/gtest.h>
#include "LineaCore/Geometry/Vector2D.hpp"
#include <numbers>
#include <cmath>

using namespace LineaCore::Geometry;

TEST(Vector2DTest, DefaultConstructor) {
    Vector2D v;
    EXPECT_EQ(v.X, 0.0);
    EXPECT_EQ(v.Y, 0.0);
}

TEST(Vector2DTest, ParameterizedConstructor) {
    Vector2D v(3.0, 4.0);
    EXPECT_EQ(v.X, 3.0);
    EXPECT_EQ(v.Y, 4.0);
}

TEST(Vector2DTest, AngleConstructor) {
    Vector2D v(std::numbers::pi / 4);
    EXPECT_NEAR(v.X, std::sqrt(2) / 2, 1e-9);
    EXPECT_NEAR(v.Y, std::sqrt(2) / 2, 1e-9);
}

TEST(Vector2DTest, Polar) {
    Vector2D v = Vector2D::Polar(1.0, std::numbers::pi / 4);
    EXPECT_NEAR(v.X, std::sqrt(2) / 2, 1e-9);
    EXPECT_NEAR(v.Y, std::sqrt(2) / 2, 1e-9);
}

TEST(Vector2DTest, Length) {
    Vector2D v(3.0, 4.0);
    EXPECT_EQ(v.Length(), 5.0);
}

TEST(Vector2DTest, Normalize) {
    Vector2D v(3.0, 4.0);
    v.Normalize();
    EXPECT_NEAR(v.Length(), 1.0, 1e-9);
    EXPECT_NEAR(v.X, 3.0 / 5.0, 1e-9);
    EXPECT_NEAR(v.Y, 4.0 / 5.0, 1e-9);
}