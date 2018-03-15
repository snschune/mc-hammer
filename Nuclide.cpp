/*
  Author: ESGonzalez
  Date: 2/20/18
*/

#include "Nuclide.h"

// return the total microscopic cross section
double Nuclide::getTotalXS( Part_ptr p ) 
{
  double totalXS = 0.0;

  for ( auto reaction : reactions ) 
  {
    totalXS += reaction->getXS( p );
  }
  return totalXS;
}

double Nuclide::getXS( Part_ptr p, std::string reactionName ) 
{
  double xs = 0.0;
  for ( auto reaction : reactions ) 
  {
    if ( reaction->name() == reactionName )
    {
      xs += reaction->getXS( p ); 
    }
  }
  return xs;
}

// randomly sample a reaction type from this nuclide
Reaction_ptr Nuclide::sampleReaction( Part_ptr p ) 
{
  double u = getTotalXS( p ) * Urand();
  double s = 0.0;
  for ( auto reaction : reactions ) {
    s += reaction->getXS( p );
    if ( s > u ) { return reaction; }
  }
  assert( false ); // should never reach here
  return nullptr;
}