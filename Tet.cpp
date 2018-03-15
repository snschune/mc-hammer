//
//  Tet.cpp
//  Reader
//
//  Created by Rob Fonti on 1/10/18.
//  Copyright © 2018 Rob Fonti. All rights reserved.
//

#include "Tet.h"

using namespace Utility;

//default cstr initializes a tet of zero size

Tet::Tet( std::string label, point p ): tetName( label ) {}

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

vector< double > Tet::getCentroid()
{
	vector< double > centroid;
	centroid.push_back((vert1[0]+vert2[0]+vert3[0]+vert4[0])/4);
	centroid.push_back((vert1[1]+vert2[1]+vert3[1]+vert4[1])/4);
	centroid.push_back((vert1[2]+vert2[2]+vert3[2]+vert4[2])/4);
	
	return centroid;
}
void Tet::setVertices(std::shared_ptr<point> p1, std::shared_ptr<point> p2,
                      std::shared_ptr<point> p3, std::shared_ptr<point> p4)
{
    vert1 = pointFourVec(*p1);
    vert2 = pointFourVec(*p2);
    vert3 = pointFourVec(*p3);
    vert4 = pointFourVec(*p4);
    
    d0 = fourDeterminant( vert1, vert2, vert3, vert4 );
    
	
	vector< double >  xy1  = {vert1[0], vert1[1],        1};
	vector< double >  xz1  = {vert1[0], vert1[2],        1};
	vector< double >  yz1  = {vert1[1], vert1[2],        1};
	vector< double >  xyz1 = {vert1[0], vert1[1], vert1[2]};                                   
	vector< double >  xy2  = {vert2[0], vert2[1],        1};
	vector< double >  xz2  = {vert2[0], vert2[2],        1};
	vector< double >  yz2  = {vert2[1], vert2[2],        1};
	vector< double > xyz2  = {vert2[0], vert2[1], vert2[2]};                                   
	vector< double >  xy3  = {vert3[0], vert3[1],        1};
	vector< double >  xz3  = {vert3[0], vert3[2],        1};
	vector< double >  yz3  = {vert3[1], vert3[2],        1};
	vector< double > xyz3  = {vert3[0], vert3[1], vert3[2]};                                   
	vector< double >  xy4  = {vert4[0], vert4[1],        1};
	vector< double >  xz4  = {vert4[0], vert4[2],        1};
	vector< double >  yz4  = {vert4[1], vert4[2],        1};
	vector< double > xyz4  = {vert4[0], vert4[1], vert4[2]};
	
	double A11 =    threeDeterminant( yz2, yz3, yz4);
	double A12 = -1*threeDeterminant( xz2, xz3, xz4);
	double A13 =    threeDeterminant( xy2, xy3, xy4);
	double A14 = -1*threeDeterminant(xyz2,xyz3,xyz4);
	
	double A21 = -1*threeDeterminant( yz1, yz3, yz4);
	double A22 =    threeDeterminant( xz1, xz3, xz4);
	double A23 = -1*threeDeterminant( xy1, xy3, xy4);
	double A24 =    threeDeterminant(xyz1,xyz3,xyz4);
	
	double A31 =    threeDeterminant( yz1, yz2, yz4);
	double A32 = -1*threeDeterminant( xz1, xz2, xz4);
	double A33 =    threeDeterminant( xy1, xy2, xy4);
	double A34 = -1*threeDeterminant(xyz1,xyz2,xyz4);
	
	double A41 = -1*threeDeterminant( yz1, yz2, yz3);
	double A42 =    threeDeterminant( xz1, xz2, xz3);
	double A43 = -1*threeDeterminant( xy1, xy2, xy3);
	double A44 =    threeDeterminant(xyz1,xyz2,xyz3);
	
	A1.push_back(A11);
	A1.push_back(A12);
	A1.push_back(A13);
	A1.push_back(A14);
	
	A2.push_back(A21);
	A2.push_back(A22);
	A2.push_back(A23);
	A2.push_back(A24);
	
	A3.push_back(A31);
	A3.push_back(A32);
	A3.push_back(A33);
	A3.push_back(A34);
	              
	A4.push_back(A41);
	A4.push_back(A42);
	A4.push_back(A43);
	A4.push_back(A44);
	
	
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

bool Tet::amIHere( const std::vector< double >& testPoint )
{
    bool isWithin = true;
    double tempDet;

    // Compute determinant and return 'false' if sign is not the same as D0
    tempDet = testPoint[0]*A1[0] + testPoint[1]*A1[1] + testPoint[2]*A1[2] + A1[3]; //D1
    if (!sameSign(d0,tempDet)) { isWithin = false; return isWithin; }
    
    tempDet = testPoint[0]*A2[0] + testPoint[1]*A2[1] + testPoint[2]*A2[2] + A2[3]; //D2
    if (!sameSign(d0,tempDet)) { isWithin = false; return isWithin; }
        
    tempDet = testPoint[0]*A3[0] + testPoint[1]*A3[1] + testPoint[2]*A3[2] + A3[3]; //D2
    if (!sameSign(d0,tempDet)) { isWithin = false; return isWithin; }
        
    tempDet = testPoint[0]*A4[0] + testPoint[1]*A4[1] + testPoint[2]*A4[2] + A4[3]; //D2
    if (!sameSign(d0,tempDet)) { isWithin = false; return isWithin; }
    
    return isWithin;
}

// Estimator interface

void Tet::scoreTally(Part_ptr p , double xs) {
  // for each EstimatorCollection
    // for each attribute
      // get the index of the Estimator to score
      // score the estimator
}

void Tet::endTallyHist() {
    for(auto est : estimators) {
        est->endHist();
    }
}


void Tet::addEstimator( EstCol_ptr newEstimator ) {
	estimators.push_back( newEstimator );
}
