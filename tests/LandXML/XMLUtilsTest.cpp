#include "LineaCore/LandXML/XMLUtils.hpp"
#include "LineaCore/Geometry/Point2D.hpp"
#include <gtest/gtest.h>
#include <libxml/xmlreader.h>
#include <limits>
#include <cstring>

using namespace LineaCore::LandXML;
using namespace LineaCore::Geometry;

TEST(XMLUtilsTest, ReadAttributeAsDouble_Valid) {
    xmlTextReaderPtr reader = xmlReaderForMemory(
        R"(<TestElement attr="42.5" />)", 
        strlen(R"(<TestElement attr="42.5" />)"), 
        nullptr, nullptr, 0);
    ASSERT_NE(reader, nullptr);

    xmlTextReaderRead(reader);
    double value = XMLUtils::ReadAttributeAsDouble(reader, "attr");
    EXPECT_DOUBLE_EQ(value, 42.5);

    xmlFreeTextReader(reader);
}

TEST(XMLUtilsTest, ReadAttributeAsDouble_Invalid) {
    xmlTextReaderPtr reader = xmlReaderForMemory(
        R"(<TestElement attr=" inf " />)", 
        strlen(R"(<TestElement attr=" inf " />)"), 
        nullptr, nullptr, 0);
    ASSERT_NE(reader, nullptr);

    xmlTextReaderRead(reader);
    try {
        ASSERT_THROW(XMLUtils::ReadAttributeAsDouble(reader, "attr"), std::runtime_error);
    } catch (const std::runtime_error& e) {
        std::string expectedMessage = "Attribute 'attr=\"\"' missing in Element <SomeElement>";
        EXPECT_EQ(e.what(), expectedMessage);
    }

    xmlFreeTextReader(reader);
}

TEST(XMLUtilsTest, ReadAttributeAsDouble_Missing) {
    xmlTextReaderPtr reader = xmlReaderForMemory(
        R"(<TestElement />)", 
        strlen(R"(<TestElement />)"), 
        nullptr, nullptr, 0);
    ASSERT_NE(reader, nullptr);

    xmlTextReaderRead(reader);
    EXPECT_THROW(XMLUtils::ReadAttributeAsDouble(reader, "attr"), std::runtime_error);

    xmlFreeTextReader(reader);
}

TEST(XMLUtilsTest, ReadAttributeAsString_Valid) {
    xmlTextReaderPtr reader = xmlReaderForMemory(
        R"(<TestElement attr="testValue" />)", 
        strlen(R"(<TestElement attr="testValue" />)"), 
        nullptr, nullptr, 0);
    ASSERT_NE(reader, nullptr);

    xmlTextReaderRead(reader);
    std::string value = XMLUtils::ReadAttributeAsString(reader, "attr");
    EXPECT_EQ(value, "testValue");

    xmlFreeTextReader(reader);
}

TEST(XMLUtilsTest, ReadContentAsPoint2D_Valid) {
    xmlTextReaderPtr reader = xmlReaderForMemory(
        R"(<TestElement>42.5 24.3</TestElement>)", 
        strlen(R"(<TestElement>42.5 24.3</TestElement>)"), 
        nullptr, nullptr, 0);
    ASSERT_NE(reader, nullptr);

    xmlTextReaderRead(reader);
    Point2D point = XMLUtils::ReadContentAsPoint2D(reader, "TestElement");
    EXPECT_DOUBLE_EQ(point.X, 24.3);
    EXPECT_DOUBLE_EQ(point.Y, 42.5);

    xmlFreeTextReader(reader);
}

TEST(XMLUtilsTest, ReadContentAsPoint2D_Invalid) {
    xmlTextReaderPtr reader = xmlReaderForMemory(
        R"(<TestElement>42.5 abc</TestElement>)", 
        strlen(R"(<TestElement>42.5 abc</TestElement>)"), 
        nullptr, nullptr, 0);
    ASSERT_NE(reader, nullptr);

    xmlTextReaderRead(reader);
    EXPECT_THROW(XMLUtils::ReadContentAsPoint2D(reader, "TestElement"), std::runtime_error);

    xmlFreeTextReader(reader);
}
