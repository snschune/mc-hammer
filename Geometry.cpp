#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <memory> 

#include "Geometry.h"
#include "Random.h"
#include "QuadSolver.h"
#include "Point.h"
#include "Surface.h"
#include "Particle.h"

vector<R_ptr> Geometry::getCellStack(vector < R_ptr >)
{
  return vector<R_ptr>;
}

vector<s_ptr> Geometry::getSurfStack(vector < s_ptr >)
{
  return vector<s_ptr>;
}


bool Geometry:: same_sign ( int a, double b ) 
{ 
    bool sign_test;
    if ( ( a * b ) < 0 ) 
 {
   sign_test = false;
 }
    else 
 {
    sign_test = true;
 }        
    return sign_test;
}

int Geometry:: where_am_i ( P_ptr a, vector<s_ptr> &SurfaceStack, vector<R_ptr> &RegionStack )
 {
    // arguments: particle position, list of surfaces, and list of regions
    // returns:   region that particle is currently in
      
    bool my_test = false; 
    int i = 1;

    for ( auto region : RegionStack ) {
        for ( auto surf : region->surf_bndry ) {
            my_test = same_sign( surf, SurfaceStack[abs(surf)]->eval(p*) );
            if (my_test == false) {
                break;
            }
        }
        if (my_test == true) {
            break;
        }
        i += 1;
    }
    
    if (my_test == false) {
        i = 0;
    }
    
    return (i-1) ;
 } 

double Geometry:: dist2surf ( P_ptr p, vector<S_ptr> SurfaceStack ) {
    vector<double> DistStack;
    double dist;
    
    for (auto surface : SurfaceStack) {
        dist = surface->distance( (p->dir)* );
        DistStack.push_back(dist);
    }
    
    double cmin = std::numeric_limits<double>::max();
    for(unsigned int i = 0; i < DistStack.size(); i++)
    {
        if(DistStack[i] < cmin)
	{
		cmin = DistStack[i];
	}
    }
	return cmin;	
}
void Geometry:: update_pos ( P_ptr p, double dist_traveled ) {
    double x_new = p->getX() + dist_traveled * a.mu;
    double y_new = p->getY() + dist_traveled * std::cos(a.azi) * std::sqrt( 1.0 - a.mu*a.mu ); 
    double z_new = p->getZ() + dist_traveled * std::sin(a.azi) * std::sqrt( 1.0 - a.mu*a.mu );

	p->setPos(x_new,y_new,z_new);
}

void Geometry::addCell(vector<s_ptr> SurfaceStack,s_ptr newPtr)
{
  SurfaceStack.push_back(newPtr);
}

