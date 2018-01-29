//
//  Tet.cpp
//  Reader
//
//  Created by Rob Fonti on 1/10/18.
//  Copyright © 2018 Rob Fonti. All rights reserved.
//

#include "Tet.h"

//default cstr initializes a tet of zero size

Tet::Tet( point p ) {}

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
    vert1 = Tet::pointFourVec(*p1);
    vert2 = Tet::pointFourVec(*p2);
    vert3 = Tet::pointFourVec(*p3);
    vert4 = Tet::pointFourVec(*p4);
    
    d0 = -1.0; //fourDeterminant( vert1, vert2, vert3, vert4 );
    
    if (d0 == 0.0)
    {
        std::cout << "ERROR: The verticies for tet " << Tet::getID() << "are co-planar." << std::endl;
    }
}

int Tet::getID()
{
    return TetID;
}

std::vector< double > Tet::pointFourVec( point p )
{
    // Takes a point and returns a vector (length 4) with a "1.0" appended
    std::vector< double > fourVec;
    
    fourVec.push_back( p.x );
    fourVec.push_back( p.y );
    fourVec.push_back( p.z );
    fourVec.push_back( 1.0 );
    
    return fourVec;
}

bool Tet::amIHere( point P )
{
    std::vector< double > testPoint = Tet::pointFourVec( P );
    bool isWithin = false;
    double tempDet;
    
    while ( !isWithin ) // Algorithm to determine if a point is in a given tet
    {
        // Compute determinant and break loop if sign is not the same as D0
        tempDet = fourDeterminant( testPoint, vert2, vert3, vert4 ); //D1
        if (!sameSign(d0,tempDet)) { break; }
        
        tempDet = fourDeterminant( vert1, testPoint, vert3, vert4 ); //D2
        if (!sameSign(d0,tempDet)) { break; }
        
        tempDet = fourDeterminant( vert1, vert2, testPoint, vert4 ); //D3
        if (!sameSign(d0,tempDet)) { break; }
        
        tempDet = fourDeterminant( vert1, vert2, vert3, testPoint ); //D4
        if (!sameSign(d0,tempDet)) { break; }
        
        isWithin = true; // If none of the tests failed, the point is within the tet
    }
    
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
