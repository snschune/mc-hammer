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
#include "EstimatorCollection.h"

using std::vector;
using std::stack;
using std::pair;
using std::time;
using std::cout;
using std::endl;

typedef std::shared_ptr<Particle>            Part_ptr; //found in Particle.h -> Material.h
typedef std::shared_ptr<Material>            Mat_ptr;
typedef std::shared_ptr<surface>             Surf_ptr;
typedef std::shared_ptr<EstimatorCollection> EstCol_ptr;

class Cell
//Region in space, bounded by surfaces/
//NOTE: create all other objects before constructing a cell, or it leads to a pain in the butt
{
private:
    std::string cellName;
    Mat_ptr mat; //material properties within cell
    vector< pair< Surf_ptr, bool > > surfacePairs;
    
    // EstimatorCollections
    vector< EstCol_ptr > estimators;
   
public: 
  //Constructor:
  Cell( std::string label ) : cellName( label ) {};
 ~Cell() {};
    
  void    addSurfacePair ( std::pair< Surf_ptr, bool > newSurfacePair ) { surfacePairs.push_back( newSurfacePair ); };
  void    addEstimator   ( EstCol_ptr newEstimator                    ) { estimators.push_back( newEstimator );     };
  void    setMaterial    ( Mat_ptr newMaterial                        ) { mat = newMaterial;                        };

  Mat_ptr                   getMat()        { return mat;        };
  std::string               name()          { return cellName;   };
  std::vector< EstCol_ptr > getEstimators() { return estimators; };
  
  //operations
  double                 distToSurface   ( Part_ptr pi );
  double                 distToCollision ( int group   );
  pair<Surf_ptr, double> closestSurface  ( Part_ptr p  );
  
  bool amIHere( const point& pos );

  // Estimator interface
  void scoreTally(Part_ptr p , double xs); 
  void endTallyHist();
  // TODO get Tally output
};
#endif 
