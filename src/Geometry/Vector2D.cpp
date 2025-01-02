// Vector2D.cpp
#include "LineaCore/Geometry/Vector2D.hpp"
#include "LineaCore/Geometry/Point2D.hpp"
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <numbers>

namespace LineaCore::Geometry {

// Constructeurs
// Initialisation avec les coordonnées X et Y
Vector2D::Vector2D(double x, double y) : X(x), Y(y) {}

// Constructeur par défaut initialisant à (0, 0)
Vector2D::Vector2D() : Vector2D(0.0, 0.0) {}

// Crée un vecteur à partir d'un angle en radians
Vector2D::Vector2D(double angle) : Vector2D(std::cos(angle), std::sin(angle)) {}

// Méthodes statiques
// Crée un vecteur à partir d'une représentation polaire (rayon et angle)
Vector2D Vector2D::Polar(double r, double angle) {
    return Vector2D(r * std::cos(angle), r * std::sin(angle));
}

// Propriétés
// Retourne la norme (longueur) du vecteur en utilisant std::hypot pour une précision accrue
double Vector2D::Length() const {
    return std::hypot(X, Y);
}

// Normalise le vecteur pour qu'il ait une longueur de 1
void Vector2D::Normalize() {
    double norm = Length();
    if (norm == 0.0) {
        throw std::runtime_error("Cannot normalize a zero-length vector.");
    }
    X /= norm;
    Y /= norm;
}

// Retourne une copie normalisée du vecteur
Vector2D Vector2D::Normalized() const {
    double norm = Length();
    if (norm == 0.0) {
        throw std::runtime_error("Cannot normalize a zero-length vector.");
    }
    return Vector2D(X / norm, Y / norm);
}

// Retourne une copie du vecteur après une rotation de 90° dans le sens antihoraire
Vector2D Vector2D::Rotated90CounterClockWise() const {
    return Vector2D(-Y, X);
}

// Retourne une copie du vecteur après une rotation de 90° dans le sens horaire
Vector2D Vector2D::Rotated90ClockWise() const {
    return Vector2D(Y, -X);
}

// Calcule l'angle du vecteur par rapport à l'axe X, dans [0, 2π)
double Vector2D::Angle02Pi() const {
    double angle = std::atan2(Y, X);
    return angle < 0 ? angle + 2 * std::numbers::pi : angle;
}

// Calcule l'angle du vecteur par rapport à l'axe X, dans [-π, π]
double Vector2D::AngleMinusPiPi() const {
    return std::atan2(Y, X);
}

// Projection dans une référence vectorielle donnée
Vector2D Vector2D::InVectorialReference(const Vector2D& refVect) const {
    return Vector2D(X * refVect.X + Y * refVect.Y, Y * refVect.X - X * refVect.Y);
}

// Opérateurs
// Produit scalaire entre deux vecteurs
double Vector2D::operator*(const Vector2D& v) const {
    return X * v.X + Y * v.Y;
}

// Produit vectoriel en 2D, qui donne une valeur scalaire
double Vector2D::operator/(const Vector2D& v) const {
    return X * v.Y - Y * v.X;
}

// Addition de deux vecteurs
Vector2D Vector2D::operator+(const Vector2D& v) const {
    return Vector2D(X + v.X, Y + v.Y);
}

// Soustraction de deux vecteurs
Vector2D Vector2D::operator-(const Vector2D& v) const {
    return Vector2D(X - v.X, Y - v.Y);
}

// Multiplication par un scalaire
Vector2D Vector2D::operator*(double d) const {
    return Vector2D(X * d, Y * d);
}

// Division par un scalaire
Vector2D Vector2D::operator/(double d) const {
    if (d == 0.0) {
        throw std::runtime_error("Division by zero.");
    }
    return Vector2D(X / d, Y / d);
}

// Multiplication par un scalaire, fonction amie pour prendre en charge l'ordre inversé
Vector2D operator*(double d, const Vector2D& v) {
    return Vector2D(v.X * d, v.Y * d);
}

// Vérifie l'égalité entre deux vecteurs
bool Vector2D::operator==(const Vector2D& v) const {
    return X == v.X && Y == v.Y;
}

// Vérifie l'inégalité entre deux vecteurs
bool Vector2D::operator!=(const Vector2D& v) const {
    return !(*this == v);
}

// Conversion explicite en Point2D
Vector2D::operator LineaCore::Geometry::Point2D() const {
    return Point2D(X, Y);
}

// Méthodes utilitaires
// Retourne une représentation sous forme de chaîne de caractères
std::string Vector2D::ToString() const {
    std::ostringstream oss;
    oss << "(" << X << ", " << Y << ")";
    return oss.str();
}

} // namespace LineaCore::Geometry
