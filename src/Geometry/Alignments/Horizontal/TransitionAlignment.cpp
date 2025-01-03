// TransitionAlignment.cpp

#include "LineaCore/Geometry/Alignments/Horizontal/TransitionAlignment.hpp"

namespace LineaCore::Geometry::Alignments::Horizontal {

HorizontalAlignment::H_Type TransitionAlignment::Type() const {
    // Retournez le type approprié pour TransitionAlignment
    return HorizontalAlignment::H_Type::Transition;
}

} // namespace LineaCore::Geometry::Alignments::Horizontal