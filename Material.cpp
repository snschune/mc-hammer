/*
	Author: Blake
	Date: 11/8/17
	Req. Files: Material.cpp, Particle.h
*/

#include "Material.h"

void Material::addNuclide( Nuclide_ptr newNuclide, double atomFrac )
{
	nuclides.push_back( std::make_pair( newNuclide, atomFrac ) );
	return;
}

double Material::getMicroXS( Particle& p ) 
{
  double xs = 0.0;
  for ( auto n : nuclides ) 
  { 
    // first is pointer to nuclide, second is atomic fraction
    xs += n.first->getTotalXS( p ) * n.second;
  }
  return xs;
}

double Material::getMacroXS( Particle& p ) 
{
  return getAtomDensity() * getMicroXS( p );
}

// randomly sample a nuclide based on total cross sections and atomic fractions
Nuclide_ptr Material::sampleNuclide( Particle& p ) 
{
  double u = getMicroXS( p ) * Urand();
  double s = 0.0;

  for ( auto n : nuclides ) 
  {
    // first is pointer to nuclide, second is atomic fraction
    s += n.first->getTotalXS( p ) * n.second;
    if ( s > u ) { return n.first; }
  }
  assert( false ); // should never reach here
  return nullptr;
}

// function that samples an entire collision: sample nuclide, then its reaction, 
// and finally process that reaction with input pointers to the working particle p
// and the particle bank
void Material::sampleCollision( Particle& p, std::stack< Particle > &bank ) {
  // first sample nuclide
  Nuclide_ptr  N = sampleNuclide( p );

  // now get the reaction
  Reaction_ptr R = N->sampleReaction( p );

  // finally process the reaction
  R->sample( p, bank );
}
