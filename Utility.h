/*
 Author: ESGonzalez
 Date: 1/26/18
 */

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <vector>
#include <cmath>
#include <iostream>
#include <limits>

#include "Point.h"

double fourDeterminant(std::vector< double > row1, std::vector< double > row2,
                       std::vector< double > row3, std::vector< double > row4 );

bool sameSign( double a, double b );

double dist(point p1 ,point p2); 

// return largest positive root of quadratic equation with coefficients a, b, c
// if both roots negative or complex, return a really big number
double quadSolve( double a, double b, double c );

std::vector< double > pointFourVec( point pos );

template<class T>  T vecSum(std::vector<T> vec) {
    T sum = 0;
    for(auto v : vec) {
        sum += v;
    }
    return(sum);
}

template<class T>  T vecMean(std::vector<T> vec) {
    T sum = 0;
    int i = 0;
    for(auto v : vec) {
        sum += v;
        ++i;
    }
    return(sum/i);
}

#endif
