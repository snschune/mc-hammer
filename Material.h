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
		std::string materialName;
		vector<double> total_XS; //size g
		vector<double> Siga; //size g
		vector<vector<double > > Sigs; //size g^2
		vector<double> Sigst; //size g-> the total for each group (s11+s12+s13...+s1g)


	public:
		//Constructor (will need to change with continuous energy)
		Material( std::string label, int ng );

		void addTotalXS( std::vector< double > newXS );
		void addAbsXS( std::vector< double > newXS );
		void addScaXS( std::vector< std::vector< double > > newXS );
		void addScaTotXS( std::vector< double > newXS );

		//Functions
		double getTotalXS(int g);
		double getAbsXS(int g);
		double getScaXS(int gi, int gf);
		std::string name() { return materialName; };

		void processRxn(Part_ptr p, stack<Part_ptr> &pstack, int g);

		void scatter(Part_ptr p, int g);

		void rotate(Part_ptr p, double mu0, double rand);
};
#endif
