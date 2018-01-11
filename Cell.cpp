/*
	Author: Blake
	Date: 11/8/17
*/

#include "Cell.h"

//constructor
<<<<<<< HEAD
Cell::Cell(Mat_ptr mati, vector<Surf_ptr> surfacesi, vector<bool> insidei): mat(mati), inside(insidei)
{
	for(unsigned int i = 0; i < surfacesi.size(); i++) //learn auto
	{
		surfaces.push_back(surfacesi[i]);
	}
}

//functions
vector<Surf_ptr> Cell::getSurfaces()
=======
Cell::Cell(Mat_ptr mati, vector<pair<Surf_ptr, bool>> surfacesi): mat(mati)
>>>>>>> esgonz
{
	for(auto surface: surfacesi) //learn auto
	{
		surfaces.push_back(surface);
	}
}

//functions
//vector<Surf_ptr> Cell::getSurfaces()
//{
//	return surfaces;
//}
//vector<bool> Cell::getInside()
//{
	//return inside;
//}

Mat_ptr Cell::getMat()
{
	return mat;
}

<<<<<<< HEAD
double Cell::distToSurface(Part_ptr pi)
{
	Surf_ptr close_surface;
	double dist;
	tie(close_surface,dist) = closestSurface(pi);
	return dist;
}
=======

>>>>>>> esgonz

double Cell::distToCollision(Part_ptr pi)
{
	int group = pi->getGroup();
	double total_xs = mat->getTotalXS(group);
	double dist = -log(Urand())/total_xs;
	return dist;
}

<<<<<<< HEAD
pair<Surf_ptr, double> Cell::closestSurface(Part_ptr p)
{
	int min_index = -1;
	double min_val = std::numeric_limits<double>::max();
	point pos = p->getPos();
	point dir = p->getDir();
	for(unsigned int i = 0; i < surfaces.size(); i++)
	{
		Surf_ptr cur_surf =  surfaces[i];
=======


void Cell::processRxn(Part_ptr p, stack<Part_ptr> &pstack)
//a collision has occurred, what happens now?
{
	mat->processRxn(p, pstack, p->getGroup());
	return;
}

bool Cell::amIHere(point pos)
{
	bool isWithin = true;
	//cycle through each surface and if there is one that has a incorrect eval, you are not in this cell
	for(auto surface: surfaces)
	{
		bool test = (surface.first->eval(pos) < 0);
		isWithin = isWithin && (test == surface.second);
	}
	return isWithin;
}

pair<Surf_ptr, double> Cell::closestSurface(Part_ptr p)
{
    Surf_ptr min_surf = nullptr;
	double min_val = std::numeric_limits<double>::max();
	point pos = p->getPos();
	point dir = p->getDir();
	for(auto bound: surfaces)
	{
		Surf_ptr cur_surf =  bound.first;
>>>>>>> esgonz
		double dist = cur_surf->distance(pos,dir);
		if(dist < min_val && dist > 0)
		{
			min_surf = cur_surf;
			min_val = dist;
		}
	}
<<<<<<< HEAD
	if(min_index == -1)
=======
	if(min_surf == nullptr)
>>>>>>> esgonz
	{
		std::cerr << "ERROR: NO SURFACE FOUND" << std::endl;
		std::exit(1);
	}
<<<<<<< HEAD
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
	point pos = p->getPos();
	bool isWithin = true;
	//cycle through each surface and if there is one that has a incorrect eval, you are not in this cell
	for(int i = 0; i < surfaces.size(); i++)
	{
		bool test = (surfaces[i]->eval(pos) < 0);
		isWithin = isWithin && (test == inside[i]);
	}
	return isWithin;
}

=======
	return make_pair(min_surf, min_val);
}

double Cell::distToSurface(Part_ptr pi)
{
	Surf_ptr close_surface;
	double dist;
	tie(close_surface,dist) = closestSurface(pi);
	return dist;
}
>>>>>>> esgonz
