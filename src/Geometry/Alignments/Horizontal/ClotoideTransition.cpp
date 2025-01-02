// ClotoideTransition.cpp

#include "LineaCore/Geometry/Alignments/Horizontal/ClotoideTransition.hpp"
#include "ClotoideTransition.hpp"

namespace LineaCore::Geometry::Alignments::Horizontal {

bool ClotoideTransition::TryFromVectorAndCurvatures(const Point2D& startingPoint, const Vector2D& chordVector, 
                                                    double startingCurvature, double endingCurvature, 
                                                    ClotoideTransition& clotoideArc) {
    double c = chordVector.Length();    //longueur de la Corde entre le point origine et le point de fin de la cloto, initialisé avec la longueur de vect
    double l = c;                       //La longueur développée de la cloto, initialisé avec la longueur de la corde
    double d;                           //Distance entre le point de début et de fin calculé sur la cloto
    double dl = 0.0;                    //Ecart entre cette distance et la corde à obtenir 
    double A2;                          //Carré du paramètre de la cloto (porte le signe de la courbure)
    Point2D ptDebLoc, ptFinLoc;         //Point de début et de fin sur la cloto dans le repère local
    Vector2D vOrient, vectRot, vectTra;

    double A, sDeb, ds;

    const double dlmax = 1E-14;

    do {
        l += dl;
        A2 = l / (endingCurvature - startingCurvature);
        A = std::sqrt(std::fabs(A2)) * (A2 > 0 ? 1.0 : -1.0);
        sDeb = A2 * startingCurvature;
        ptDebLoc = PtLoc(sDeb, A);   // Point sur la clothoïde
        ptFinLoc = PtLoc(sDeb + l, A);

        vOrient = ptFinLoc - ptDebLoc;
        d = vOrient.Length();
        dl = c - d;
    } while (std::fabs(dl / l) >= dlmax);

    ds = l;
    vectRot = chordVector.InVectorialReference(vOrient) / (d * d);
    ptDebLoc = ptDebLoc.RotatedBy(vectRot);
    vectTra = startingPoint - ptDebLoc;

    clotoideArc = ClotoideTransition(A, sDeb, ds, vectRot, vectTra);
    return true;
}

Point2D ClotoideTransition::PtLoc(double s, double A)
{
        constexpr double TwoRootPi = 3.54490770181103;
        constexpr double SqrtTwo = 1.41421356237309;
        constexpr double RootPiOverTwo = 1.2533141373155;

        s /= std::fabs(A); // Réduit l'abscisse curviligne sur la clotoïde unitaire
        double absS = std::fabs(s);
        double x, y;

        if (absS > TwoRootPi) {
            double t = absS / SqrtTwo;
            double F = 1.0 / t;
            double G = 0.5 / (t * t * t);

            if (absS < 5.75) {
                F -= 0.75 / (t * t * t * t * t);
                G -= 1.875 / (t * t * t * t * t * t * t);
                if (absS < 4.0) {
                    F += 6.5625 / (t * t * t * t * t * t * t * t * t);
                    G += 29.53125 / (t * t * t * t * t * t * t * t * t * t * t);
                }
            }

            double t2 = t * t;
            double cost2 = std::cos(t2);
            double sint2 = std::sin(t2);

            x = (RootPiOverTwo + F * sint2 - G * cost2) * SqrtTwo * std::copysign(1.0, s) / 2.0;
            y = (RootPiOverTwo - F * cost2 - G * sint2) * SqrtTwo * std::copysign(1.0, s) / 2.0;

        } else {
            x = s;
            y = (s * s * s) / 6.0;

            if (absS > 0.0730965294187392) {
                x -= (s * s * s * s * s) / 40.0;
                y -= (s * s * s * s * s * s * s) / 336.0;
                if (absS > 0.458853326351216) {
                    x += (s * s * s * s * s * s * s * s * s) / 3456.0;
                    y += (s * s * s * s * s * s * s * s * s * s * s) / 42240.0;
                    if (absS > 0.844610123283693) {
                        x -= (s * s * s * s * s * s * s * s * s * s * s * s * s) / 599040.0;
                        y -= (s * s * s * s * s * s * s * s * s * s * s * s * s * s * s) / 9676800.0;
                        if (absS > 1.23036692021617) {
                            x += (s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s) / 175472640.0;
                            y += (s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s) / 3530096640.0;
                            if (absS > 1.61612371714865) {
                                x -= (s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s) / 78033715200.0;
                                y -= (s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s) / 1880240947200.0;
                                if (absS > 2.00188051408112) {
                                    x += (s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s) / 49049763840000.0;
                                    y += (s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s) / 1377317368627200.0;
                                    if (absS > 2.3876373110136) {
                                        x -= (s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s) / 41421544567603200.0;
                                        y -= (s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s) / 1328346084409344000.0;
                                        if (absS > 2.77339410794608) {
                                            x += (s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s) / 45249466617298944000.0;
                                            y += (s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s) / 1631723190138961920000.0;
                                            if (absS > 3.15915090487856) {
                                                x -= (s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s) / 62098722550431436800000.0;
                                                y -= (s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s * s) / 248730558972268544000000.0;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return Point2D(x * std::fabs(A), y * A);

}
} // namespace LineaCore::Geometry::Alignments::Horizontal