/*
	Author: Blake
	Date: 11/21/17
	Main File
*/

#include "Transport.h"
using std::make_shared;

Transport::Transport()
{
}

void Transport::setup()
{
	//read input file if it existed
	//plane at x = 0 and at x = 10 -> cell1
		//material
		vector<double> sigt;
		vector<double> siga;
		vector<double> sigsi;
		vector<vector<double>> sigso;
		sigt.push_back(1.0);
		siga.push_back(1.0);
		sigsi.push_back(0.0);
		sigso.push_back(sigsi);
		Mat_ptr mat1 = make_shared<Material>(1, sigt, siga, sigso);
		
		//bounds
		Surf_ptr plane1 = make_shared<plane>("plane1", 1.0, 0.0, 0.0, 0.0);
		Surf_ptr plane2 = make_shared<plane>("plane2", 1.0, 0.0, 0.0, 10.0);
		vector<bool> inside1;
		inside1.push_back(false);
		inside1.push_back(true);
		vector<Surf_ptr> cellSurfaces1;
		cellSurfaces1.push_back(plane1);
		cellSurfaces1.push_back(plane2);
		
		cout << "trans.cpp line 38" << endl;
		//create cell 
		Cell_ptr cell1 = make_shared<Cell>(mat1, cellSurfaces1, inside1);
		
		//add to the geometry
		mats.push_back(mat1);
		surfaces.push_back(plane1);
		surfaces.push_back(plane2);
		cells.push_back(cell1);
		
		
	//read source info
	//all particles start in the positive x direction at the origin
	numHis = 1e6;
	
	for(int i = 0; i < numHis; i++)
	{
		p_ptr d = make_shared<point>(1,0,0);
		p_ptr p = make_shared<point>(0.1,0,0);
		r_ptr r = make_shared<ray>(*d, *p);
		
		
		pstack.push(make_shared<Particle>(*r, 0, 1));
	}
	//set up estimators
	tallies.push_back(0);
	tallies.push_back(0);
	
}
void Transport::runTransport()
{
	cout << "starting transport" << endl;
	while(!pstack.empty())
	{
		Part_ptr p = pstack.top();
		runHistory(p);
		pstack.pop();
	}
}
void Transport::runHistory(Part_ptr p)
{
	while(p->isAlive())
	{
		int curCell = p->getCell();
		double d2s = cells[curCell]->distToSurface(p);
		double d2c = cells[curCell]->distToCollision(p);
		
		if(d2s > d2c) //collision!
		{
			p->move(d2c);
			cells[p->getCell()]->processRxn(p, pstack);
			tallies[1]++;
		}
		else
		{
			p->move(d2s + 0.01);
			//INSERT FANCY CODE TO FIGURE OUT WHERE I AM
			p->kill(); //only 1 cell in this code
			tallies[0]++;
		}
	}
}
void Transport::output()
{
	cout << "Total Number of Histories: " << numHis << endl;
	cout << "Total Number Absorbed: " << tallies[1] << endl;
	cout << "Total Number Leaked: " << tallies[0] << endl; 
}
