// GeometryUtils.hpp
#pragma once

#include "Point2D.hpp"
#include <functional>

namespace LineaCore::Geometry {

class GeometryUtils {

private:

    static const double Epsilon; // Tolérance pour la convergence

    // Fonction privée pour l’interpolation quadratique inverse
    double inverseQuadraticInterpolation(double a, double fa, double b, double fb, double c, double fc);

public:

    /**
     * @brief Recherche d'une racine f(x) = yc d'une fonction f sur un intervalle.
     *
     * Cette méthode utilise une combinaison de la méthode de Brent (interpolation
     * inverse quadratique et méthode de la sécante) et de la bissection pour
     * rechercher efficacement une racine dans un intervalle donné.
     * 
     * @param x0 Origine de l'intervalle de recherche.
     * @param dx Étendue de l'intervalle de recherche (peut être infini pour des
     *          recherches sans borne explicite).
     * @param yc Valeur cible pour laquelle la racine est recherchée (f(x) = yc).
     * @param xRef Échelle caractéristique pour définir la précision relative de la
     *            recherche. La convergence s'arrête lorsque |b-a| < xRef * Epsilon.
     * @param f Fonction à analyser, fournie comme délégué std::function<double(double)>.
     * @param byExcess Si non nul :
     *                 - true : retourne la racine par excès (valeur supérieure).
     *                 - false : retourne la racine par défaut (valeur inférieure).
     *                 - nullptr : retourne simplement la meilleure estimation de la racine.
     * @return Un Point2D contenant :
     *         - X : la racine trouvée ou NaN si aucune n'est trouvée.
     *         - Y : la valeur de f(x) en ce point (ou NaN en cas d'échec).
     *
     * @note La méthode traite les cas d'infini dans dx en explorant dynamiquement
     *       l'intervalle jusqu'à trouver un changement de signe dans f(x).
     * @note Si les signes de f(x0) et f(x0+dx) sont identiques, aucune racine
     *       n'est recherchée.
     * @warning En cas de convergence lente ou de détection de stagnation (trois
     *          itérations consécutives avec la même amplitude), la méthode renvoie
     *          la meilleure estimation trouvée.
     */
    static Point2D BrentFunctionValue(double x0, double dx, double yc, double xRef, std::function<double(double)> f, bool* byExcess); 

};

} // namespace LineaCore::Geometry