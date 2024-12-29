// StraightAlignment.cpp
#include "LineaCore/Geometry/Alignments/Horizontal/StraightAlignment.hpp"
#include "LineaCore/LandXML/XMLUtils.hpp"
#include <stdexcept>
#include <cmath>

namespace LineaCore::Geometry::Alignments::Horizontal {

StraightAlignment::StraightAlignment()
    : _normedVector(1.0, 0.0), // Vecteur unitaire par défaut (direction X)
      _ds(0.0)                 // Longueur par défaut
{
    startingPoint = Point2D(0.0, 0.0);
    SetExtremities(); // Initialise les extrémités avec les valeurs par défaut
}

StraightAlignment::StraightAlignment(const Point2D &stPoint, const Vector2D &vector)
    : _normedVector(vector.Normalized()),
        _ds(vector.Length()) {
    startingPoint = stPoint;
    SetExtremities();
}

StraightAlignment::StraightAlignment(const Point2D& stPoint, const Vector2D& vector, double length)
    : _normedVector(vector.Normalized()),
      _ds(length) {
    startingPoint = stPoint;
    SetExtremities();
}

HorizontalAlignment::H_Type StraightAlignment::Type() const {
    return HorizontalAlignment::H_Type::Straight;
}

double StraightAlignment::Length() const {
    return _ds;
}

Point2D StraightAlignment::Point(double s) const {
    return startingPoint + _normedVector * s;
}

Vector2D StraightAlignment::Normal(double s) const {
    return _normedVector.Rotated90ClockWise();
}

double StraightAlignment::Curvature(double s) const {
    return 0.0;
}

std::vector<Point2D> StraightAlignment::Points(double maxThrow) const {
    return {startingPoint, startingPoint + _normedVector * _ds};
}

// Implémentation de LandXMLSerializable
void StraightAlignment::ReadLandXML(xmlTextReaderPtr reader) {
    Point2D start;
    Point2D end;
    bool foundStart = false;
    bool foundEnd = false;

    while (xmlTextReaderRead(reader) == 1) {
        if (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT) {
            std::string nodeName = reinterpret_cast<const char*>(xmlTextReaderConstLocalName(reader));
            if (nodeName == "Start") {
                std::string content = reinterpret_cast<const char*>(xmlTextReaderReadString(reader));
                start = LandXML::XMLUtils::ReadContentAsPoint2D(content, "Start");
                foundStart = true;
            } else if (nodeName == "End") {
                std::string content = reinterpret_cast<const char*>(xmlTextReaderReadString(reader));
                end = LandXML::XMLUtils::ReadContentAsPoint2D(content, "End");
                foundEnd = true;
            }
        } else if (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT) {
            std::string nodeName = reinterpret_cast<const char*>(xmlTextReaderConstLocalName(reader));
            if (nodeName == "Line") {
                break;
            }
        }
    }

    if (!foundStart) {
        throw std::runtime_error("Missing <Start> element in <Line>");
    }
    if (!foundEnd) {
        throw std::runtime_error("Missing <End> element in <Line>");
    }

    startingPoint = start;
    Vector2D vector = end - start;
    _normedVector = vector.Normalized();
    _ds = vector.Length();
    SetExtremities();
}

void StraightAlignment::WriteLandXML(xmlTextWriterPtr writer) const {
    if (xmlTextWriterStartElement(writer, BAD_CAST "Line") < 0) {
        throw std::runtime_error("Error starting <Line> element");
    }

    if (xmlTextWriterStartElement(writer, BAD_CAST "Start") < 0 ||
        xmlTextWriterWriteFormatString(writer, "%f %f", startingPoint.Y, startingPoint.X) < 0 ||
        xmlTextWriterEndElement(writer) < 0) {
        throw std::runtime_error("Error writing <Start> element");
    }

    if (xmlTextWriterStartElement(writer, BAD_CAST "End") < 0 ||
        xmlTextWriterWriteFormatString(writer, "%f %f", endingPoint.Y, endingPoint.X) < 0 ||
        xmlTextWriterEndElement(writer) < 0) {
        throw std::runtime_error("Error writing <End> element");
    }

    if (xmlTextWriterEndElement(writer) < 0) {
        throw std::runtime_error("Error ending <Line> element");
    }
}


} // namespace LineaCore::Geometry::Alignments::Horizontal
