#include <gtest/gtest.h>
#include "LineaCore/Geometry/Alignments/Horizontal/CurvedAlignment.hpp"
#include "LineaCore/Geometry/Point2D.hpp" // Ensure this header file defines the Point2D class
#include "LineaCore/Geometry/Vector2D.hpp"

using namespace LineaCore::Geometry::Alignments::Horizontal;
using namespace LineaCore::Geometry;

TEST(CurvedAlignmentTest, Constructor) {
    Point2D center(100.0, 100.0);
    double radius = 50.0;
    double angleStart = 0.0;
    double arcLength = 25.0;

    CurvedAlignment curve(center, radius, angleStart, arcLength);

    EXPECT_EQ(curve.Type(), HorizontalAlignment::H_Type::Curved);
    EXPECT_DOUBLE_EQ(curve.Length(), arcLength);
    EXPECT_DOUBLE_EQ(curve.SignedRadius(), radius);
}

TEST(CurvedAlignmentTest, PointCalculation) {
    Point2D center(100.0, 100.0);
    double radius = 50.0;
    double angleStart = 0.0;
    double arcLength = 25.0;

    CurvedAlignment curve(center, radius, angleStart, arcLength);

    auto pointStart = curve.Point(0.0);
    EXPECT_DOUBLE_EQ(pointStart.X, 150.0);
    EXPECT_DOUBLE_EQ(pointStart.Y, 100.0);

    auto pointEnd = curve.Point(arcLength);
    EXPECT_NEAR(pointEnd.X, 143.879, 1e-3);
    EXPECT_NEAR(pointEnd.Y, 123.971, 1e-3);
}

TEST(CurvedAlignmentTest, Serialization) {
    Point2D center(100.0, 100.0);
    double radius = 50.0;
    double angleStart = 0.0;
    double arcLength = 25.0;

    CurvedAlignment curve(center, radius, angleStart, arcLength);

    const std::string outputFile = "output.xml";

    // Écrire dans un fichier de sortie
    xmlTextWriterPtr writer = xmlNewTextWriterFilename(outputFile.c_str(), 0);
    ASSERT_NE(writer, nullptr) << "Failed to create output file";

    xmlTextWriterStartDocument(writer, nullptr, "UTF-8", nullptr);
    // Activer l'indentation
    xmlTextWriterSetIndent(writer, 1);
    xmlTextWriterSetIndentString(writer, BAD_CAST "  "); // Indentation avec 2 espaces

    curve.WriteLandXML(writer);
    xmlTextWriterEndDocument(writer);

    xmlFreeTextWriter(writer);
}

TEST(CurvedAlignmentTest, Deserialization) {

        // Chemin vers le fichier d'exemple
    const std::string inputFile = "C:/yvans/Dev/CPP/Linea/Core/examples/LandXMLFiles/v1.xml";

    const char* xmlData =
        R"(<Curve rot="ccw">
               <Start>100.0 150.0</Start>
               <Center>100.0 100.0</Center>
               <End>101.243 149.845</End>
           </Curve>)";

    // Charger le fichier d'entrée
    xmlTextReaderPtr reader = xmlReaderForFile(inputFile.c_str(), nullptr, 0);
    ASSERT_NE(reader, nullptr) << "Failed to load input file";

    std::unique_ptr<CurvedAlignment> curve;

    while (xmlTextReaderRead(reader) == 1) {
        if (xmlStrcmp(xmlTextReaderConstName(reader), BAD_CAST "Curve") == 0) {
            curve = std::make_unique<CurvedAlignment>();
            curve->ReadLandXML(reader);
            break;
        }
    }
    xmlFreeTextReader(reader);

    ASSERT_TRUE(curve);
    EXPECT_DOUBLE_EQ(curve->SignedRadius(), -1251.8997665895513);
    EXPECT_NEAR(curve->Point(25.0).X, 1319515.3114442297, 1e-3);
    EXPECT_NEAR(curve->Point(25.0).Y, 6248058.6181983491, 1e-3);
}
