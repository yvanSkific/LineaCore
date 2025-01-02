// Point2D.hpp
#pragma once

#include <string>

namespace LineaCore::Geometry {

class Vector2D; // Déclaration anticipée

/**
 * @class Point2D
 * @brief Représente un point dans un espace 2D avec des coordonnées X et Y.
 * 
 * La classe Point2D fournit des méthodes pour manipuler et effectuer des opérations sur des points 2D,
 * y compris la vérification de NaN, les opérations mathématiques et la conversion en vecteur 2D.
 */
class Point2D {
public:
    double X; ///< Coordonnée X du point
    double Y; ///< Coordonnée Y du point

    /**
     * @brief Constructeur par défaut qui initialise les coordonnées du point à (0, 0).
     * @param x Coordonnée X du point (par défaut 0.0).
     * @param y Coordonnée Y du point (par défaut 0.0).
     */
    Point2D(double x = 0.0, double y = 0.0);

    /**
     * @brief Retourne un point représentant une valeur NaN (Not a Number).
     * @return Un point avec des coordonnées NaN.
     */
    static Point2D NaN();

    /**
     * @brief Vérifie si le point est NaN.
     * @return true si le point est NaN, false sinon.
     */
    bool IsNaN() const;

    /**
     * @brief Vérifie l'égalité entre deux points.
     * @param p Le point à comparer.
     * @return true si les points ont les mêmes coordonnées, false sinon.
     */
    bool operator==(const Point2D& p) const;

    /**
     * @brief Vérifie l'inégalité entre deux points.
     * @param p Le point à comparer.
     * @return true si les points n'ont pas les mêmes coordonnées, false sinon.
     */
    bool operator!=(const Point2D& p) const;

    /**
     * @brief Soustraction entre deux points.
     * @param p Le point à soustraire.
     * @return Un vecteur représentant la différence entre les deux points.
     */
    Vector2D operator-(const Point2D& p) const;

    /**
     * @brief Addition avec un vecteur.
     * @param v Le vecteur à ajouter.
     * @return Un nouveau point résultant de l'addition du vecteur au point.
     */
    Point2D operator+(const Vector2D& v) const;

    /**
     * @brief Soustraction avec un vecteur.
     * @param v Le vecteur à soustraire.
     * @return Un nouveau point résultant de la soustraction du vecteur au point.
     */
    Point2D operator-(const Vector2D& v) const;

    /**
     * @brief Négation du point.
     * @return Un nouveau point avec des coordonnées négatives.
     */
    Point2D operator-() const;

    /**
     * @brief Translate le point par un vecteur donné.
     * @param v Le vecteur de translation.
     */
    void TranslateBy(const Vector2D& v);

    /**
     * @brief Calcule le point milieu entre deux points.
     * @param p Le premier point.
     * @param q Le deuxième point.
     * @return Le point milieu entre p et q.
     */
    static Point2D MidPoint(const Point2D& p, const Point2D& q);

    /**
     * @brief Effectue une rotation du point par un vecteur de rotation donné.
     * @param rotVect Le vecteur de rotation.
     * @return Un nouveau point résultant de la rotation.
     */
    Point2D RotatedBy(const Vector2D& rotVect) const;

    /**
     * @brief Conversion explicite du point en vecteur 2D.
     * @return Un vecteur 2D avec les mêmes coordonnées que le point.
     */
    explicit operator Vector2D() const;

    /**
     * @brief Convertit le point en une chaîne de caractères.
     * @return Une chaîne de caractères représentant le point sous la forme "(X, Y)".
     */
    std::string ToString() const;
};

} // namespace LineaCore::Geometry

