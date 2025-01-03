// XMLUtils.hpp
#pragma once

#include <libxml/xmlreader.h> // Pour xmlTextReaderPtr
#include <string>
#include "LineaCore/Geometry/Point2D.hpp"

namespace LineaCore::LandXML {

class XMLUtils {
public:
    // Read an attribute as a double
    static double ReadAttributeAsDouble(xmlTextReaderPtr reader, const char* attributeName);

    // Read an attribute as a double, allowing NaN if absent
    // static double ReadAttributeAsNaNableDouble(const std::string& attributeValue);

    // Read an attribute as a string
    static std::string ReadAttributeAsString(xmlTextReaderPtr reader, const char* attributeName);

    // Read the content of an element as a Point2D
    static Geometry::Point2D ReadContentAsPoint2D(xmlTextReaderPtr reader, const std::string& elementName);

private:
    // Parse a string as a double with error checking
    static double ParseAsDouble(const std::string& value, const std::string& elementName, const std::string& attributeName);
};

} // namespace LineaCore::LandXML

