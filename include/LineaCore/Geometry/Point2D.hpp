#ifndef LINEACORE_GEOMETRY_POINT2D_HPP
#define LINEACORE_GEOMETRY_POINT2D_HPP

#include "Vector2D.hpp"
#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>

namespace LineaCore::Geometry {

class Point2D {
public:
    // Membres publics pour X et Y
    double X;
    double Y;

    // Constructeurs
    Point2D(double x = 0.0, double y = 0.0);

    // Point NaN statique
    static Point2D NaN();

    // Propriétés
    bool IsNaN() const;

    // Opérateurs de comparaison
    bool operator==(const Point2D& p) const;
    bool operator!=(const Point2D& p) const;

    // Opérateurs mathématiques
    Vector2D operator-(const Point2D& p) const;        // Soustraction entre deux points
    Point2D operator+(const Vector2D& v) const;        // Addition avec un vecteur
    Point2D operator-(const Vector2D& v) const;        // Soustraction avec un vecteur
    Point2D operator-() const;                         // Négation

    // Opérations internes
    void TranslateBy(const Vector2D& v);
    static Point2D MidPoint(const Point2D& p, const Point2D& q);

    // Rotation par un vecteur
    Point2D RotatedBy(const Vector2D& rotVect) const;

    // Conversion explicite en Vector2D
    explicit operator Vector2D() const;

    // Représentation sous forme de chaîne
    std::string ToString() const;
};

} // namespace LineaCore::Geometry

#endif // LINEACORE_GEOMETRY_POINT2D_HPP
