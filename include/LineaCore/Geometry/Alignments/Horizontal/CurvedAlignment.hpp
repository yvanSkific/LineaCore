// CurvedAlignment.hpp
#pragma once

#include "HorizontalAlignment.hpp"
#include "LineaCore/LandXML/LandXMLSerializable.hpp"
#include "LineaCore/Geometry/Point2D.hpp"
#include "LineaCore/Geometry/Vector2D.hpp"
#include <vector>
#include <string>
#include <cmath>
#include <memory>

namespace LineaCore::Geometry::Alignments::Horizontal {

class CurvedAlignment : public HorizontalAlignment, public LandXML::LandXMLSerializable {
private:
    Point2D _centerPoint;
    double _sens;
    double _absR;
    double _angDeb;
    double _ds;

    Point2D pointFromAngle(double angle) const;
    double angle(double s) const;

public:
    // Constructeurs
    CurvedAlignment(){};
    CurvedAlignment(const Point2D& centre, double rayonAbs, double sens, double angDebut, double longueurDev);
    CurvedAlignment(const Point2D& centre, double rayon, double angDebut, double longueurDev);

    // Destructeur
    virtual ~CurvedAlignment() = default;

    // Propriétés
    H_Type Type() const override;
    double Length() const override;
    double SignedRadius() const;

    // Méthodes
    Point2D Point(double s) const override;
    Vector2D Normal(double s) const override;
    double Curvature(double s) const override;
    std::vector<Point2D> Points(double maxThrow) const override;

    // Sérialisation
    void ReadLandXML(xmlTextReaderPtr reader) override;
    void WriteLandXML(xmlTextWriterPtr writer) const override;

    // Méthode statique
    static bool TryFromChordAndRadius(const Point2D& ptO, const Vector2D& v, double rr, std::unique_ptr<CurvedAlignment>& curve);
};

} // namespace LineaCore::Geometry::Alignments::Horizontal

