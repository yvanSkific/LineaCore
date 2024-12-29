// XMLUtils.cpp
#include "LineaCore/LandXML/XMLUtils.hpp"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <limits>

namespace LineaCore::LandXML {

double XMLUtils::ReadAttributeAsDouble(const std::string& attributeValue, const std::string& elementName, const std::string& attributeName) {
    if (attributeValue.empty()) {
        throw std::runtime_error("Attribute '" + attributeName + "=" + "' missing in Element <" + elementName + ">");
    }
    return ParseAsDouble(attributeValue, elementName, attributeName);
}

double XMLUtils::ReadAttributeAsNaNableDouble(const std::string& attributeValue) {
    if (attributeValue.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return ParseAsDouble(attributeValue, "", "");
}

std::string XMLUtils::ReadAttributeAsString(const std::string& attributeValue, const std::string& elementName, const std::string& attributeName) {
    if (attributeValue.empty()) {
        throw std::runtime_error("Attribute '" + attributeName + "=" + "' missing in Element <" + elementName + ">");
    }
    return attributeValue;
}

Geometry::Point2D XMLUtils::ReadContentAsPoint2D(const std::string& contentValue, const std::string& elementName) {
    if (contentValue.empty()) {
        throw std::runtime_error("Missing content in Element <" + elementName + ">");
    }

    std::istringstream stream(contentValue);
    double x = 0.0, y = 0.0;
    if (!(stream >> y >> x)) {
        throw std::runtime_error("Content of two numerical values (Northing Easting) expected in Element <" + elementName + ">");
    }
    return Geometry::Point2D(x, y);
}

double XMLUtils::ParseAsDouble(const std::string& value, const std::string& elementName, const std::string& attributeName) {
    if (value == "INF") {
        return std::numeric_limits<double>::infinity();
    }
    if (value == "-INF") {
        return -std::numeric_limits<double>::infinity();
    }

    try {
        size_t idx;
        double result = std::stod(value, &idx);
        if (idx != value.size()) {
            throw std::invalid_argument("Extra characters");
        }
        return result;
    } catch (const std::exception&) {
        throw std::runtime_error("Attribute '" + attributeName + "=" + value + "' numerical value expected in Element <" + elementName + ">");
    }
}

} // namespace LineaCore::LandXML

