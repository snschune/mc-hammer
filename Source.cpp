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

Particle setSourcePoint::sample(){
//	Particle particleNew;
	double pi = acos(-1.);
	
	auto group = groupSample(groupProbability);
	
	point pos = point(x0,y0,z0);
	
	double mu = 2 * Urand() - 1;
	double phi = 2 * pi*Urand();
	double omegaX=mu;
	double omegaY=sin(acos(mu))*cos(phi);
	double omegaZ=sin(acos(mu))*sin(phi);
	point dir = point(omegaX,omegaY,omegaZ);
	
//	particleNew.Particle(pos,dir,1,group);

        Particle particleNew( pos, dir, 1, group );

	return particleNew;
}

Particle setSourceSphere::sample(){
	double pi = acos(-1.);
	//Radius of the new particle
	double radius = pow((pow(radInner,3.0) + Urand()*(pow(radOuter,3.0)-pow(radOuter,3.0))),(1. / 3.));
	double mu = 2.0 * Urand() - 1.0;
	double phi = 2.0 * pi*Urand();

	double x=radius*sqrt(1-pow(mu,2.))*cos(phi)+x0;
	double y=radius*sqrt(1-pow(mu,2.))*sin(phi)+y0;
	double z=radius*mu+z0;

	auto group = groupSample(groupProbability);
	
	point pos = point(x,y,z);

        // direction sampling	
	mu = 2 * Urand() - 1;
	phi = 2 * pi*Urand();
	double omegaX=mu;
	double omegaY=sin(acos(mu))*cos(phi);
	double omegaZ=sin(acos(mu))*sin(phi);
	point dir = point(omegaX,omegaY,omegaZ);
	
        Particle particleNew( pos, dir, 1, group );

	return particleNew;

}
