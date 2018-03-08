/*
	Author: Blake
	Date: 11/8/17
*/

#include "Cell.h"

//constructor
Cell::Cell(Mat_ptr mati, vector<Surf_ptr> surfacesi, vector<bool> insidei): mat(mati), surfaces(surfacesi), inside(insidei) {}

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
	Surf_ptr close_surface = closestSurface(pi);
	ray r = pi->getray();
	double dist = close_surface->distance(r);
	return dist;
}

double Cell::distToCollision(Part_ptr pi)
{
	int group = pi->getGroup();
	double total_xs = mat->getTotalXS(group);
	double dist = -log(Urand())/total_xs;
	return dist;
}

Surf_ptr Cell::closestSurface(Part_ptr p)
{
	int min_index = -1;
	double min_val = std::numeric_limits<double>::max();
	ray r = p->getray();
	for(unsigned int i = 0; i < surfaces.size(); i++)
	{
		Surf_ptr cur_surf =  surfaces[i];
		double dist = cur_surf->distance(r);

		if(dist < min_val)
		{
			min_index = i;
			min_val = dist;
		}
	}
	return surfaces[min_index];
}

void Cell::processRxn(Part_ptr p, double dist, stack<Part_ptr> &pstack)
//a collision has occurred, what happens now?
{
	p->move(dist); //CHANGE THIS
	mat->processRxn(p, pstack, p->getGroup());
	return;
}

