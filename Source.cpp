#include <cmath>
#include <vector>
#include <tuple>
#include "Random.h"
#include "Source.h"

std::tuple<double,double,double,double,double,double> source(){
	//Generate new particle
	double pi = 3.1415926535897;
	//Radius of the new particle
	double radius = pow((pow(stack.radius_inner,3) + Urand()*(pow(stack.radius_outer,3)-pow(stack.radius_inner,3))),(1 / 3));
	//Particle initial direction
	double mu = 2 * Urand() - 1;
	double phi = 2 * pi*Urand();
	//Particle energy
	double energy = Urand(); //sample some cdf
	
	double x=radius*sqrt(1-pow(mu,2))*cos(phi);
	double y=radius*sqrt(1-pow(mu,2))*sin(phi);
	double z=radius*mu;
	std::tuple<double,double,double,double,double,double> stack(x,y,z,mu,phi, energy);
	return stack;
}
