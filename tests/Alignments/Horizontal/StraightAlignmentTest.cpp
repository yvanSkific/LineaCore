#include "LineaCore/Geometry/Alignments/Horizontal/StraightAlignment.hpp"
#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

using namespace LineaCore::Geometry::Alignments::Horizontal;

TEST(StraightAlignmentTest, ReadWriteLandXML) {
    // Chemin vers le fichier d'exemple
    const std::string inputFile = "C:/yvans/Dev/CPP/Linea/Core/examples/LandXMLFiles/v1.xml";
    const std::string outputFile = "output.xml";

    // Charger le fichier d'entrée
    xmlTextReaderPtr reader = xmlReaderForFile(inputFile.c_str(), nullptr, 0);
    ASSERT_NE(reader, nullptr) << "Failed to load input file";

    // Lire l'alignement
    auto alignment = std::make_unique<StraightAlignment>();
    bool lineFound = false;

    while (xmlTextReaderRead(reader) == 1) {
        const char* nodeName = reinterpret_cast<const char*>(xmlTextReaderConstName(reader));
        if (xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT &&
            strcmp(nodeName, "Line") == 0) {
            alignment->ReadLandXML(reader);
            lineFound = true;
            break;
        }
    }

    ASSERT_TRUE(lineFound) << "Failed to find <Line> element in the input file";

    xmlFreeTextReader(reader);

    // Vérifier les données lues
    EXPECT_NEAR(alignment->getStartingPoint().X, 1320073.617574, 0.001);
    EXPECT_NEAR(alignment->getStartingPoint().Y, 6248433.993484, 0.001);
    EXPECT_NEAR(alignment->getEndingPoint().X, 1319630.077000, 0.001);
    EXPECT_NEAR(alignment->getEndingPoint().Y, 6248132.874953, 0.001);

    // Écrire dans un fichier de sortie
    xmlTextWriterPtr writer = xmlNewTextWriterFilename(outputFile.c_str(), 0);
    ASSERT_NE(writer, nullptr) << "Failed to create output file";

    xmlTextWriterStartDocument(writer, nullptr, "UTF-8", nullptr);
        // Activer l'indentation
    xmlTextWriterSetIndent(writer, 1);
    xmlTextWriterSetIndentString(writer, BAD_CAST "  "); // Indentation avec 2 espaces
    
    alignment->WriteLandXML(writer);
    xmlTextWriterEndDocument(writer);

    xmlFreeTextWriter(writer);

    // Vérifier que le fichier de sortie contient les mêmes informations
    std::ifstream outFile(outputFile);
    std::ostringstream outBuffer;
    outBuffer << outFile.rdbuf();

    std::string outputContent = outBuffer.str();
    EXPECT_NE(outputContent.find("<Start>"), std::string::npos);
    EXPECT_NE(outputContent.find("<End>"), std::string::npos);
    EXPECT_NE(outputContent.find("1320073.617574"), std::string::npos);
    EXPECT_NE(outputContent.find("6248433.993484"), std::string::npos);
    EXPECT_NE(outputContent.find("1319630.077000"), std::string::npos);
    EXPECT_NE(outputContent.find("6248132.874953"), std::string::npos);
}
