// TransitionAlignment.hpp

#include "HorizontalAlignment.hpp"

namespace LineaCore::Geometry::Alignments::Horizontal {

class TransitionAlignment : public HorizontalAlignment {
protected:
    // Membres communs aux courbes de transition (ajoutez si nécessaire).

public:
    // Constructeur et destructeur
    TransitionAlignment() = default;
    virtual ~TransitionAlignment() = default;

};

} // namespace LineaCore::Geometry::Alignments::Horizontal
