#ifndef Geometry_h
#define Geometry_h


#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <memory> 

#include "Random.h"
#include "QuadSolver.h"
#include "Point.h"
#include "Cell.h"
#include "Surface.h"

using std::vector;

class Geometry
{
  private:
   vector< Cell > VectOfCells;
   vector<R_ptr> CellStack;
   vector<s_ptr> SurfaceStack;

  public:
    bool same_sign(int a, double b);
    int where_am_i(P_ptr a, vector<s_ptr> &SurfaceStack, vector<R_ptr> &CellStack);
    double dist2surf(P_ptr p, vector<S_ptr> SurfaceStack);
    void update_pos(P_ptr p, double dist_traveled);
    vector<s_ptr> getSurfStack(vector < s_ptr >;
    vector<R_ptr> getCellStack(vector < R_ptr >;
    void addCell(vector<s_ptr> SurfaceStack);







#endif
