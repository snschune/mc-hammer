/*
 Author: ESGonzalez
 Date: 1/26/18
 */

#include "Utility.h"

double fourDeterminant(std::vector< double > row1, std::vector< double > row2,
                                std::vector< double > row3, std::vector< double > row4)
{ // This function takes in four vector doubles and returns the determinant
    double det;
    det = 1.0; // The algorithm for calculating the determinant will go here
    return det;
}

bool sameSign( double a, double b )
{
    bool signTest;
    if ( a*b < 0.0 )
    {
        signTest = false;
    }
    else
    {
        signTest = true;
    }
    
    return signTest;
}
