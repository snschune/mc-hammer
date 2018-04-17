#include "Nuclide.h"

// return the total microscopic cross section
double Nuclide::getTotalXS( int group ) 
{
  double totalXS = 0.0;

  for ( auto reaction : reactions ) 
  {
    totalXS += reaction->getXS( group );
  }
  return totalXS;
}

double Nuclide::getXS( int group, std::string reactionName ) 
{
  double xs = 0.0;
  for ( auto reaction : reactions ) 
  {
    if ( reaction->name() == reactionName )
    {
      xs += reaction->getXS( group ); 
    }
  }
  return xs;
}

// randomly sample a reaction type from this nuclide
Reaction_ptr Nuclide::sampleReaction( int group ) 
{
  double u = getTotalXS( group ) * Urand();
  double s = 0.0;
  for ( auto reaction : reactions ) {
    s += reaction->getXS( group );
    if ( s > u ) { return reaction; }
  }
  assert( false ); // should never reach here
  return nullptr;
}