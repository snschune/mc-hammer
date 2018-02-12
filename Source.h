#include <tuple>
#include <vector>
#include <memory>
#include <string>
#include "Particle.h"
#ifndef _SOURCE_HEADER_
#define _SOURCE_HEADER_
typedef std::shared_ptr<Particle> Part_ptr;

class Source {
private:
   std::string sourceName;
protected:
	unsigned int groupSample(std::vector<double> groupProbability);
public:
   Source( std::string label ) : sourceName( label ) {};
   ~Source() {} ;

   virtual std::string name() { return sourceName; };
	virtual Part_ptr    sample() = 0;
};

class setSourcePoint : public Source {
private: 
   double x0,y0,z0;
   std::vector <double> groupProbability;
public:
   setSourcePoint( std::string label, double xSource, double ySource, double zSource, std::vector<double> groupProbSet) : Source(label), x0(xSource), y0(ySource), z0(zSource), groupProbability(groupProbSet)  {};
   ~setSourcePoint() {};
   Part_ptr sample();
};

class setSourceSphere : public Source {
private: 
   double x0,y0,z0, radInner, radOuter;
   std::vector <double> groupProbability;
public:
   setSourceSphere(std::string label, double xSource, double ySource, double zSource, double radInner, double radOuter, std::vector<double> groupProbSet )
   : Source(label), x0(xSource), y0(ySource), z0(zSource), radInner(radInner), radOuter(radOuter), groupProbability(groupProbSet) {};
   ~setSourceSphere() {};
   Part_ptr sample();
};

#endif
