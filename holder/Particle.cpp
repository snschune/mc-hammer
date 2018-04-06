/*
	Author: Blake
	Date: 11/8/17
	Req. Files: Particle.h
*/

#include "Particle.h"

//constructors
Particle::Particle(ray ri, int regioni, int gi): r(ri), region(regioni), group(gi), alive(1) {}

point Particle::getPos()
{
	return r.pos;
}

point Particle::getDir()
{
	return r.dir;
}

ray Particle::getray()
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

void Particle::setPos(point posi)
{
	r.pos = posi;
}

void Particle::setDir(point diri)
{
	r.dir = diri;
}

void Particle::setPos(double xi, double yi, double zi)
{
	(r.pos).x = xi;
	(r.pos).y = yi;
	(r.pos).z = zi;
}

void Particle::setDir(double ui, double vi, double wi)
{
	(r.dir).x = ui;
	(r.dir).y = vi;
	(r.dir).z = wi;
}

void Particle::move(double dist)
{
	point d = r.dir;
	point p = r.pos;

	double xn = p.x + d.x*dist;
	double yn = p.y + d.y*dist;
	double zn = p.z + d.z*dist;
	
	setPos(xn,yn,zn);

	return; 
}

void Particle::kill()
{
	alive = 0;
	return;
}
