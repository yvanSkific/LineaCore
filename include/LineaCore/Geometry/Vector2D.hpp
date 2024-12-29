// Vector2D.hpp
#pragma once
#include <string>

namespace LineaCore::Geometry {

// Classe représentant un vecteur 2D
class Vector2D {
public:
    // Membres publics pour un accès direct aux coordonnées
    double X;
    double Y;

    // Constructeurs
    Vector2D();                                 // Par défaut, initialise à (0, 0)
    Vector2D(double x, double y);             // Initialise avec des coordonnées X et Y
    explicit Vector2D(double angle);          // Initialise avec un angle en radians

    // Méthodes statiques
    static Vector2D Polar(double r, double angle); // Crée un vecteur à partir de coordonnées polaires

    // Propriétés
    double Length() const;                // Retourne la longueur du vecteur
    void Normalize();                     // Normalise le vecteur (longueur = 1)
    Vector2D Normalized() const;          // Retourne une copie normalisée
    Vector2D Rotated90CounterClockWise() const; // Retourne une copie après une rotation de 90° antihoraire
    Vector2D Rotated90ClockWise() const;        // Retourne une copie après une rotation de 90° horaire
    double Angle02Pi() const;             // Retourne l'angle dans [0, 2π)
    double AngleMinusPiPi() const;        // Retourne l'angle dans [-π, π]

    // Opérateurs
    double operator*(const Vector2D& v) const; // Produit scalaire
    double operator/(const Vector2D& v) const; // Produit vectoriel (scalaire en 2D)
    Vector2D operator+(const Vector2D& v) const; // Addition
    Vector2D operator-(const Vector2D& v) const; // Soustraction
    Vector2D operator*(double d) const;        // Multiplication par un scalaire
    Vector2D operator/(double d) const;        // Division par un scalaire

    bool operator==(const Vector2D& v) const;  // Vérifie l'égalité
    bool operator!=(const Vector2D& v) const;  // Vérifie l'inégalité

    // Méthodes utilitaires
    std::string ToString() const;              // Représentation sous forme de chaîne

    // Déclaration friend pour prendre en charge la multiplication scalaire dans les deux ordres
    friend Vector2D operator*(double d, const Vector2D& v);
};

} // namespace LineaCore::Geometry

