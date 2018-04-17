/*
 Author: Blake
 Date: 11/8/17
 */

#include "Cell.h"

double Cell::distToCollision( int group )
{
  double total_xs = mat->getMacroXS( group );
  double dist = -log(Urand())/total_xs;
  return dist;
}

bool Cell::amIHere( const point& pos )
{
  bool isWithin = true;
  //cycle through each surface and if there is one that has a incorrect eval, you are not in this cell
  for(auto surfacePair: surfacePairs)
  {
    bool posInSurface = (surfacePair.first->eval(pos) < 0); //is the position inside(true) or out of the surface
    bool cellInSurface = surfacePair.second;
    bool match = posInSurface == cellInSurface;
    isWithin = isWithin == match;
  }
  return isWithin;
}

pair<Surf_ptr, double> Cell::closestSurface(Part_ptr p)
{
	Surf_ptr min_surf = nullptr;
	double min_val = std::numeric_limits<double>::max();
	point pos = p->getPos();
	point dir = p->getDir();
	for(auto bound: surfacePairs)
	{
		Surf_ptr cur_surf =  bound.first;
		double dist = cur_surf->distance(pos,dir);
		if(dist < min_val && dist >  0)
		{
			min_surf = cur_surf;
			min_val  = dist;
		}
	}
	if(min_surf == nullptr)
	{
		p->printState();
		std::cerr << "ERROR: NO SURFACE FOUND" << std::endl;
		std::exit(1);
	}
	return make_pair(min_surf, min_val);
}

double Cell::distToSurface(Part_ptr pi)
{
    Surf_ptr close_surface;
    double dist;
    tie(close_surface,dist) = closestSurface(pi);
    return dist;
}

// Estimator interface

void Cell::scoreTally(Part_ptr p , double xs) 
{
  // for each EstimatorCollection
    // for each attribute
      // get the index of the Estimator to score
      // score the estimator
}

void Cell::endTallyHist() 
{
  for(auto est : estimators) {
      est->endHist();
  }
}

