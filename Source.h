#include <tuple>
#include <vector>
#include <memory>
#include <string>

#ifndef _SOURCE_HEADER_
#define _SOURCE_HEADER_

class Source {
private:
	std::vector < std::tuple <double, double, double, double, double, double> > ParticleInfo;
public:
	virtual std::tuple <double, double, double, double, double, double > sample(double radInner, double radOuter, std::vector<double> energyProbability, std::vector<double> energyList);
};

class Point : public Source {
private: 
   double x,y,z;
   std::vector <double> energyProbability,energyList;
public:
   double radInner=0;
   double radOuter=0;
};

class Sphere : public Source {
private: 
   double x,y,z, radInner, radOuter;
   std::vector <double> energyProbability,energyList;
};

#endif
