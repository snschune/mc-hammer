#ifndef __NUCLIDE_H__
#define __NUCLIDE_H__

#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include <cmath>
#include <string>
#include <cassert>
#include "Reaction.h"

typedef std::shared_ptr< Reaction > Reaction_ptr;

class Nuclide
{
  private:
    std::string                 nuclideName;
    std::vector< Reaction_ptr > reactions;

  public:
    // Constructor/Destructor
    Nuclide( std::string label ) : nuclideName( label ) {};
   ~Nuclide() {};

    // Adders/Setters
    void addReaction ( Reaction_ptr newReaction ) { reactions.push_back( newReaction ); };

    // Getters
    std::string                 name()         { return nuclideName;  };
    std::vector< Reaction_ptr > getReactions() { return reactions;    };
    double                      getTotalXS ( int group                           );
    double                      getXS      ( int group, std::string reactionName );

    // Functions
    Reaction_ptr sampleReaction( int group );
};

#endif