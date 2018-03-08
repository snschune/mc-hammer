/*
 Author: Blake
 Date: 11/8/17
 Req. Files: Particle.h
 */

#include "Particle.h"
using std::cout;
using std::endl;

//constructors

// copy constructor -- for fission
Particle::Particle( const Particle &p) {
  pos              = p.getPos();
  dir              = p.getDir();
  alive            = true;
  group            = p.getGroup();
  cell             = p.getCell();
  collisionCounter = p.getNumCollisions(); 
}

// default constructor -- for source
Particle::Particle(point posi, point diri, int gi): pos(posi), dir(diri), group(gi), alive(true) , collisionCounter(0) 
{
    double norm = 1.0 / std::sqrt( dir.x * dir.x  +  dir.y * dir.y  +  dir.z * dir.z );
    dir.x *= norm; dir.y *= norm; dir.z *= norm;
}

// functions
// sets
void Particle::setCell(Cell_ptr celli)
{
	cell = celli;
	return;
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
	double radius = std::sqrt(pos.x*pos.x + pos.y*pos.y + pos.z*pos.z);
	cout << "distance from origin: " << radius << endl;
    cout << "Group: " << group;
    cout << " Alive: " << alive << endl;
    cout << endl;
    
}

