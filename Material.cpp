/*
	Author: Blake
	Date: 11/8/17
	Req. Files: Material.cpp
*/

#include "Material.h"

void Material::addNuclide( Nuclide_ptr newNuclide, double atomFrac )
{
	nuclides.push_back( std::make_pair( newNuclide, atomFrac ) );
	return;
}

double Material::getMicroXS( int group ) 
{
  double xs = 0.0;
  for ( auto n : nuclides ) 
  { 
    // first is pointer to nuclide, second is atomic fraction
    xs += n.first->getTotalXS( group ) * n.second;
  }
  return xs;
}

double Material::getMacroXS( int group ) 
{
  return getAtomDensity() * getMicroXS( group );
}

// randomly sample a nuclide based on total cross sections and atomic fractions
Nuclide_ptr Material::sampleNuclide( int group ) 
{
  double u = getMicroXS( group ) * Urand();
  double s = 0.0;

  for ( auto n : nuclides ) 
  {
    // first is pointer to nuclide, second is atomic fraction
    s += n.first->getTotalXS( group ) * n.second;
    if ( s > u ) { return n.first; }
  }
  assert( false ); // should never reach here
  return nullptr;
}

// function that samples an entire collision: sample nuclide, then its reaction, 
// and finally process that reaction with input pointers to the working particle p
// and the particle bank
Reaction_ptr Material::sampleCollision( int group ) {
  // first sample nuclide
  Nuclide_ptr  N = sampleNuclide( group );

  // now get the reaction
  Reaction_ptr R = N->sampleReaction( group );

  return R;
}
