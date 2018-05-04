#include <cmath>
#include <vector>
#include <tuple>
#include "Random.h"
#include "Source.h"
#include "Particle.h"



unsigned int Source::groupSample(std::vector<double> groupProbability)
{
	if(groupProbability.size() > 1) {
	    double rand = Urand();
	    double c = 0;
	    for(unsigned int i = 0; i < groupProbability.size(); i++)
	    {
		    c += groupProbability[i];
		    if(c > rand)
		    {
			    return (i+1);
		    }
	    }
    }

    return(1);
}

Particle setSourcePoint::sample(){
	double pi = acos(-1.);
	
	auto group = groupSample(groupProbability);
	
	point pos = point(x0,y0,z0);
	
	double mu = 2 * Urand() - 1;
	double phi = 2 * pi*Urand();
	double omegaX=mu;
	double omegaY=sin(acos(mu))*cos(phi);
	double omegaZ=sin(acos(mu))*sin(phi);
	point dir = point(omegaX,omegaY,omegaZ);
	
    Particle p = Particle(pos, dir, group );

	return p;
}

Particle setSourceSphere::sample(){
	double pi = acos(-1.);
	//Radius of the new particle
	//double radius = pow((pow(radInner,3.0) + Urand()*(pow(radOuter,3.0)-pow(radInner,3.0))),(1. / 3.));
	//double mu = 2.0 * Urand() - 1.0;
	//double phi = 2.0 * pi*Urand();

	//double x=radius*sqrt(1-pow(mu,2.))*cos(phi)+x0;
	//double y=radius*sqrt(1-pow(mu,2.))*sin(phi)+y0;
	//double z=radius*mu+z0;
	//std::cout << "mu: " << mu << " x: " << x << " y: " << y << " z: " << z << std::endl;
	//std::cout << std::endl;
	double x;
	double y;
	double z;
	bool reject = true;
	while(reject)
	{
		x = 2*Urand()*radOuter;
		y = 2*Urand()*radOuter;
		z = 2*Urand()*radOuter;
		double dist = sqrt(x*x+y*y+z*z);
		if(dist < radOuter)
			reject = false;
	}
	auto group = groupSample(groupProbability);
	
	point pos = point(x,y,z);

        // direction sampling	
	double mu = 2 * Urand() - 1;
	double phi = 2 * pi*Urand();
	double omegaX=mu;
	double omegaY=sin(acos(mu))*cos(phi);
	double omegaZ=sin(acos(mu))*sin(phi);
	point dir = point(omegaX,omegaY,omegaZ);
	
     Particle p = Particle(pos, dir, group );

	return p;

}
