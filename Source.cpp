#include <cmath>
#include <vector>
#include <tuple>
#include "Random.h"
#include "Source.h"
#include "Particle.h"



unsigned int Source::groupSample(std::vector<double> groupProbability){
	double group;
	double groupRand = Urand(); //sample some cdf
	for (auto n=0; n<groupProbability.size(); n++){
		if (groupProbability[n] < groupRand){
			return n;
		}
	}
	//return group;
	//TODO: put in error code
}

Part_ptr setSourcePoint::sample(){
	double pi = acos(-1.);
	
	auto group = groupSample(groupProbability);
	
	point pos = point(x0,y0,z0);
	
	double mu = 2 * Urand() - 1;
	double phi = 2 * pi*Urand();
	double omegaX=mu;
	double omegaY=sin(acos(mu))*cos(phi);
	double omegaZ=sin(acos(mu))*sin(phi);
	point dir = point(omegaX,omegaY,omegaZ);
	
     Part_ptr p = std::make_shared<Particle>(pos, dir, group );

	return p;
}

Part_ptr setSourceSphere::sample(){
	double pi = acos(-1.);
	//Radius of the new particle
	double radius = pow((pow(radInner,3.0) + Urand()*(pow(radOuter,3.0)-pow(radInner,3.0))),(1. / 3.));
	double mu = 2.0 * Urand() - 1.0;
	double phi = 2.0 * pi*Urand();

	double x=radius*sqrt(1-pow(mu,2.))*cos(phi)+x0;
	double y=radius*sqrt(1-pow(mu,2.))*sin(phi)+y0;
	double z=radius*mu+z0;
	//std::cout << "mu: " << mu << " x: " << x << " y: " << y << " z: " << z << std::endl;
	//std::cout << std::endl;
	auto group = groupSample(groupProbability);
	
	point pos = point(x,y,z);

        // direction sampling	
	mu = 2 * Urand() - 1;
	phi = 2 * pi*Urand();
	double omegaX=mu;
	double omegaY=sin(acos(mu))*cos(phi);
	double omegaZ=sin(acos(mu))*sin(phi);
	point dir = point(omegaX,omegaY,omegaZ);
	
     Part_ptr p = std::make_shared<Particle>(pos, dir, group );

	return p;

}
