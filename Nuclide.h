#ifndef __NUCLIDE_H__
#define __NUCLIDE_H__

#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include <cmath>
#include <string>
#include <cassert>
#include "XSection.h"
#include "Random.h"

typedef std::shared_ptr< XSection > XSec_ptr;

class Nuclide
{
  private:
    std::string             nuclideName;
    std::vector< XSec_ptr > xSections;

  public:
    // Constructor/Destructor
    Nuclide( std::string label ) : nuclideName( label ) {};
   ~Nuclide() {};

    // Adders/Setters
    void addXSection ( XSec_ptr newXSection ) { xSections.push_back( newXSection ); };

    // Getters
    std::string                 name()         { return nuclideName;  };
    std::vector< XSec_ptr >     getXSections() { return xSections;    };
    double                      getTotalXS     ( int group                           );
    double                      getXS          ( int group, std::string xSectionName );

    // Functions
    React_ptr sampleReaction( int group );
};

#endif