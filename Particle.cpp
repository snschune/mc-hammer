/*
	Author: Blake
	Date: 11/8/17
	Req. Files: Particle.h
*/

#include "Particle.h"

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

point Particle::getDir()
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
	r->pos = posi;
}

void Particle::setDir(p_ptr diri)
{
	r->dir = diri;
}

void Particle::setPos(double xi, double yi, double zi)
{
	(r->pos)->x = xi;
	(r->pos)->y = yi;
	(r->pos)->z = zi;
}

void Particle::setDir(double ui, double vi, double wi)
{
	(r->pos)->x = ui;
	(r->pos)->y = vi;
	(r->pos)->z = wi;
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
