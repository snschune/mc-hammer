/*
	Author: Blake
	Date: 11/8/17
	Req. Files: Particle.h
*/

#include "Particle.h"
using std::cout;
using std::endl;

//constructors
Particle::Particle(r_ptr ri, int regioni, int gi): r(ri), cellNum(regioni), group(gi), alive(1) {}
bool Particle::isAlive()
{
	return alive;
}

int Particle::getCell()
{
	return cellNum;
}

p_ptr Particle::getPos()
{
	return r->pos;
}

p_ptr Particle::getDir()
{
	return r->dir;
}

r_ptr Particle::getray()
{
	return r;
}

int Particle::getGroup()
{
	return group;
}

void Particle::setGroup(int g)
{
	group = g;
	return;
}

void Particle::setPos(p_ptr posi)
{
	setPos(posi->x,posi->y,posi->z);
}

void Particle::setDir(p_ptr diri)
{
	setDir(diri->x,diri->y,diri->z);
}

void Particle::setPos(double xi, double yi, double zi)
{
	(r->pos)->x = xi;
	(r->pos)->y = yi;
	(r->pos)->z = zi;
}

void Particle::setDir(double ui, double vi, double wi)
{
	(r->dir)->x = ui;
	(r->dir)->y = vi;
	(r->dir)->z = wi;
}

void Particle::move(double dist)
{
	p_ptr d = r->dir;
	p_ptr p = r->pos;

	double xn = p->x + d->x*dist;
	double yn = p->y + d->y*dist;
	double zn = p->z + d->z*dist;
	
	setPos(xn,yn,zn);

	return; 
}

void Particle::kill()
{
	alive = 0;
	return;
}

void Particle::printState()
{
	cout << "Position: " << (r->pos)->x << " " << (r->pos)->y << " " << (r->pos)->z << endl;
	cout << "Direction: " << (r->dir)->x << " " << (r->dir)->y << " " << (r->dir)->z << endl;
	cout << "Group: " << group;
	cout << " Cell: " << cellNum;
	cout << " Alive: " << alive << endl;
	cout << endl;
	
}