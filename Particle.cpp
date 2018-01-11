/*
	Author: Blake
	Date: 11/8/17
	Req. Files: Particle.h
*/

#include "Particle.h"
using std::cout;
using std::endl;

//constructors
Particle::Particle(point posi, point diri, Cell_ptr celli, int gi): pos(posi), dir(diri), cell(celli), group(gi), alive(1) 
{
	double norm = 1.0 / std::sqrt( dir.x * dir.x  +  dir.y * dir.y  +  dir.z * dir.z );
  	dir.x *= norm; dir.y *= norm; dir.z *= norm;
}

bool Particle::isAlive()
{
	return alive;
}

Cell_ptr Particle::getCell()
{
	return cell;
}

point Particle::getPos()
{
	return pos;
}

point Particle::getDir()
{
	return dir;
}

/*ray Particle::getray()
{
	return r;
}
*/

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
	setPos(posi.x,posi.y,posi.z);
}

void Particle::setDir(point diri)
{
	setDir(diri.x,diri.y,diri.z);
}

void Particle::setPos(double xi, double yi, double zi)
{
	pos.x = xi;
	pos.y = yi;
	pos.z = zi;
}

void Particle::setDir(double ui, double vi, double wi)
{
	dir.x = ui;
	dir.y = vi;
	dir.z = wi;

	double norm = 1.0 / std::sqrt( dir.x * dir.x  +  dir.y * dir.y  +  dir.z * dir.z );
  	dir.x *= norm; dir.y *= norm; dir.z *= norm;
}

void Particle::move(double dist)
{
	double xn = pos.x + dir.x*dist;
	double yn = pos.y + dir.y*dist;
	double zn = pos.z + dir.z*dist;
	
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
	cout << "Position: " << pos.x << " " << pos.y << " " << pos.z << endl;
	cout << "Direction: " << dir.x << " " << dir.y << " " << dir.z << endl;
	cout << "Group: " << group;
	//cout << " Cell: " << cellNum;
	cout << " Alive: " << alive << endl;
	cout << endl;
	
}
