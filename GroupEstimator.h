/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 * This class is for grouping tallies to get an answer over a mesh, multiple surfaces, or multiple cells
 */

 // TODO add safety features for adding tallies to correct group, verifying number of groups
 //   in case not added in order 

#ifndef _GROUPESTIMATOR_HEADER_
#define _GROUPESTIMATOR_HEADER_

#include <iostream>
#include <memory> 

#include "Utility.h"
#include "Mesh.h"
#include "Tet.h"

using std::vector;
using std::string;

typedef std::shared_ptr<Estimator> Estimator_ptr;
typedef std::shared_ptr<surface>   Surf_ptr;
typedef std::shared_ptr<Cell>      Cell_ptr;
typedef std::shared_ptr<Mesh>      Mesh_ptr;

class GroupEstimator {
  protected:
    string name;
    vector < vector < Estimator_ptr > > estimators;
    vector < Estimator_ptr > currentGroup;
  
  public:
    GroupEstimator( string namein ) : name(namein) {};
   ~GroupEstimator() {};

    virtual vector <vector<Estimator_ptr > > getEstimators() { return(estimators); };
    //virtual vector <Estimator_ptr > getGroup(int i);
    //virtual vector <Estimator_ptr > getTally(int index);
    //virtual void addEstimatorGroup( vector< Estimator_ptr > estimatorGroup) {estimators.push_back(estimatorGroup); };
    virtual void addToGroup( Estimator_ptr estimator) { currentGroup.push_back(estimator); };
    virtual void pushGroups() {estimators.push_back(currentGroup); };
};

class MeshGroupTally: public GroupEstimator {
  private:
    Mesh_ptr mesh;
  public:
    MeshGroupTally( string name): GroupEstimator(name) {};
   ~MeshGroupTally() {}; 
};

class CellGroupTally: public GroupEstimator {
  private:
    std::vector< Cell_ptr> cells;
  public:
    CellGroupTally( string name): GroupEstimator(name) {};
   ~CellGroupTally() {}; 
    
    void addCell(Cell_ptr cell) {cells.push_back(cell); pushGroups(); };  
};

class SurfaceGroupTally: public GroupEstimator {
  private:
    std::vector< Surf_ptr> surfs;
  public:
    SurfaceGroupTally( string name): GroupEstimator(name){};
   ~SurfaceGroupTally() {}; 
};

#endif
