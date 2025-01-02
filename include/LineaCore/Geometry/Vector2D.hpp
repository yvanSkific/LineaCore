// Vector2D.hpp
#pragma once

#include <string>

namespace LineaCore::Geometry {

class Point2D; // Déclaration anticipée

/**
 * @class Vector2D
 * @brief Classe représentant un vecteur 2D.
 */
class Vector2D {
public:
    // Membres publics pour un accès direct aux coordonnées
    double X; ///< Coordonnée X du vecteur
    double Y; ///< Coordonnée Y du vecteur

    /**
     * @brief Constructeur par défaut, initialise à (0, 0).
     */
    Vector2D();

    /**
     * @brief Initialise avec des coordonnées X et Y.
     * @param x Coordonnée X.
     * @param y Coordonnée Y.
     */
    Vector2D(double x, double y);

    /**
     * @brief Initialise avec un angle en radians.
     * @param angle Angle en radians.
     */
    explicit Vector2D(double angle);

    /**
     * @brief Crée un vecteur à partir de coordonnées polaires.
     * @param r Rayon.
     * @param angle Angle en radians.
     * @return Vecteur 2D correspondant.
     */
    static Vector2D Polar(double r, double angle);

    /**
     * @brief Retourne la longueur du vecteur.
     * @return Longueur du vecteur.
     */
    double Length() const;

    /**
     * @brief Normalise le vecteur (longueur = 1).
     */
    void Normalize();

    /**
     * @brief Retourne une copie normalisée du vecteur.
     * @return Vecteur normalisé.
     */
    Vector2D Normalized() const;

    /**
     * @brief Retourne une copie après une rotation de 90° antihoraire.
     * @return Vecteur après rotation.
     */
    Vector2D Rotated90CounterClockWise() const;

    /**
     * @brief Retourne une copie après une rotation de 90° horaire.
     * @return Vecteur après rotation.
     */
    Vector2D Rotated90ClockWise() const;

    /**
     * @brief Retourne l'angle dans [0, 2π).
     * @return Angle en radians.
     */
    double Angle02Pi() const;

    /**
     * @brief Retourne l'angle dans [-π, π].
     * @return Angle en radians.
     */
    double AngleMinusPiPi() const;

    /**
     * @brief Projection dans une référence vectorielle donnée.
     * @param refVect Vecteur de référence.
     * @return Vecteur projeté.
     */
    Vector2D InVectorialReference(const Vector2D& refVect) const;

    /**
     * @brief Produit scalaire.
     * @param v Vecteur à multiplier.
     * @return Produit scalaire.
     */
    double operator*(const Vector2D& v) const;

    /**
     * @brief Produit vectoriel (scalaire en 2D).
     * @param v Vecteur à multiplier.
     * @return Produit vectoriel.
     */
    double operator/(const Vector2D& v) const;

    /**
     * @brief Addition de deux vecteurs.
     * @param v Vecteur à ajouter.
     * @return Vecteur résultant.
     */
    Vector2D operator+(const Vector2D& v) const;

    /**
     * @brief Soustraction de deux vecteurs.
     * @param v Vecteur à soustraire.
     * @return Vecteur résultant.
     */
    Vector2D operator-(const Vector2D& v) const;

    /**
     * @brief Multiplication par un scalaire.
     * @param d Scalaire.
     * @return Vecteur résultant.
     */
    Vector2D operator*(double d) const;

    /**
     * @brief Division par un scalaire.
     * @param d Scalaire.
     * @return Vecteur résultant.
     * @throws std::runtime_error Si le scalaire est zéro.
     */
    Vector2D operator/(double d) const;

    /**
     * @brief Vérifie l'égalité entre deux vecteurs.
     * @param v Vecteur à comparer.
     * @return true si les vecteurs sont égaux, false sinon.
     */
    bool operator==(const Vector2D& v) const;

    /**
     * @brief Vérifie l'inégalité entre deux vecteurs.
     * @param v Vecteur à comparer.
     * @return true si les vecteurs sont différents, false sinon.
     */
    bool operator!=(const Vector2D& v) const;

    /**
     * @brief Conversion explicite en Point2D.
     * @return Point2D correspondant.
     */
    explicit operator LineaCore::Geometry::Point2D() const;

    /**
     * @brief Retourne une représentation sous forme de chaîne de caractères.
     * @return Représentation sous forme de chaîne.
     */
    std::string ToString() const;

    // Déclaration friend pour prendre en charge la multiplication scalaire dans les deux ordres
    friend Vector2D operator*(double d, const Vector2D& v);
};

} // namespace LineaCore::Geometry

