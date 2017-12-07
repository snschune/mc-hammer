/*
	Author: Blake
	Date: 11/8/17
*/

#include "Cell.h"

//constructor
Cell::Cell(Mat_ptr mati, vector<Surf_ptr> surfacesi, vector<bool> insidei): mat(mati), inside(insidei)
{
	for(unsigned int i = 0; i < surfacesi.size(); i++)
	{
		surfaces.push_back(surfacesi[i]);
	}
}

//functions
vector<Surf_ptr> Cell::getSurfaces()
{
	return surfaces;
}
vector<bool> Cell::getInside()
{
	return inside;
}
Mat_ptr Cell::getMat()
{
	return mat;
}

double Cell::distToSurface(Part_ptr pi)
{
	Surf_ptr close_surface;
	double dist;
	tie(close_surface,dist) = closestSurface(pi);
	return dist;
}

double Cell::distToCollision(Part_ptr pi)
{
	int group = pi->getGroup();
	double total_xs = mat->getTotalXS(group);
	double dist = -log(Urand())/total_xs;
	return dist;
}

pair<Surf_ptr, double> Cell::closestSurface(Part_ptr p)
{
	int min_index = -1;
	double min_val = std::numeric_limits<double>::max();
	r_ptr r = p->getray();
	for(unsigned int i = 0; i < surfaces.size(); i++)
	{
		Surf_ptr cur_surf =  surfaces[i];
		double dist = cur_surf->distance(*r);
		if(dist < min_val && dist > 0)
		{
			min_index = i;
			min_val = dist;
		}
	}
	if(min_index == -1)
	{
		std::cerr << "ERROR: NO SURFACE FOUND" << std::endl;
		std::exit(1);
	}
	return make_pair(surfaces[min_index], min_val);
}

void Cell::processRxn(Part_ptr p, stack<Part_ptr> &pstack)
//a collision has occurred, what happens now?
{
	mat->processRxn(p, pstack, p->getGroup());
	return;
}

bool Cell::amIHere(Part_ptr p)
{
	point pos = *(p->getPos());
	bool isWithin = true;
	//cycle through each surface and if there is one that has a incorrect eval, you are not in this cell
	for(int i = 0; i < surfaces.size(); i++)
	{
		bool test = (surfaces[i]->eval(pos) < 0);
		isWithin = isWithin && (test == inside[i]);
	}
	return isWithin;
}

