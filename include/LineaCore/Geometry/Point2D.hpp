// Point2D.hpp
#pragma once

#include "Vector2D.hpp"
#include <string>

/**
 * @class Point2D
 * @brief Représente un point dans un espace 2D avec des coordonnées X et Y.
 * 
 * La classe Point2D fournit des méthodes pour manipuler et effectuer des opérations sur des points 2D,
 * y compris la vérification de NaN, les opérations mathématiques et la conversion en vecteur 2D.
 * 
 * @namespace LineaCore::Geometry
 * 
 * @public
 * @member double X
 * @brief Coordonnée X du point.
 * 
 * @public
 * @member double Y
 * @brief Coordonnée Y du point.
 * 
 * @public
 * @fn Point2D(double x = 0.0, double y = 0.0)
 * @brief Constructeur par défaut qui initialise les coordonnées du point à (0, 0).
 * @param x Coordonnée X du point (par défaut 0.0).
 * @param y Coordonnée Y du point (par défaut 0.0).
 * 
 * @public
 * @fn static Point2D NaN()
 * @brief Retourne un point représentant une valeur NaN (Not a Number).
 * @return Un point avec des coordonnées NaN.
 * 
 * @public
 * @fn bool IsNaN() const
 * @brief Vérifie si le point est NaN.
 * @return true si le point est NaN, false sinon.
 * 
 * @public
 * @fn bool operator==(const Point2D& p) const
 * @brief Vérifie l'égalité entre deux points.
 * @param p Le point à comparer.
 * @return true si les points ont les mêmes coordonnées, false sinon.
 * 
 * @public
 * @fn bool operator!=(const Point2D& p) const
 * @brief Vérifie l'inégalité entre deux points.
 * @param p Le point à comparer.
 * @return true si les points n'ont pas les mêmes coordonnées, false sinon.
 * 
 * @public
 * @fn Vector2D operator-(const Point2D& p) const
 * @brief Soustraction entre deux points.
 * @param p Le point à soustraire.
 * @return Un vecteur représentant la différence entre les deux points.
 * 
 * @public
 * @fn Point2D operator+(const Vector2D& v) const
 * @brief Addition avec un vecteur.
 * @param v Le vecteur à ajouter.
 * @return Un nouveau point résultant de l'addition du vecteur au point.
 * 
 * @public
 * @fn Point2D operator-(const Vector2D& v) const
 * @brief Soustraction avec un vecteur.
 * @param v Le vecteur à soustraire.
 * @return Un nouveau point résultant de la soustraction du vecteur au point.
 * 
 * @public
 * @fn Point2D operator-() const
 * @brief Négation du point.
 * @return Un nouveau point avec des coordonnées négatives.
 * 
 * @public
 * @fn void TranslateBy(const Vector2D& v)
 * @brief Translate le point par un vecteur donné.
 * @param v Le vecteur de translation.
 * 
 * @public
 * @fn static Point2D MidPoint(const Point2D& p, const Point2D& q)
 * @brief Calcule le point milieu entre deux points.
 * @param p Le premier point.
 * @param q Le deuxième point.
 * @return Le point milieu entre p et q.
 * 
 * @public
 * @fn Point2D RotatedBy(const Vector2D& rotVect) const
 * @brief Effectue une rotation du point par un vecteur de rotation donné.
 * @param rotVect Le vecteur de rotation.
 * @return Un nouveau point résultant de la rotation.
 * 
 * @public
 * @fn explicit operator Vector2D() const
 * @brief Conversion explicite du point en vecteur 2D.
 * @return Un vecteur 2D avec les mêmes coordonnées que le point.
 * 
 * @public
 * @fn std::string ToString() const
 * @brief Convertit le point en une chaîne de caractères.
 * @return Une chaîne de caractères représentant le point sous la forme "(X, Y)".
 */
namespace LineaCore::Geometry {

class Point2D {
public:
    // Membres publics pour X et Y
    double X;
    double Y;

    // Constructeurs
    /**
     * @brief Constructeur par défaut qui initialise les coordonnées du point à (0, 0).
     * @param x Coordonnée X du point (par défaut 0.0).
     * @param y Coordonnée Y du point (par défaut 0.0).
     */
    Point2D(double x = 0.0, double y = 0.0);

    // Point NaN statique
    /**
     * @brief Retourne un point représentant une valeur NaN (Not a Number).
     * @return Un point avec des coordonnées NaN.
     */
    static Point2D NaN();

    // Propriétés
    /**
     * @brief Vérifie si le point est NaN.
     * @return true si le point est NaN, false sinon.
     */
    bool IsNaN() const;

    // Opérateurs de comparaison
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
    /**
     * @brief Conversion explicite du point en vecteur 2D.
     * @return Un vecteur 2D avec les mêmes coordonnées que le point.
     */
    explicit operator Vector2D() const;

    // Représentation sous forme de chaîne
    /**
     * @brief Convertit le point en une chaîne de caractères.
     * @return Une chaîne de caractères représentant le point sous la forme "(X, Y)".
     */
    std::string ToString() const;
};

} // namespace LineaCore::Geometry

