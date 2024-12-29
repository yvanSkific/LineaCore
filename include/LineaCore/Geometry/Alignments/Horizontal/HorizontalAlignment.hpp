// HorizontalAlignment.hpp
#pragma once

#include "LineaCore/Geometry/Point2D.hpp"
#include "LineaCore/Geometry/Vector2D.hpp"
#include <vector>
#include <string>
#include <stdexcept>

namespace LineaCore::Geometry::Alignments::Horizontal {

// Classe de base HorizontalAlignment
class HorizontalAlignment {
public:
    enum class H_Type {
        Straight,
        Curved,
        Transition
    };

protected:
    Point2D startingPoint;
    Point2D endingPoint;
    Vector2D startingNormal;
    Vector2D endingNormal;

    void SetExtremities();

public:
    virtual ~HorizontalAlignment() = default;

    virtual H_Type Type() const = 0;
    virtual double Length() const = 0;

    virtual Point2D Point(double s) const = 0;
    virtual Vector2D Normal(double s) const = 0;
    virtual double Curvature(double s) const = 0;
    virtual std::vector<Point2D> Points(double maxThrow) const = 0;


    // Accesseurs pour les points et vecteurs calculés
    const Point2D& getStartingPoint() const { return startingPoint; }
    const Point2D& getEndingPoint() const { return endingPoint; }
    const Vector2D& getStartingNormal() const { return startingNormal; }
    const Vector2D& getEndingNormal() const { return endingNormal; }
};

} // namespace LineaCore::Geometry::Alignments::Horizontal 

