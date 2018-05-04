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
    
  double importance;
  unsigned long long tracks_entered;
  unsigned long long collisions;
  
  // Estimators
  vector< Estimator_ptr > estimators;
   
public: 
  //Constructor:
  Cell( std::string label ) : cellName( label ), importance(1.0), tracks_entered(0), collisions(0) {};
 ~Cell() {};
    
  void    addSurfacePair ( std::pair< Surf_ptr, bool > newSurfacePair ) { surfacePairs.push_back( newSurfacePair ); };
  void    addEstimator   ( Estimator_ptr newEstimator                 ) { estimators.push_back( newEstimator );     };
  void    setMaterial    ( Mat_ptr newMaterial                        ) { mat = newMaterial;                        };
  Mat_ptr                      getMat()        { return mat;        };
  std::string                  name()          { return cellName;   };
  std::vector< Estimator_ptr > getEstimators() { return estimators; };

  //operations
  void   setImportance( double imp );
  double getImportance();

  double                 distToSurface   ( Particle& pi );
  double                 distToCollision ( Particle& pi );
  pair<Surf_ptr, double> closestSurface  ( Particle& p  );
  
  bool amIHere( const point& pos );

  void recordTrackEntering();
  unsigned long long getTracksEntered();

  void recordCollision();
  unsigned long long getCollisions();

  // Estimator interface
  void scoreTally(Particle& p , double xs); 
  void endTallyHist();
  std::pair< double , double > getSingleGroupTally(int group, unsigned long long nHist);
  std::vector< std::pair< double , double > > getTally(unsigned long long nHist);
};
#endif 
