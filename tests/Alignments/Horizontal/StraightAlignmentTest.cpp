#include "LineaCore/Geometry/Alignments/Horizontal/StraightAlignment.hpp"
#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

using namespace LineaCore::Geometry::Alignments::Horizontal;

TEST(StraightAlignmentTest, ReadWriteLandXML) {
    // Chemin vers le fichier d'exemple
    const std::string inputFile = "path/to/v1.xml";
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
    EXPECT_NEAR(alignment->getStartingPoint().X, 123.456, 0.001);
    EXPECT_NEAR(alignment->getStartingPoint().Y, 654.321, 0.001);
    EXPECT_NEAR(alignment->getEndingPoint().X, 789.012, 0.001);
    EXPECT_NEAR(alignment->getEndingPoint().Y, 210.987, 0.001);

    // Écrire dans un fichier de sortie
    xmlTextWriterPtr writer = xmlNewTextWriterFilename(outputFile.c_str(), 0);
    ASSERT_NE(writer, nullptr) << "Failed to create output file";

    xmlTextWriterStartDocument(writer, nullptr, "UTF-8", nullptr);
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
    EXPECT_NE(outputContent.find("123.456"), std::string::npos);
    EXPECT_NE(outputContent.find("654.321"), std::string::npos);
    EXPECT_NE(outputContent.find("789.012"), std::string::npos);
    EXPECT_NE(outputContent.find("210.987"), std::string::npos);
}
