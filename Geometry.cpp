/*
 Author: ESGonzalez
 Date: 1/8/18
*/

#include "Geometry.h"
Geometry::Geometry()
{
	setup();
}

void Geometry::setup()
{	
	//material
	vector<double> sigt;
	vector<double> siga;
	vector<double> sigsi;
	vector<vector<double>> sigso;
	sigt.push_back(1.0);
	siga.push_back(0.5);
	sigsi.push_back(0.5);
	sigso.push_back(sigsi);
	Mat_ptr mat1 = make_shared<Material>(1, sigt, siga, sigso);
	materials.push_back(mat1);
	
	//surface bounbdaries
	Surf_ptr plane1 = make_shared<plane>("plane1", 0.0, 0.0, 1.0, 0.0);
	Surf_ptr plane2 = make_shared<plane>("plane2", 0.0, 0.0, 1.0, 5.0);
	surfaces.push_back(plane1);
	surfaces.push_back(plane2);

	//create cell
	pair< Surf_ptr, bool > surf1 (plane1, false);
	pair< Surf_ptr, bool > surf2 (plane2, true );
	vector< pair< Surf_ptr, bool > > cellSurfaces1;
	cellSurfaces1.push_back(surf1);
     cellSurfaces1.push_back(surf2);
	Cell_ptr cell1 = make_shared<Cell>(mat1, cellSurfaces1);
	cells.push_back(cell1);


}

/*
bool Geometry::amIHere( point pos, Cell& cell )
{
  // requires a vector of pairs of surfaces and sense (bool) for each cell
  vector< pair<Surf_ptr ,bool> > surfNSenses = cell.getSurfNSenses();
    
  bool isWithin = true;
  //cycle through each surface and if there is one that has a incorrect eval, you are not in this cell
  for( auto surfNSense : surfNSenses )
    {
      bool test = ( get<0>(surfNSense)->eval(pos) < 0 );
      isWithin = isWithin && ( test == get<1>(surfNSense) );
    }
  return isWithin;
}
*/

Cell_ptr Geometry::whereAmI( point pos )
{
    
  Cell_ptr hereIAm;
    
  for( auto cell : cells )
    {
     if ( bool test = cell->amIHere( pos ) == true )
	{
		hereIAm = cell;
	}
    }
  return hereIAm;
}


void Geometry::addCell(Cell_ptr newCell)
{
  cells.push_back(newCell);
}

void Geometry::addSurface( Surf_ptr newSurface)
{
  surfaces.push_back(newSurface);
}

void Geometry::addMaterial( Mat_ptr newMaterial)
{
  materials.push_back(newMaterial);
}


