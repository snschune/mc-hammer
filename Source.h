#include <tuple>
#include <vector>
#include <memory>
#include <string>
#include "Particle.h"
#ifndef _SOURCE_HEADER_
#define _SOURCE_HEADER_

class Source {
private:
	double groupSample(std::vector<double> groupProbability, std::vector<double> groupList);
public:
	virtual Particle sample();
};

class setSourcePoint : public Source {
private: 
   double x0,y0,z0;
   std::vector <double> groupProbability,groupList;
public:
   setSourcePoint(double xSource, double ySource, double zSource, std::vector<double> groupProbSet, std::vector<double> groupListSet) : x0(xSource), y0(ySource), z0(zSource), groupProbability(groupProbSet), groupList(groupListSet) {};
   Particle sample();
};

class setSourceSphere : public Source {
private: 
   double x0,y0,z0, radInner, radOuter;
   std::vector <double> groupProbability,groupList;
public:
   setSourceSphere(double xSource, double ySource, double zSource, double radInner, double radOuter, std::vector<double> groupProbSet, std::vector<double> groupListSet)
   : x0(xSource), y0(ySource), z0(zSource), radInner(radInner), radOuter(radOuter), groupProbability(groupProbSet), groupList(groupListSet) {};
   Particle sample();
};

#endif
