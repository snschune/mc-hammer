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
#include "Particle.h"
#include "Nuclide.h"


using std::vector;
using std::stack;

typedef std::shared_ptr< Particle > Part_ptr;
typedef std::shared_ptr< Nuclide  > Nuclide_ptr;

class Material
//Material in which neutrons transport through. Contains all x-sec data and processes reactions
//Multigroup compatible. Fission not added yet.
{
  private:
    std::string                                     materialName;
    double                                          atomDensity; // for homogeneous, set to 1
    std::vector< std::pair< Nuclide_ptr, double > > nuclides;

    double getMicroXS( Part_ptr p );

  public:
    // Constructor/Destructor
    Material( std::string label, double atomDensityi ) : materialName(label), atomDensity(atomDensityi) {};
   ~Material() {};

    // Adders
    void addNuclide( Nuclide_ptr newNuclide, double atomFrac );

    // Getters
    std::string name()           { return materialName; };
    double      getAtomDensity() { return atomDensity;  };
    double      getMacroXS( Part_ptr p );

    // Functions
    Nuclide_ptr sampleNuclide   ( Part_ptr p                          );
    void        sampleCollision ( Part_ptr p, stack< Part_ptr > &bank );
};
#endif
