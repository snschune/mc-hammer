/*
 Author: Blake
 Date: 11/8/17
 */

#include "Cell.h"

//constructor
Cell::Cell( std::string label ): cellName(label) {}

//functions
//vector<Surf_ptr> Cell::getSurfaces()
//{
//    return surfaces;
//}
//vector<bool> Cell::getInside()
//{
//return inside;
//}

Mat_ptr Cell::getMat()
{
    return mat;
}

void Cell::addSurfacePair( std::pair< Surf_ptr, bool > newSurfacePair ) {
    surfacePairs.push_back( newSurfacePair );
}

void Cell::addEstimator( Estimator_ptr newEstimator ) {
    estimators.push_back( newEstimator );
}

void Cell::setMaterial( Mat_ptr newMaterial ) {
    mat = newMaterial;
}



double Cell::distToCollision(Part_ptr pi)
{
    int group = pi->getGroup();
    double total_xs = mat->getTotalXS(group);
    double dist = -log(Urand())/total_xs;
    return dist;
}



void Cell::processRxn(Part_ptr p, stack<Part_ptr> &pstack)
//a collision has occurred, what happens now?
{
    mat->processRxn(p, pstack, p->getGroup());
    return;
}

bool Cell::amIHere(point pos)
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
			min_val = dist;
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

void Cell::scoreTally(Part_ptr p , double xs) {
    estimators.at( p->getGroup() - 1 )->score(xs);
}

void Cell::endTallyHist() {
    for(auto est : estimators) {
        est->endHist();
    }
}

std::pair< double , double > Cell::getSingleGroupTally(int group, unsigned long long nHist) {
    return( estimators.at(group - 1)->getScalarEstimator(nHist) );
}

std::vector< std::pair< double , double > > Cell::getTally(unsigned long long nHist) {
    std::vector< std::pair< double , double > > tallies;
    for( auto est : estimators) {
        tallies.push_back( est->getScalarEstimator(nHist) );
    }
    return(tallies);
}
