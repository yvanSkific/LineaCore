// ClotoideTransition.cpp

#include "LineaCore/Geometry/Alignments/Horizontal/ClotoideTransition.hpp"
#include "LineaCore/LandXML/XMLUtils.hpp"
#include "LineaCore/Geometry/GeometryUtils.hpp"

namespace LineaCore::Geometry::Alignments::Horizontal {

ClotoideTransition::ClotoideTransition(double parameter, double startAbscissa, double length, const Vector2D &rotationVector, const Vector2D &translationVector)
    : _A(parameter), _startAbscissa(startAbscissa), _ds(length), 
    _rotationVector(rotationVector), _translationVector(translationVector) {
    SetExtremities();
}

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

bool ClotoideTransition::IsCounterClockWise() const
{
    if (_startAbscissa < 0) {
        return _A < 0;
    } else {
        return _A > 0;
    }
}

Point2D ClotoideTransition::PI() const {
    return GeometryUtils::IntersectionStraightStraight(
        startingPoint,
        StartingTangent(),
        endingPoint,
        EndingTangent()
    );
}

double ClotoideTransition::Length() const {
    return _ds;
}

Point2D ClotoideTransition::Point(double s) const {
    return PtLoc(_startAbscissa + s, _A).RotatedBy(_rotationVector) + _translationVector;
}

Vector2D ClotoideTransition::Normal(double s) const {
    double sLocal = _startAbscissa + s;
    double AngVectTang = _rotationVector.AngleMinusPiPi() + (sLocal * sLocal) / _A / std::fabs(_A) / 2.0;
    return Vector2D(std::sin(AngVectTang), -std::cos(AngVectTang));
}

double ClotoideTransition::Curvature(double s) const {
    return (_startAbscissa + s) / _A / std::fabs(_A);
}

std::vector<Point2D> ClotoideTransition::Points(double maxThrow) const {
    int N = static_cast<int>(std::ceil((_ds * _ds) / (4 * std::fabs(_A) * std::sqrt(2 * _ds * maxThrow)))) + 1;
    double dTetha = (_ds * _ds) / (N * 2 * _A * _A);
    std::vector<Point2D> points(N + 1);
    double s = 0;

    for (int i = 0; i < N; ++i) {
        points[i] = Point(std::fabs(s + _startAbscissa));
        s = std::sqrt(s * s + 2 * _A * _A * dTetha);
    }

    s = _ds;
    points[N] = Point(std::fabs(s + _startAbscissa));

    return points;
}

void ClotoideTransition::ReadLandXML(xmlTextReaderPtr reader) {
    double length = LandXML::XMLUtils::ReadAttributeAsDouble(reader, "length");
    double radiusEnd = LandXML::XMLUtils::ReadAttributeAsDouble(reader, "radiusEnd");
    if (radiusEnd == 0) {
        throw std::runtime_error("Attribute 'radiusEnd' value cannot be zero in Element <Spiral>");
    }
    double radiusStart = LandXML::XMLUtils::ReadAttributeAsDouble(reader, "radiusStart");
    if (radiusStart == 0) {
        throw std::runtime_error("Attribute 'radiusStart' value cannot be zero in Element <Spiral>");
    }
    std::string rot = LandXML::XMLUtils::ReadAttributeAsString(reader, "rot");
    if (rot != "cw" && rot != "ccw") {
        throw std::runtime_error("Attribute 'rot' value must be \"cw\" or \"ccw\" in Element <Spiral>");
    }
    std::string spiType = LandXML::XMLUtils::ReadAttributeAsString(reader, "spiType");
    if (spiType != "clothoid") {
        throw std::runtime_error("Attribute 'spiType' value must be \"clothoid\" in Element <Spiral>");
    }

    Point2D start = Point2D::NaN();
    Point2D pi = Point2D::NaN();
    Point2D end = Point2D::NaN();

    while (xmlTextReaderRead(reader)) {
        if (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT) {
            std::string nodeName(reinterpret_cast<const char*>(xmlTextReaderConstLocalName(reader)));
            if (nodeName == "Start") {
                start = LandXML::XMLUtils::ReadContentAsPoint2D(reader, "Start");
            } else if (nodeName == "PI") {
                pi = LandXML::XMLUtils::ReadContentAsPoint2D(reader, "PI");
            } else if (nodeName == "End") {
                end = LandXML::XMLUtils::ReadContentAsPoint2D(reader, "End");
            }
        } else if (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT) {
            std::string nodeName(reinterpret_cast<const char*>(xmlTextReaderConstLocalName(reader)));
            if (nodeName == "Spiral") {
                break;
            }
        }
    }

    if (start.IsNaN() || pi.IsNaN() || end.IsNaN()) {
        throw std::runtime_error("Missing required points in <Spiral>");
    }

    double sens = (rot == "ccw") ? 1.0 : -1.0;
    double startCurvature = radiusStart == std::numeric_limits<double>::infinity() ? 0.0 : sens / radiusStart;
    double endCurvature = radiusEnd == std::numeric_limits<double>::infinity() ? 0.0 : sens / radiusEnd;

    if (!TryFromVectorAndCurvatures(start, end - start, startCurvature, endCurvature, *this)) {
        throw std::runtime_error("Clothoid Spiral could not be defined from the given values in Element <Spiral>");
    }

    SetExtremities();
}

void ClotoideTransition::WriteLandXML(xmlTextWriterPtr writer) const {
    xmlTextWriterStartElement(writer, BAD_CAST "Spiral");

    xmlTextWriterWriteAttribute(writer, BAD_CAST "length", BAD_CAST std::to_string(_ds).c_str());
    xmlTextWriterWriteAttribute(writer, BAD_CAST "radiusEnd", BAD_CAST std::to_string(1.0 / std::abs(Curvature(_ds))).c_str());
    xmlTextWriterWriteAttribute(writer, BAD_CAST "radiusStart", BAD_CAST std::to_string(1.0 / std::abs(Curvature(0.0))).c_str());
    xmlTextWriterWriteAttribute(writer, BAD_CAST "rot", BAD_CAST (IsCounterClockWise() ? "ccw" : "cw"));
    xmlTextWriterWriteAttribute(writer, BAD_CAST "spiType", BAD_CAST "clothoid");

    xmlTextWriterStartElement(writer, BAD_CAST "Start");
    xmlTextWriterWriteFormatString(writer, LandXML::xmlCoordFormat, startingPoint.Y, startingPoint.X);
    xmlTextWriterEndElement(writer);

    Point2D pi = PI();
    xmlTextWriterStartElement(writer, BAD_CAST "PI");
    xmlTextWriterWriteFormatString(writer, LandXML::xmlCoordFormat, pi.Y, pi.X);
    xmlTextWriterEndElement(writer);

    xmlTextWriterStartElement(writer, BAD_CAST "End");
    xmlTextWriterWriteFormatString(writer, LandXML::xmlCoordFormat, endingPoint.Y, endingPoint.X);
    xmlTextWriterEndElement(writer);

    xmlTextWriterEndElement(writer);
}

} // namespace LineaCore::Geometry::Alignments::Horizontal