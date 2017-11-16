/*
	Author: Blake
	Date: 11/8/17
	Req. Files: Material.cpp, Particle.h
*/

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include <cmath>
#include <string>
#include "Particle.h"


using std::vector;
using std::stack;

typedef std::shared_ptr<Particle> Part_ptr;

class Material
//Material in which neutrons transport through. Contains all x-sec data and processes reactions
//Multigroup compatible. Fission not added yet.
{
	private:
		int num_g;
		vector<double> total_XS; //size g
		vector<double> Siga; //size g
		vector<double> Sigs; //size g^2
		vector<double> Sigst; //size g-> the total for each group (s11+s12+s13...+s1g)


	public:
	//Constructor
		Material(int ng, vector<double> total_XSi, vector<double> Sigai, vector<double> Sigsi);
	//Functions
	double getTotalXS(int g);
	double getAbsXS(int g);
	double getScaXS(int gi, int gf);

	void processRxn(Part_ptr p, stack<Part_ptr> &pstack, int g);

	void scatter(Part_ptr p, int g);

	void rotate(Part_ptr p, double mu0, double rand);
};
#endif
