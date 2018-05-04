/*
 Author: Blake
 Date: 11/8/17
 */

#include "Cell.h"

void Cell::setImportance(double imp)
{
  importance = imp;
}

double Cell::getImportance()
{
  return importance;
}

double Cell::distToCollision(Particle& pi)
{
  double total_xs = mat->getMacroXS(pi);
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

pair<Surf_ptr, double> Cell::closestSurface(Particle& p)
{
	Surf_ptr min_surf = nullptr;
	double min_val = std::numeric_limits<double>::max();
	point pos = p.getPos();
	point dir = p.getDir();
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
		p.printState();
		std::cerr << "ERROR: NO SURFACE FOUND" << std::endl;
		std::exit(1);
	}
	return make_pair(min_surf, min_val);
}

double Cell::distToSurface(Particle& pi)
{
  Surf_ptr close_surface;
  double dist;
  tie(close_surface,dist) = closestSurface(pi);
  return dist;
}

void Cell::recordTrackEntering() 
{
  tracks_entered++;
}

unsigned long long Cell::getTracksEntered() 
{
  return tracks_entered;
}

void Cell::recordCollision()
{
  collisions++;
}

unsigned long long Cell::getCollisions()
{
  return collisions;
}

// Estimator interface

void Cell::scoreTally(Particle& p , double xs) 
{
  if ( estimators.at( p.getGroup() - 1 )->getCollisionOrder() == p.getNCollisions() )
  {
    estimators.at( p.getGroup() - 1 )->score(p,xs);
  }
}

void Cell::endTallyHist() 
{
  for(auto est : estimators) 
  {
    est->endHist();
  }
}

std::pair< double , double > Cell::getSingleGroupTally(int group, unsigned long long nHist) 
{
  return( estimators.at(group - 1)->getScalarEstimator(nHist) );
}

std::vector< std::pair< double , double > > Cell::getTally(unsigned long long nHist) {
  std::vector< std::pair< double , double > > tallies;
  for( auto est : estimators) 
  {
    tallies.push_back( est->getScalarEstimator(nHist) );
  }
  return(tallies);
}
