// HorizontalAlignment.cpp

#include "LineaCore/Geometry/Alignments/Horizontal/HorizontalAlignment.hpp"

namespace LineaCore::Geometry::Alignments::Horizontal {

void HorizontalAlignment::SetExtremities()
{
    startingPoint = Point(0.0);
    endingPoint = Point(Length());
    startingNormal = Normal(0.0);
    endingNormal = Normal(Length());
}

} // namespace LineaCore::Geometry::Alignments::Horizontal 