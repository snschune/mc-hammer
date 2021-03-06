/*
	Author: Blake
	Date: 11/8/17
	Req. Files: Material.cpp, Particle.h
*/

#include "Material.h"
#include "Random.h"

//Constructor
Material::Material(int ng, vector<double> total_XSi, vector<double> Sigai, vector<double> Sigsi): num_g(ng), total_XS(total_XSi), Siga(Sigai), Sigs(Sigsi) 
{
	for(int i = 0; i < ng; i++)
	{
		double rowsum = 0;
		for(int j = 0; j < ng; j++)
		{
			rowsum += Sigsi[ng*i+j];	
		}
		Sigst[i] = rowsum;
	}
}

double Material::getTotalXS(int g)
{
	return total_XS[g-1];
}

double Material::getAbsXS(int g)
{
	return Siga[g-1];
}

double Material::getScaXS(int gi, int gf)
{
	return Sigs[gi*num_g+gf-1];
}

void Material::processRxn(Part_ptr p, stack<Part_ptr> &pstack, int g)
{
	double cutoff = Siga[g-1]/total_XS[g-1];
	double rand = Urand();

	if(cutoff > rand) //particle is killed
	{
		p->kill();
	}
	else
	{
		scatter(p,g);
	}
	return;
}

void Material::scatter(Part_ptr p, int g)
{
	//select energy group to shift
	double rand = Urand();
	double cutoff = 0;
	int gf = 0;
	for(int i = (g-1)*num_g; i < g*num_g; i++)
	{
		cutoff += Sigs[i]/Sigst[g-1]; 
		if(rand < cutoff)
		{
			gf = i-(g-1)*num_g+1;
			break;	
		}
	}
	p->setGroup(gf);
	
	//change direction (isotropic scattering)
	rand = Urand();
	double mu0 = 2*Urand()-1;
	rotate(p,mu0,rand);
}

void Material::rotate(Part_ptr p, double mu0, double rand)
{
	if(mu0 == 1)
		return; //no scattering
	
	double pi = 3.1415926535897;
	
	ray r = p->getray();
	point d = r.dir;
	double u = d.x;
	double v = d.y;
	double w = d.z;
	
	double phi = 2*pi*rand; 
	double us = cos(phi);
	double vs = sin(phi);

	
	double sts = sqrt((1-mu0)*(1+mu0)); //sin(theta)
	
	us = us*sts;
	vs = vs*sts;
	
	double u2v2 = u*u+v*v;
	
	if(u2v2 == 0) //if particle is (0,0,1)
	{
		//cout << "z-direction!" << endl;
		p->setDir(us,vs,mu0);
		return;
	}
	
	double sintheta = sqrt(u2v2);
	double sinthetai = 1.0/sintheta;
	double cosphi = u*sinthetai;
	double sinphi = v*sinthetai;
	
	double u_new = u*mu0 + us*w*cosphi - vs*sinphi;
	double v_new = v*mu0 + us*w*sinphi + vs*cosphi;
	double w_new = w*mu0 - us*sintheta;
	
	p->setDir(u_new,v_new,w_new);
	return;
}
