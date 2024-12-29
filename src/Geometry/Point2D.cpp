// Point2D.cpp
#include "LineaCore/Geometry/Point2D.hpp"
#include <cmath>
#include <stdexcept>
#include <string>
#include <sstream>


namespace LineaCore::Geometry {

// Constructeurs
Point2D::Point2D(double x, double y) : X(x), Y(y) {}

// Retourne une instance de Point2D avec des valeurs NaN
Point2D Point2D::NaN() {
    return Point2D(std::nan(""), std::nan(""));
}

// Vérifie si le point est NaN
bool Point2D::IsNaN() const {
    return std::isnan(X) || std::isnan(Y);
}

// Méthodes statiques
// Retourne le milieu entre deux points
Point2D Point2D::MidPoint(const Point2D& p, const Point2D& q) {
    return Point2D((p.X + q.X) / 2.0, (p.Y + q.Y) / 2.0);
}

// Effectue une translation du point selon un vecteur donné
void Point2D::TranslateBy(const Vector2D& v) {
    X += v.X;
    Y += v.Y;
}

// Effectue une rotation autour de l'origine en utilisant un vecteur de rotation
Point2D Point2D::RotatedBy(const Vector2D& rotVect) const {
    return Point2D(X * rotVect.X - Y * rotVect.Y, Y * rotVect.X + X * rotVect.Y);
}

// Opérateurs
// Soustraction entre deux points, retourne un vecteur
Vector2D Point2D::operator-(const Point2D& p) const {
    return Vector2D(X - p.X, Y - p.Y);
}

// Addition d'un point et d'un vecteur, retourne un nouveau point
Point2D Point2D::operator+(const Vector2D& v) const {
    return Point2D(X + v.X, Y + v.Y);
}

// Soustraction d'un vecteur à un point, retourne un nouveau point
Point2D Point2D::operator-(const Vector2D& v) const {
    return Point2D(X - v.X, Y - v.Y);
}

// Négation d'un point (inverse les coordonnées)
Point2D Point2D::operator-() const {
    return Point2D(-X, -Y);
}

// Vérifie l'égalité entre deux points
bool Point2D::operator==(const Point2D& p) const {
    return X == p.X && Y == p.Y;
}

// Vérifie l'inégalité entre deux points
bool Point2D::operator!=(const Point2D& p) const {
    return !(*this == p);
}

// Conversion explicite en Vector2D
Point2D::operator Vector2D() const {
    return Vector2D(X, Y);
}

// Conversion en chaîne de caractères
std::string Point2D::ToString() const {
    std::ostringstream oss;
    oss << "(" << X << ", " << Y << ")";
    return oss.str();
}

} // namespace LineaCore::Geometry
