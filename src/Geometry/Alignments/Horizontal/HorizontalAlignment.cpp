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

// Getter pour la tangente de départ
Vector2D HorizontalAlignment::StartingTangent() const{
    return startingNormal.Rotated90CounterClockWise();
}

// Getter pour la tangente de fin
Vector2D HorizontalAlignment::EndingTangent() const{
    return endingNormal.Rotated90CounterClockWise();
}

} // namespace LineaCore::Geometry::Alignments::Horizontal
