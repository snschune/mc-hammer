/*
	Author: Blake
	Date: 11/8/17
	Req. Files: Material.cpp, Particle.h
*/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include <cmath>
#include <string>
#include "Nuclide.h"
#include "Reaction.h"

using std::vector;
using std::stack;

typedef std::shared_ptr< Reaction > Reaction_ptr;
typedef std::shared_ptr< Nuclide  > Nuclide_ptr;

class Material
//Material in which neutrons transport through. Contains all x-sec data and processes reactions
//Multigroup compatible. Fission not added yet.
{

  private:
    std::string                                     materialName;
    double                                          atomDensity; // for homogeneous, set to 1
    std::vector< std::pair< Nuclide_ptr, double > > nuclides;

    double getMicroXS( int group );

  public:
    // Constructor/Destructor
    Material( std::string label, double atomDensityi ) : materialName( label ), atomDensity( atomDensityi ) {};
   ~Material() {};

    // Adders
    void addNuclide( Nuclide_ptr newNuclide, double atomFrac );

    // Getters
    std::string name()           { return materialName; };
    double      getAtomDensity() { return atomDensity;  };
    double      getMacroXS( int group );

    // Functions
    Nuclide_ptr     sampleNuclide   ( int group );
    Reaction_ptr    sampleCollision ( int group );
};
#endif
