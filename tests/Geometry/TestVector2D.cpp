#include "../../include/LineaCore/Geometry/Vector2D.hpp"
#include <cassert>
#include <iostream>

int main() {
    using namespace LineaCore::Geometry;

    // Test du constructeur par défaut
    Vector2D v1;
    assert(v1.X == 0 && v1.Y == 0);

    // Test du constructeur avec coordonnées
    Vector2D v2(3.0, 4.0);
    assert(v2.Length() == 5.0); // Longueur doit être 5

    // Test de la normalisation
    Vector2D v3 = v2.Normalized();
    assert(v3.Length() == 1.0); // Longueur doit être 1

    // Test de l'addition
    Vector2D v4 = v2 + Vector2D(1.0, 1.0);
    assert(v4.X == 4.0 && v4.Y == 5.0); // Vérifie les coordonnées

    // Test de la multiplication scalaire
    Vector2D v5 = v2 * 2.0;
    assert(v5.X == 6.0 && v5.Y == 8.0); // Vérifie les coordonnées

    // Test de la méthode ToString
    assert(v2.ToString() == "(3, 4)");

    // Test de la normalisation d'un vecteur nul
    try {
        Vector2D v6(0.0, 0.0);
        v6.Normalize(); // Devrait lancer une exception
        assert(false); // Si on arrive ici, l'exception n'a pas été lancée
    } catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Cannot normalize a zero-length vector.");
    }

    std::cout << "Tous les tests ont réussi !" << std::endl;
    return 0;
}