#pragma once

#include "TransitionAlignment.hpp"
#include "LineaCore/LandXML/LandXMLSerializable.hpp"
#include "LineaCore/Geometry/Point2D.hpp"
#include "LineaCore/Geometry/Vector2D.hpp"
#include <vector>
#include <cmath>

namespace LineaCore::Geometry::Alignments::Horizontal {

class ClotoideTransition : public TransitionAlignment, public LandXML::LandXMLSerializable {
private:
    double _A;                      // Paramètre de la cloto
    double _startAbscissa;          // Longueur développée entre l'origine de la cloto et le point de début
    double _length;                 // Longueur développée de l'arc de cloto

    Vector2D _rotationVector;       // Vecteur rotation pour le passage du repère local au repère global
    Vector2D _translationVector;    // Vecteur translation pour le passage du repère local au repère global

public:
    ClotoideTransition(double parameter, double startAbscissa, double length, const Vector2D& rotationVector, const Vector2D& translationVector);
    virtual ~ClotoideTransition() = default;

    H_Type Type() const override;
    double Length() const override;

    Point2D Point(double s) const override;
    Vector2D Normal(double s) const override;
    double Curvature(double s) const override;

    std::vector<Point2D> Points(double maxThrow) const override;

    void ReadLandXML(xmlTextReaderPtr reader) override;
    void WriteLandXML(xmlTextWriterPtr writer) const override;

    // Constructeurs statiques pour générer des transitions
    static bool TryFromVectorAndCurvatures(const Point2D& startingPoint, const Vector2D& chordVector, double startingCurvature, double endingCurvature, ClotoideTransition& clotoideArc);
    static bool TryFromPointToAlign(const Point2D& point, const Point2D& alignmentOrigin, const Vector2D& alignmentVector, ClotoideTransition& clotoideArc);
    static bool TryFromAlignToPoint(const Point2D& oAlign, const Vector2D& vAlign, const Point2D& Pt, ClotoideTransition& clotoide);

private:
    static Point2D PtLoc(double s, double A);
    static Vector2D PtUnit(double s);
    static double YsurXclotoUnit(double x);
};

} // namespace LineaCore::Geometry::Alignments::Horizontal
