#include <gtest/gtest.h>
#include "LineaCore/Geometry/Point2D.hpp"
#include "LineaCore/Geometry/Vector2D.hpp"

using namespace LineaCore::Geometry;

TEST(Point2DTest, DefaultConstructor) {
    Point2D p;
    EXPECT_EQ(p.X, 0.0);
    EXPECT_EQ(p.Y, 0.0);
}

TEST(Point2DTest, ParameterizedConstructor) {
    Point2D p(3.0, 4.0);
    EXPECT_EQ(p.X, 3.0);
    EXPECT_EQ(p.Y, 4.0);
}

TEST(Point2DTest, NaN) {
    Point2D p = Point2D::NaN();
    EXPECT_TRUE(p.IsNaN());
}

TEST(Point2DTest, EqualityOperator) {
    Point2D p1(1.0, 2.0);
    Point2D p2(1.0, 2.0);
    EXPECT_TRUE(p1 == p2);
}

TEST(Point2DTest, InequalityOperator) {
    Point2D p1(1.0, 2.0);
    Point2D p2(3.0, 4.0);
    EXPECT_TRUE(p1 != p2);
}

TEST(Point2DTest, ToString) {
    Point2D p(1.0, 2.0);
    EXPECT_EQ(p.ToString(), "(1, 2)");
}

TEST(Point2DTest, ConversionToVector2D) {
    Point2D p(1.0, 2.0);
    Vector2D v = static_cast<Vector2D>(p);
    EXPECT_EQ(v.X, 1.0);
    EXPECT_EQ(v.Y, 2.0);
}