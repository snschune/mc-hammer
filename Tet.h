//
//  Tet.h
//  Reader
//
//  Created by Rob Fonti on 1/10/18.
//  Copyright © 2018 Rob Fonti. All rights reserved.
//

#ifndef Tet_h
#define Tet_h

#include <vector>
#include <iostream>
#include <memory>
#include "Point.h"
#include "Utility.h"
#include "Estimator.h"
#include "Constants.h"

//Tet Class includes 4 points which define a given tetrahedra
//Tets have ID's associated with them.

typedef std::shared_ptr<point>     point_ptr;
typedef std::shared_ptr<Estimator> Estimator_ptr;
typedef std::shared_ptr<Particle>  Part_ptr; 

using std::vector;

class Tet
{
private:
    int    TetID;
    double d0; //sign of the D0 deternminant (false = negative, true = positive)
    std::string tetName;
    vector< double > vert1;
    vector< double > vert2;
    vector< double > vert3;
    vector< double > vert4;
	vector< double > A1, A2, A3, A4;; //3x3 determinants precomp

    // Estimators
    vector< Estimator_ptr > estimators;
    
public:
    
    Tet( std::string label, point p );

    std::string name() { return tetName; };
    
    void setVertices( std::shared_ptr<point> p1, std::shared_ptr<point> p2,
                      std::shared_ptr<point> p3, std::shared_ptr<point> p4 );
    
    void addVertice( std::shared_ptr< point > inVertice );
    void addEstimator( Estimator_ptr newEstimator );
    void setID( int tetID );

    int              getID();
    vector< double > getVert1();
    vector< double > getVert2();
    vector< double > getVert3();
    vector< double > getVert4();
    vector< double > getCentroid();
    std::vector< Estimator_ptr > getEstimators() { return estimators; };
    
    bool amIHere( const std::vector< double >& testPoint );

    // Estimator interface
    void scoreTally(Particle& p , double xs); 
    void endTallyHist();
    std::pair< double , double > getSingleGroupTally(int group, unsigned long long nHist);
    vector< std::pair< double , double > > getTally(unsigned long long nHist);
  
};

#endif /* Tet_h */
