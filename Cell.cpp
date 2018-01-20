/*
 Author: Blake
 Date: 11/8/17
 */

#include "Cell.h"

//constructor
Cell::Cell(Mat_ptr mati, vector<pair<Surf_ptr, bool>> surfacesi ,  vector< Estimator_ptr > estimi): mat(mati) , estimators(estimi)
{
    for(auto surface: surfacesi) //learn auto
    {
        surfaces.push_back(surface);
    }

}

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
    for(auto surface: surfaces)
    {
        bool test = (surface.first->eval(pos) < 0);
        isWithin = isWithin && (test == surface.second);
    }
    return isWithin;
}

pair<Surf_ptr, double> Cell::closestSurface(Part_ptr p)
{
    Surf_ptr min_surf = nullptr;
    double min_val = std::numeric_limits<double>::max();
    point pos = p->getPos();
    point dir = p->getDir();
    for(auto bound: surfaces)
    {
        Surf_ptr cur_surf =  bound.first;
        double dist = cur_surf->distance(pos,dir);
        if(dist < min_val && dist > 0)
        {
            min_surf = cur_surf;
            min_val = dist;
        }
    }
    if(min_surf == nullptr)
    {
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

std::pair< double , double > Cell::getSingleGroupTally(int group) {
    return( estimators.at(group - 1)->getScalarEstimator() );
}

std::vector< std::pair< double , double > > Cell::getTally() {
    std::vector< std::pair< double , double > > tallies;
    for( auto est : estimators) {
        tallies.push_back( est->getScalarEstimator() );
    }

    return(tallies);
}
