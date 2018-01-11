/*
	Author: Blake
	Date: 11/8/17
	Req. Files: Material.cpp, Particle.h
*/

#include "Material.h"
#include "Random.h"
#include <iostream>

using std::cout;
using std::endl;
//Constructor
Material::Material(int ng, vector<double> total_XSi, vector<double> Sigai, vector<vector<double>> Sigsi): num_g(ng), total_XS(total_XSi), Siga(Sigai), Sigs(Sigsi) 
{
	vector<double> gsvec; //group sum vector
	for(int i = 0; i < ng; i++)
	{
		double rowsum = 0;
		gsvec = Sigs[i];
		for(int j = 0; j < ng; j++)
		{
			rowsum += gsvec[j];
		}
		Sigst.push_back(rowsum);
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
	vector<double> cScat = Sigs[gi];
	return cScat[gf];
}

void Material::processRxn(Part_ptr p, stack<Part_ptr> &pstack, int g)
{
	double cutoff = Siga[g-1]/total_XS[g-1];
	double rand = Urand();

	if(cutoff > rand) //particle is killed
	{
		//cout << "Absorption!" << endl;
		p->kill();
		//cout << "after: " << endl;
		//p->printState();
	}
	else
	{
		//cout << "Scatter!" << endl;
		scatter(p,g);
		//cout << "after: " << endl;
		//p->printState();
	}
	return;
}

void Material::scatter(Part_ptr p, int g)
{
	//select energy group to shift
	double rand = Urand();
	double cutoff = 0;
	int gf = 0;
	vector<double> curSigs = Sigs[g-1];
	for(int i = 0; i < num_g; i++)
	{
		cutoff += curSigs[i]/Sigst[g-1]; 
		if(rand < cutoff)
		{
			gf = i+1;
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
	//cout << "Rotation! mu = " << mu0 << " rand = " << rand << endl;
	if(mu0 == 1)
		return; //no scattering
	
	double pi = 3.1415926535897;
	
	point d = p->getDir();
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
