/*
 Author: ESGonzalez
 Date: 1/26/18
 */

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <vector>
#include <cmath>
#include <iostream>

#include "Point.h"

double fourDeterminant(std::vector< double > row1, std::vector< double > row2,
                       std::vector< double > row3, std::vector< double > row4 );

bool sameSign( double a, double b );

double dist(point p1 ,point p2); 

template<class T>  T vecSum(std::vector<T> vec) {
    T sum = 0;
    for(auto v : vec) {
        sum += v;
    }
    return(sum);
}

#endif
