// GeometryUtils.cpp
#include "LineaCore/Geometry/GeometryUtils.hpp"
#include <cmath>
#include <limits>
#include <algorithm> // for std::swap
#include "GeometryUtils.hpp"

namespace LineaCore::Geometry {

const double GeometryUtils::Epsilon = 1E-10; // Tolérance pour la convergence

double GeometryUtils::inverseQuadraticInterpolation(double a, double fa, double b, double fb, double c, double fc)
{
    return a * fb * fc / ((fa - fb) * (fa - fc)) +
           b * fa * fc / ((fb - fa) * (fb - fc)) +
           c * fa * fb / ((fc - fa) * (fc - fb));
}

Point2D GeometryUtils::BrentFunctionValue(double x0, double dx, double yc, double xRef, std::function<double(double)> f, bool *byExcess)
{
    double a = x0;
    double fa = f(a) - yc;
    double b;
    double fb;

    bool deltaTooLarge = false;

    // Gestion des cas où dx est infini
    if (std::isinf(dx)) {
        double delta = xRef * std::copysign(1.0, dx); // Initialisation de delta selon la direction de dx
        do {
            b = a + delta;
            fb = f(b) - yc;
            delta *= 2.0; // Augmentation exponentielle de delta

            // Vérification : delta est-il trop grand par rapport à la tolérance ?
            deltaTooLarge = xRef / std::fabs(delta * 100) < Epsilon;
            if (deltaTooLarge) {
                return Point2D::NaN();
            }
        } while (!(fa * fb <= 0.0)); // Continue jusqu'à ce qu'un changement de signe soit détecté
    } else {
        b = a + dx;
        fb = f(b) - yc;
    }

    // Vérification si les signes de fa et fb sont opposés
    if (fa * fb >= 0.0) {
        if (fa == 0.0) {
            fa = f(a);
            return Point2D(a, fa + yc);
        } else if (fb == 0.0) {
            return Point2D(b, fb + yc);
        } else {
            return Point2D::NaN();
        }
    }

    double Epsilon_xRef = xRef * Epsilon;
    double s;
    double fs;

    // Interchange si nécessaire
    if (std::fabs(fa) < std::fabs(fb)) {
        std::swap(a, b);
        std::swap(fa, fb);
    }

    double c = a;
    double fc = fa;
    double d = 0.0;
    double previousGap = std::numeric_limits<double>::infinity();
    int identicalIterationsCount = 0;

    bool flag = true;

    // Boucle principale de la méthode de Brent
    while (!(fb == 0.0 || previousGap < Epsilon_xRef || identicalIterationsCount > 3)) {
        // Calcul de s par interpolation quadratique inverse ou méthode de la secante
        if (fa != fc && fb != fc) {
            s = a * fb * fc / ((fa - fb) * (fa - fc)) + b * fa * fc / ((fb - fa) * (fb - fc)) + c * fa * fb / ((fc - fa) * (fc - fb));
        } else {
            s = b - fb * (b - a) / (fb - fa);
        }

        // Vérification des bornes et ajustement de s
        if (s < (3.0 * a + b) / 4.0 || s > b || (flag && std::fabs(s - b) >= std::fabs(b - c) / 2.0) || (!flag && std::fabs(s - b) >= std::fabs(c - d) / 2)) {
            s = (a + b) / 2.0;
            flag = true;
        } else {
            flag = false;
        }

        fs = f(s) - yc;
        d = c;
        c = b;
        fc = fb;

        if (fa * fs < 0.0) {
            b = s;
            fb = fs;
        } else {
            a = s;
            fa = fs;
        }

        if (std::fabs(fa) < std::fabs(fb)) {
            std::swap(a, b);
            std::swap(fa, fb);
        }

        if (previousGap != std::fabs(b - a)) {
            previousGap = std::fabs(b - a);
            identicalIterationsCount = 0;
        } else {
            identicalIterationsCount++;
        }
    }

    // Retourne le résultat en fonction de byExcess
    if (byExcess == nullptr) {
        fb = f(b);
        return Point2D(b, fb + yc);
    } else {
        if (*byExcess) {
            if (fa > fb) {
                fa = f(a);
                return Point2D(a, fa + yc);
            } else {
                fb = f(b);
                return Point2D(b, fb + yc);
            }
        } else {
            if (fa < fb) {
                fa = f(a);
                return Point2D(a, fa + yc);
            } else {
                fb = f(b);
                return Point2D(b, fb + yc);
            }
        }
    }
}

} // namespace LineaCore::Geometry