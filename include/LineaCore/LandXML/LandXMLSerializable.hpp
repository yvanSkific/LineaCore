// LandXMLSerializable.hpp
#pragma once

#include <libxml/xmlreader.h> // Pour xmlTextReaderPtr
#include <libxml/xmlwriter.h> // Pour xmlTextWriterPtr
#include <stdexcept>
#include <string>

namespace LineaCore::LandXML {

class LandXMLSerializable {
public:
    virtual ~LandXMLSerializable() = default;

    // Méthodes virtuelles pures pour la sérialisation et la désérialisation
    virtual void ReadLandXML(xmlTextReaderPtr reader) = 0;
    virtual void WriteLandXML(xmlTextWriterPtr writer) const = 0;
};

} // namespace LineaCore::LandXML
