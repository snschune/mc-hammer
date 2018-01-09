/*
 Author: ESGonzalez
 Date: 1/8/18
*/

#include "Geometry.h"

bool Geometry::amIHere( point pos, Cell cell )
{
  // requires a vector of pairs of surfaces and sense (bool) for each cell
  vector< pair<surface,bool> > surfNSenses = cell.getSurfNSenses();
    
  bool isWithin = true;
  //cycle through each surface and if there is one that has a incorrect eval, you are not in this cell
  for( auto surfNSense : surfNSenses )
    {
      bool test = ( get<0>(surfNSense)->eval(pos) < 0 );
      isWithin = isWithin && ( test == get<1>(surfNSense) );
    }
  return isWithin;
}

Cell_ptr Geometry::whereAmI( point pos )
{
    
  Cell_ptr hereIAm;
    
  for( auto cell : cells )
    {
      if ( bool test = amIHere( pos, cell ) == true ):
	hereIAm->cell;
    }
  return hereIAm;
}


void Geometry::addCell( Cell newCell)
{
  cells.push_back(newCell);
}

void Geometry::addSurface( surface newSurface)
{
  surfaces.push_back(newSurface);
}

void Geometry::addMaterial( Material newMaterial)
{
  materials.push_back(newMaterial);
}
