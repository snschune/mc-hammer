/*
	Author: Blake
	Date: 11/21/17
	Main File
*/

#include "Transport.h"
using std::make_shared;

Transport::Transport(){}

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
		siga.push_back(0.5);
		sigsi.push_back(0.5);
		sigso.push_back(sigsi);
		Mat_ptr mat1 = make_shared<Material>(1, sigt, siga, sigso);
		
		//bounds
		Surf_ptr plane1 = make_shared<plane>("plane1", 0.0, 0.0, 1.0, 0.0);
		Surf_ptr plane2 = make_shared<plane>("plane2", 0.0, 0.0, 1.0, 5.0);
		vector<bool> inside1;
		inside1.push_back(false); //false -> outside, true -> inside
		inside1.push_back(true);
		vector<Surf_ptr> cellSurfaces1;
		cellSurfaces1.push_back(plane1);
		cellSurfaces1.push_back(plane2);
		
		//create cell 
		Cell_ptr cell1 = make_shared<Cell>(mat1, cellSurfaces1, inside1);
		
		//add to the geometry
		mats.push_back(mat1);
		surfaces.push_back(plane1);
		surfaces.push_back(plane2);
		cells.push_back(cell1);
		
		
	//set up estimators
	tallies.push_back(0);
	tallies.push_back(0);
	
	//set # his
	numHis = 100;
	
}
void Transport::runTransport()
{
	for(int i = 0; i < numHis ; i++)
	{
		//sample src 
		p_ptr pos = make_shared<point>(0,0,0.001);
		p_ptr dir = make_shared<point>(0,0,11);
		r_ptr r = make_shared<ray>(pos, dir);
		Part_ptr p_new = make_shared<Particle>(r, 1, 1);
		pstack.push(p_new);
		
		//run history
		while(!pstack.empty())
		{
			Part_ptr p = pstack.top();
			while(p->isAlive())
			{
				//cout << "Before: " << endl;
				//p->printState();
				int current_Cell = p->getCell() - 1;
				double d2s = cells[current_Cell]->distToSurface(p);
				double d2c = cells[current_Cell]->distToCollision(p);
				if(d2s > d2c) //collision!
				{
					p->move(d2c);
					cells[current_Cell]->processRxn(p, pstack);
					if(!p->isAlive())
						tallies[1]++;
				}
				else //hit surface
				{
					cout << "pre escape " << cells[0]->amIHere(p) << endl;
					p->move(d2s + 0.0001);
					cout << "escape " << cells[0]->amIHere(p) << endl;
					p->kill(); //only 1 cell in this code
					//p->printState();
					tallies[0]++;
				}
			}
			pstack.pop();
		}
	}
}
void Transport::output()
{
	cout << "Total Number of Histories: " << numHis << endl;
	cout << "Total Number Absorbed: " << tallies[1] << endl;
	cout << "Total Number Leaked: " << tallies[0] << endl; 
}
