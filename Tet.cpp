//
//  Tet.cpp
//  Reader
//
//  Created by Rob Fonti on 1/10/18.
//  Copyright © 2018 Rob Fonti. All rights reserved.
//

#include "Tet.h"

//default cstr initializes a tet of zero size

Tet::Tet( point p , vector <Estimator_ptr> estimatorsin): estimators(estimatorsin) {}

std::vector< double > Tet::getVert1()
{
    return vert1;
}

std::vector< double > Tet::getVert2()
{
    return vert2;
}

std::vector< double > Tet::getVert3()
{
    return vert3;
}

std::vector< double > Tet::getVert4()
{
    return vert4;
}

void Tet::setVertices(std::shared_ptr<point> p1, std::shared_ptr<point> p2,
                      std::shared_ptr<point> p3, std::shared_ptr<point> p4)
{
    vert1 = pointFourVec(*p1);
    vert2 = pointFourVec(*p2);
    vert3 = pointFourVec(*p3);
    vert4 = pointFourVec(*p4);
    
    d0 = fourDeterminant( vert1, vert2, vert3, vert4 );
    
    if (d0 == 0.0)
    {
        std::cout << "ERROR: The verticies for tet " << Tet::getID() << "are co-planar." << std::endl;
    }
}

void Tet::setID( int tetID )
{
    TetID = tetID;
}

int Tet::getID()
{
    return TetID;
}

bool Tet::amIHere( std::vector< double > testPoint )
{
    bool isWithin = true;
    double tempDet;

    // Compute determinant and return 'false' if sign is not the same as D0
    tempDet = fourDeterminant( testPoint, vert2, vert3, vert4 ); //D1
    if (!sameSign(d0,tempDet)) { isWithin = false; return isWithin; }
    
    tempDet = fourDeterminant( vert1, testPoint, vert3, vert4 ); //D2
    if (!sameSign(d0,tempDet)) { isWithin = false; return isWithin; }
        
    tempDet = fourDeterminant( vert1, vert2, testPoint, vert4 ); //D3
    if (!sameSign(d0,tempDet)) { isWithin = false; return isWithin; }
        
    tempDet = fourDeterminant( vert1, vert2, vert3, testPoint ); //D4
    if (!sameSign(d0,tempDet)) { isWithin = false; return isWithin; }
    
    return isWithin;
}

// Estimator interface

void Tet::scoreTally(Part_ptr p , double xs) {
    estimators.at( p->getGroup() - 1 )->score(xs);
}

void Tet::endTallyHist() {
    for(auto est : estimators) {
        est->endHist();
    }
}

std::pair< double , double > Tet::getSingleGroupTally(int group) {
    return( estimators.at(group - 1)->getScalarEstimator() );
}

std::vector< std::pair< double , double > > Tet::getTally() {
    std::vector< std::pair< double , double > > tallies;
    for( auto est : estimators) {
        tallies.push_back( est->getScalarEstimator() );
    }

    return(tallies);
}
