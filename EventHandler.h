/*
 * Author: Kyle Beyer

 *
 * This class handles estimator scoring at collision and surface crossing events. 
 * The base class is an abstract interface, and the derived classes correspond to (and are explicitly called at) the mentioned events
 * The class handles determination of which tally types to populate, given a geometric object (cell, surface, unstructured mesh element)
 * as well as determines the correct multipliers to score. 
 * It acts as a high level interface between transport and EstimatorCollection
 */

#ifndef _EVENTHANDLER_HEADER_
#define _EVENTHANDLER_HEADER_

#include <iostream>
#include <vector>
#include <memory> 

#include "Cell.h"
#include "Mesh.h"
#include "Surface.h"
#include "Particle.h"
#include "EstimatorCollection.h"

using std::vector;
using std::string;

typedef std::shared_ptr< Cell                >  Cell_ptr;
typedef std::shared_ptr< Material            >  Mat_ptr;
typedef std::shared_ptr< surface             >  Surf_ptr;
typedef std::shared_ptr< Nuclide             >  Nuclide_ptr;
typedef std::shared_ptr< Reaction            >  Reaction_ptr;
typedef std::shared_ptr< Particle            >  Part_ptr;
typedef std::shared_ptr< Point               >  Point_ptr;
typedef std::shared_ptr< Tet                 > Tet_ptr;
typedef std::shared_ptr< EstimatorCollection >  EstCol_ptr;


class EventHandler {

  protected:
    // enumeration binding tally type to integers
    static const enum
  
  public:
    EventHandler() {};
   ~EventHandler() {};

    double getMultiplier( int EstimatorType ) = 0; 
    void   score(Point_ptr p0 , Part_ptr particle)  = 0;

};

class CollisionHandler : public EventHandler {
  private:
    Cell_ptr currentCell;
    Tet_ptr  currentTet;
   
  public:
    CollisionHandler() {};
   ~CollisionHandler() {};

   void setCurrentCell( Cell_ptr cell );
   void setCurrentTet( Tet_ptr tet );

};


class SurfaceCrossingHandler : public EventHandler {
  private:
    Surf_ptr surfaceCrossed;
    Cell_ptr cellLeft;

  public:
    SurfaceCrossingHandler() {};
   ~SurfaceCrossingHandler() {};

    void setSurfaceCrossed( Surf_ptr surf );
    void setCellLeft( Cell_ptr cell );

};

#endif
