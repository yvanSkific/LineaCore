// CurvedAlignment.cpp

#include "LineaCore/Geometry/Alignments/Horizontal/CurvedAlignment.hpp"
#include "LineaCore/LandXML/XMLUtils.hpp"
#include <cmath>
#include <stdexcept>

namespace LineaCore::Geometry::Alignments::Horizontal {

CurvedAlignment::CurvedAlignment(const Point2D& centre, double rayonAbs, double sens, double angDebut, double longueurDev)
    : _centerPoint(centre), _absR(rayonAbs), _sens(sens), _angDeb(angDebut), _ds(longueurDev) {
    SetExtremities();
}

CurvedAlignment::CurvedAlignment(const Point2D& centre, double rayon, double angDebut, double longueurDev)
    : CurvedAlignment(centre, std::abs(rayon), (rayon >= 0.0 ? 1.0 : -1.0), angDebut, longueurDev) {}

HorizontalAlignment::H_Type CurvedAlignment::Type() const {
    return HorizontalAlignment::H_Type::Curved;
}

double CurvedAlignment::Length() const {
    return _ds;
}

double CurvedAlignment::SignedRadius() const {
    return _sens * _absR;
}

Point2D CurvedAlignment::Point(double s) const {
    return pointFromAngle(angle(s));
}

Vector2D CurvedAlignment::Normal(double s) const {
    return Vector2D::Polar(1.0, angle(s));
}

double CurvedAlignment::Curvature(double /*s*/) const {
    return _sens / _absR;
}

std::vector<Point2D> CurvedAlignment::Points(double maxThrow) const {
    int n = static_cast<int>(std::ceil(_ds / (_absR * 2.0 * std::acos(1.0 - maxThrow / _absR)))) + 1;
    double dTheta = _ds / _absR / n;

    std::vector<Point2D> points;
    points.reserve(n + 1);

    double theta = _angDeb;
    for (int i = 0; i < n; ++i) {
        points.push_back(pointFromAngle(theta));
        theta += _sens * dTheta;
    }
    points.push_back(Point(_ds));

    return points;
}

void CurvedAlignment::ReadLandXML(xmlTextReaderPtr reader) {
    std::string rot = LandXML::XMLUtils::ReadAttributeAsString(
        reinterpret_cast<const char*>(xmlTextReaderGetAttribute(reader, BAD_CAST "rot")),
        reinterpret_cast<const char*>(xmlTextReaderConstName(reader)), "rot");

    if (rot != "cw" && rot != "ccw") {
        throw std::runtime_error("Attribute 'rot' value must be \"cw\" or \"ccw\" in Element <" +
                                 std::string(reinterpret_cast<const char*>(xmlTextReaderConstName(reader))) + ">");
    }

    Point2D start = Point2D::NaN();
    Point2D center = Point2D::NaN();
    Point2D end = Point2D::NaN();

    // Parcours des nœuds enfants
    while (xmlTextReaderRead(reader) == 1) {
        if (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT) {
            std::string elementName(reinterpret_cast<const char*>(xmlTextReaderConstName(reader)));
            if (elementName == "Start") {
                start = LandXML::XMLUtils::ReadContentAsPoint2D(
                    reinterpret_cast<const char*>(xmlTextReaderReadString(reader)), "Start");
            } else if (elementName == "Center") {
                center = LandXML::XMLUtils::ReadContentAsPoint2D(
                    reinterpret_cast<const char*>(xmlTextReaderReadString(reader)), "Center");
            } else if (elementName == "End") {
                end = LandXML::XMLUtils::ReadContentAsPoint2D(
                    reinterpret_cast<const char*>(xmlTextReaderReadString(reader)), "End");
            }
        } else if (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT) {
            std::string elementName(reinterpret_cast<const char*>(xmlTextReaderConstName(reader)));
            if (elementName == "Curve") {
                break;
            }
        }
    }

    // Validation des points lus
    if (start.IsNaN()) {
        throw std::runtime_error("Missing <Start> element in <Curve>");
    }
    if (center.IsNaN()) {
        throw std::runtime_error("Missing <Center> element in <Curve>");
    }
    if (end.IsNaN()) {
        throw std::runtime_error("Missing <End> element in <Curve>");
    }

    // Initialisation des propriétés de l'arc
    _centerPoint = center;
    Vector2D startVector = start - center;
    _absR = startVector.Length();
    _angDeb = startVector.Angle02Pi();

    Vector2D endVector = end - center;
    if (rot == "ccw") {
        _sens = 1.0;
        _ds = _absR * endVector.InVectorialReference(startVector).Angle02Pi();
    } else {
        _sens = -1.0;
        _ds = _absR * startVector.InVectorialReference(endVector).Angle02Pi();
    }

    // Mise à jour des extrémités
    SetExtremities();
}

void CurvedAlignment::WriteLandXML(xmlTextWriterPtr writer) const {
    xmlTextWriterStartElement(writer, BAD_CAST "Curve");

    xmlTextWriterWriteAttribute(writer, BAD_CAST "rot", BAD_CAST (_sens > 0 ? "ccw" : "cw"));

    xmlTextWriterStartElement(writer, BAD_CAST "Start");
    xmlTextWriterWriteFormatString(writer, "%.9f %.9f", startingPoint.Y, startingPoint.X);
    xmlTextWriterEndElement(writer);

    xmlTextWriterStartElement(writer, BAD_CAST "Center");
    xmlTextWriterWriteFormatString(writer, "%.9f %.9f", _centerPoint.Y, _centerPoint.X);
    xmlTextWriterEndElement(writer);

    xmlTextWriterStartElement(writer, BAD_CAST "End");
    xmlTextWriterWriteFormatString(writer, "%.9f %.9f",endingPoint.Y, endingPoint.X);
    xmlTextWriterEndElement(writer);

    xmlTextWriterEndElement(writer);
}

Point2D CurvedAlignment::pointFromAngle(double angle) const {
    return Point2D(_centerPoint.X + std::cos(angle) * _absR, _centerPoint.Y + std::sin(angle) * _absR);
}

double CurvedAlignment::angle(double s) const {
    return _angDeb + _sens * s / _absR;
}

bool CurvedAlignment::TryFromChordAndRadius(const Point2D& ptO, const Vector2D& v, double rr,
                                            std::unique_ptr<CurvedAlignment>& curve) {
    double tanTheta = 0.0;
    double d = v.Length() / 2.0;

    if (d > std::abs(rr)) {
        curve.reset();
        return false;
    }

    double absR = std::abs(rr);
    double sens = (rr >= 0.0 ? 1.0 : -1.0);
    Point2D ptC;
    double angDeb;
    double ds;

    if (d == absR) {
        ptC = static_cast<Point2D>(v / 2.0);
    } else {
        tanTheta = sens * std::sqrt((d * d) / (absR * absR - d * d));
        ptC.X = (v.X - v.Y / tanTheta) / 2.0;
        ptC.Y = (v.Y + v.X / tanTheta) / 2.0;
    }

    angDeb = static_cast<Vector2D>(-ptC).Angle02Pi();
    ds = std::abs(std::atan(tanTheta) * 2.0 * absR);
    ptC.TranslateBy(Vector2D(ptO));

    curve = std::make_unique<CurvedAlignment>(ptC, sens * absR, angDeb, ds);
    return true;
}

} // namespace LineaCore::Geometry::Alignments::Horizontal
