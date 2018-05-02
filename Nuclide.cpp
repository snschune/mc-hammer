#include "Nuclide.h"

// return the total microscopic cross section
double Nuclide::getTotalXS( int group ) 
{
  double totalXS = 0.0;

  for ( auto xSection : xSections ) 
  {
    totalXS += xSection->getXS( group );
  }
  return totalXS;
}

double Nuclide::getXS( int group, std::string xSectionName ) 
{
  double xs = 0.0;
  for ( auto xSection : xSections ) 
  {
    if ( xSection->name() == xSectionName )
    {
      xs += xSection->getXS( group ); 
    }
  }
  return xs;
}

// randomly sample a xSection type from this nuclide
React_ptr Nuclide::sampleReaction( int group ) 
{
  double u = getTotalXS( group ) * Urand();
  double s = 0.0;
  for ( auto xSection : xSections ) {
    s += xSection->getXS( group );
    if ( s > u ) { return xSection->getRxn(); }
  }
  assert( false ); // should never reach here
  return nullptr;
}