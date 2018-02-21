/*
 Author: Blake
 Date: 11/8/17
 Req. Files: Cell.cpp, Material.h, Surface.h, Random.h
 */

#ifndef __CELL_H__
#define __CELL_H__

#include <iostream>
#include <memory>
#include <stack>
#include <limits>
#include <utility>
#include <tuple>
#include <vector>
#include <ctime>

#include "Material.h"
#include "Surface.h"
#include "Random.h"
#include "Particle.h"
#include "Geometry.h"
#include "Estimator.h"

using std::vector;
using std::stack;
using std::pair;
using std::time;
using std::cout;
using std::endl;

typedef std::shared_ptr<Particle>  Part_ptr; //found in Particle.h -> Material.h
typedef std::shared_ptr<Material>  Mat_ptr;
typedef std::shared_ptr<surface>   Surf_ptr;
typedef std::shared_ptr<Estimator> Estimator_ptr;

class Cell
//Region in space, bounded by surfaces/
//NOTE: create all other objects before constructing a cell, or it leads to a pain in the butt
{
private:
    std::string cellName;
    Mat_ptr mat; //material properties within cell
    vector<pair<Surf_ptr, bool>> surfacePairs;
    
    // Estimators
    vector< Estimator_ptr > estimators;
   
public: 
  //Constructor:
  Cell( std::string label ) : cellName( label ) {};
 ~Cell() {};
  
  Mat_ptr getMat();  
  void    addSurfacePair ( std::pair< Surf_ptr, bool > newSurfacePair );
  void    addEstimator   ( Estimator_ptr newEstimator                 );
  void    setMaterial    ( Mat_ptr newMaterial                        );
  std::string                  name()          { return cellName;   };
  std::vector< Estimator_ptr > getEstimators() { return estimators; };
  
  //operations
  double                 distToSurface   ( Part_ptr pi );
  double                 distToCollision ( Part_ptr pi );
  pair<Surf_ptr, double> closestSurface  ( Part_ptr p  );
  
  bool amIHere( point pos );

  // Estimator interface
  void scoreTally(Part_ptr p , double xs); 
  void endTallyHist();
  std::pair< double , double > getSingleGroupTally(int group, unsigned long long nHist);
  std::vector< std::pair< double , double > > getTally(unsigned long long nHist);
};
#endif 
