// XMLUtils.cpp
#include "LineaCore/LandXML/XMLUtils.hpp"
#include <libxml/xmlreader.h>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cstring>

namespace LineaCore::LandXML {

double XMLUtils::ReadAttributeAsDouble(xmlTextReaderPtr reader, const char* attributeName) {
    const char* attributeValue = reinterpret_cast<const char*>(xmlTextReaderGetAttribute(reader, BAD_CAST attributeName));
    if (attributeValue == nullptr || std::strlen(attributeValue) == 0) {
        std::ostringstream oss;
        oss << "Attribute '" << attributeName << "=\"\"' missing in Element <" 
            << reinterpret_cast<const char*>(xmlTextReaderConstName(reader)) << ">";
        //std::cerr << oss.str() << std::endl; // Impression sur std::cerr
        throw std::runtime_error(oss.str());
    }

    try {
        return ParseAsDouble(attributeValue, 
                             reinterpret_cast<const char*>(xmlTextReaderConstName(reader)), 
                             attributeName);
    } catch (const std::exception& ex) {
        std::ostringstream oss;
        oss << "Error parsing attribute '" << attributeName << "' in Element <" 
            << reinterpret_cast<const char*>(xmlTextReaderConstName(reader)) << ">: " << ex.what();
        //std::cerr << oss.str() << std::endl; // Impression sur std::cerr
        throw std::runtime_error(oss.str());    }
}

/* 
double XMLUtils::ReadAttributeAsNaNableDouble(const std::string& attributeValue) {
    if (attributeValue.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return ParseAsDouble(attributeValue, "", "");
}
 */

std::string XMLUtils::ReadAttributeAsString(xmlTextReaderPtr reader, const char* attributeName) {
    const char* attributeValue = reinterpret_cast<const char*>(xmlTextReaderGetAttribute(reader, BAD_CAST attributeName));
    if (attributeValue == nullptr || std::strlen(attributeValue) == 0)  {
        std::ostringstream oss;
        oss << "Attribute '" << attributeName << "=\"\"' missing in Element <" 
            << reinterpret_cast<const char*>(xmlTextReaderConstName(reader)) << ">";
        //std::cerr << oss.str() << std::endl; // Impression sur std::cerr
        throw std::runtime_error(oss.str());    
    }
    return attributeValue;
}

Geometry::Point2D XMLUtils::ReadContentAsPoint2D(xmlTextReaderPtr reader, const std::string& elementName) {
    
    std::string contentValue = reinterpret_cast<const char*>(xmlTextReaderReadString(reader));
    
    if (contentValue.empty()) {
        std::ostringstream oss;
        oss << "Missing content in Element <" << elementName << ">";
        //std::cerr << oss.str() << std::endl; // Impression sur std::cerr
        throw std::runtime_error(oss.str());
    }

    std::istringstream stream(contentValue);
    double x = 0.0, y = 0.0;
    if (!(stream >> y >> x)) {
        std::ostringstream oss;
        oss << "Content of two numerical values (Northing Easting) expected in Element <" << elementName << ">";
        //std::cerr << oss.str() << std::endl; // Impression sur std::cerr
        throw std::runtime_error(oss.str());    }
    return Geometry::Point2D(x, y);
}

double XMLUtils::ParseAsDouble(const std::string& strValue, const std::string& elementName, const std::string& attributeName) {
    if (strValue == "INF") {
        return std::numeric_limits<double>::infinity();
    }
    if (strValue == "-INF") {
        return -std::numeric_limits<double>::infinity();
    }

    char* endPtr = nullptr;
    double value = std::strtod(strValue.c_str(), &endPtr);

    if (*endPtr != '\0') {
        std::ostringstream oss;
        oss << "Attribute '" << attributeName << "=" << strValue 
            << "' numerical value expected in Element <" << elementName << ">";
        //std::cerr << oss.str() << std::endl; // Impression sur std::cerr
        throw std::runtime_error(oss.str());
    }

    return value;
}

} // namespace LineaCore::LandXML

