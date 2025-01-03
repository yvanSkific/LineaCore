// TransitionAlignment.hpp
#pragma once

#include "HorizontalAlignment.hpp"

namespace LineaCore::Geometry::Alignments::Horizontal {

class TransitionAlignment : public HorizontalAlignment {
protected:
    // Membres communs aux courbes de transition (ajoutez si nécessaire).

public:
    // Constructeur et destructeur
    TransitionAlignment() = default;
    virtual ~TransitionAlignment() = default;

    H_Type Type() const override;

};

} // namespace LineaCore::Geometry::Alignments::Horizontal
