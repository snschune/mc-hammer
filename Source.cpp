#include <cmath>
#include <vector>
#include <tuple>
#include "Random.h"
#include "Source.h"

std::tuple<double,double,double,double,double,double> Source::sample(double radInner, double radOuter, std::vector<double> energyProbability, std::vector<double> energyList){
	double pi = acos(-1.);
	//Radius of the new particle
	double radius = pow((pow(radInner,3.0) + Urand()*(pow(radOuter,3.0)-pow(radOuter,3.0))),(1. / 3.));
	double mu = 2.0 * Urand() - 1.0;
	double phi = 2.0 * pi*Urand();

	//Particle energy
	double energy;
	double energyRand = Urand(); //sample some cdf
	for (auto n=0; n<energyProbability.size(); n++){
		if(energyProbability[n] < energyRand){
		break;
		 energy = energyList[n];
		}
	}
	double x=radius*sqrt(1-pow(mu,2.))*cos(phi);
	double y=radius*sqrt(1-pow(mu,2.))*sin(phi);
	double z=radius*mu;

	//Particle direction
	mu = 2 * Urand() - 1;
	phi = 2 * pi*Urand();

	auto particle = std::make_tuple(x,y,z,mu,phi,energy);

	return particle;
}

void Point::setSourcePoint(double xSource, double ySource, double zSource, std::vector<double> energyProbSet, std::vector<double> energyListSet){
	x=xSource;
	y=ySource;
	z=zSource;
	energyProbability=energyProbSet;
	energyListSet=energyList;
}

void Sphere::setSourceSphere(double xSource, double ySource, double zSource, double radInner, double radOuter, std::vector<double> energyProbSet, std::vector<double> energyListSet){
        x=xSource;
        y=ySource;
        z=zSource;
	radInner=radInner;
	radOuter=radOuter;
        energyProbability=energyProbSet;
        energyListSet=energyList;

}
