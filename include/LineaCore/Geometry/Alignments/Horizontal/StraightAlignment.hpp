// StraightAlignment.hpp
#pragma once

#include "HorizontalAlignment.hpp" // HorizontalAlignment
#include "LineaCore/LandXML/LandXMLSerializable.hpp" // LandXMLSerializable
#include <memory>

namespace LineaCore::Geometry::Alignments::Horizontal {

class StraightAlignment : public HorizontalAlignment, public LandXML::LandXMLSerializable {
private:
    Vector2D _normedVector;
    double _ds;

public:
    StraightAlignment(){};
    StraightAlignment(const Point2D& ptDebut, const Vector2D& vecteur);
    StraightAlignment(const Point2D& ptDebut, const Vector2D& vecteur, double longueur);

    virtual ~StraightAlignment() = default;

    H_Type Type() const override;
    double Length() const override;
    
    Point2D Point(double s) const override;
    Vector2D Normal(double s) const override;
    double Curvature(double s) const override;

    std::vector<Point2D> Points(double maxThrow) const override;

        // Implémentation de LandXMLSerializable
    void ReadLandXML(xmlTextReaderPtr reader) override;
    void WriteLandXML(xmlTextWriterPtr writer) const override;
};

} // namespace LineaCore::Geometry::Alignments::Horizontal

