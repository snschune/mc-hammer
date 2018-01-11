#include <cmath>
#include <vector>
#include <tuple>
#include "Random.h"
#include "Source.h"
#include "Particle.h"

double Source::groupSample(std::vector<double> groupProbability, std::vector<double> groupList){
	double group;
	double groupRand = Urand(); //sample some cdf
	for (auto n=0; n<groupProbability.size(); n++){
		if(groupProbability[n] < groupRand){
		break;
		 group = groupList[n];
		}
	}
	return group;
}

Particle setSourcePoint::sample(){
	Particle particleNew;
	double pi = acos(-1.);
	
	group = groupSample(groupProbability, groupList);
	
	point pos = point(x0,y0,z0);
	
	mu = 2 * Urand() - 1;
	phi = 2 * pi*Urand();
	double omegaX=mu;
	double OmegaY=sin(acos(mu))*cos(phi);
	double OmegaZ=sin(acos(mu))*sin(phi);
	point dir = point(omegaX,omegaY,omegaZ);
	
	particleNew.Particle(pos,dir,1,group);

	return particleNew;
}

Particle setSourceSphere::sample(){
	Particle particleNew;
	double pi = acos(-1.);
	//Radius of the new particle
	double radius = pow((pow(radInner,3.0) + Urand()*(pow(radOuter,3.0)-pow(radOuter,3.0))),(1. / 3.));
	double mu = 2.0 * Urand() - 1.0;
	double phi = 2.0 * pi*Urand();

	double x=radius*sqrt(1-pow(mu,2.))*cos(phi)+x0;
	double y=radius*sqrt(1-pow(mu,2.))*sin(phi)+y0;
	double z=radius*mu+z0;

	group = groupSample(groupProbability, groupList);
	
	point pos = point(xSource,ySource,zSource);
	
	mu = 2 * Urand() - 1;
	phi = 2 * pi*Urand();
	double omegaX=mu;
	double OmegaY=sin(acos(mu))*cos(phi);
	double OmegaZ=sin(acos(mu))*sin(phi);
	point dir = point(omegaX,omegaY,omegaZ);
	
	particleNew.Particle(pos,dir,1,group);

	return particleNew;

}
