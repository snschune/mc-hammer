/*
 * Author: Kyle Beyer
 * Last Updated: 11/30/17
 *
 * This class can:
 *  measure the path length density of particles in a 3D mesh
 *  tally the path length density of particles in a cell
 *  tally the number of particles crossing a surface
 */

//TODO get functions, with gettally returning an uncertainty as well

//TODO add energy dependence
//TODO add material specificity
//TODO add reaction type specificity

#ifndef _ESTIMATOR_HEADER_
#define _ESTIMATOR_HEADER_

#include "Point.h"
#include "Particle.h"  
#include "Surface.h"
#include "Cell.h"
#include "Material.h"
#include "RxnLog.h"

using std::vector;
using std::string;

typedef std::shared_ptr<Particle>  Part_ptr; //found in Particle.h -> Material.h
typedef std::shared_ptr<Material>  Mat_ptr;
typedef std::shared_ptr<surface>   Surf_ptr;
typedef std::shared_ptr<Cell>      Cell_ptr;
typedef std::shared_ptr<rxnLog>     log_ptr;

class estimator {
  private:
    std::string estimator_name;
    std::string estimator_type;
    // energy binning
    // material

  protected:
    double dist(point p1 , point p2);

  public:
     estimator( string comment , string type) : estimator_name(comment) , estimator_type(type) {};
    ~estimator() {};
    
    virtual std::string name() { return estimator_name; };
    virtual std::string type() { return estimator_type; };

    virtual void update(Part_ptr pi , Part_ptr pf , log_ptr rxns );
};

//TODO create mesh class, use 1D array and lookup functions

class meshTally : public estimator {
  private:
      vector < vector < vector < double > > > mesh;
  public:
     meshTally(string comment, string type , vector<int> numBins); 
    ~meshTally() {};

     void update(Part_ptr pi , Part_ptr pf , log_ptr rxns);
};

class surfaceTally : public estimator {
    private:
        double   tally;
        Surf_ptr surf;
    public:
         surfaceTally(string comment , string type, Surf_ptr surfi );
        ~surfaceTally() {};
        
        void update(Part_ptr pi , Part_ptr pf , log_ptr rxns );
};

class cellTally : public estimator {
    private:
        double     tally;
        Cell_ptr   cell;
    public:
         cellTally(string comment , string type , Cell_ptr celli);
        ~cellTally() {};

         void update(Part_ptr pi , Part_ptr pf , log_ptr rxns);
};

#endif
