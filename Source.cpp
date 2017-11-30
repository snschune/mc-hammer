#include <cmath>
#include <vector>
#include <tuple>
#include "Random.h"
#include "Source.h"

std::tuple<double,double,double,double,double,double> Source::source(){
	//Generate new particle
	double radius_inner=1;
	double radius_outer=2;
	std::vector<double> energy_sample{0,1};
	std::vector<double> energyList{3};
	double pi = 3.1415926535897;
	//Radius of the new particle
	double radius = pow((pow(radius_inner,3) + Urand()*(pow(radius_outer,3)-pow(radius_inner,3))),(1 / 3));
	double mu = 2 * Urand() - 1;
	double phi = 2 * pi*Urand();
	//Particle energy
	double energyRand = Urand(); //sample some cdf
	int n;
	for (n=0; n<energy_sample.size(); n++){
		if(energy_sample[n] < energyRand){
		break;
		}
	}
	double energy = energyList[n];
	double x=radius*sqrt(1-pow(mu,2))*cos(phi);
	double y=radius*sqrt(1-pow(mu,2))*sin(phi);
	double z=radius*mu;
	double mu = 2 * Urand() - 1;
	double phi = 2 * pi*Urand();
	std::tuple<double,double,double,double,double,double> stack(x,y,z,mu,phi, energy);
	return stack;
}
