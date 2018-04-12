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
Particle::Particle( const Particle &p): pos(p.getPos()) , dir(p.getDir())  {
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
void Particle::setSurf(Surf_ptr surfi)
{
	surf = surfi;
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

void Particle::scatter( int gf )
{
  setGroup(gf);
  collisionCounter++;
  //change direction (isotropic scattering)
  double rand = Urand();
  double mu0 = 2*Urand()-1;
  rotate( mu0,rand );
}

void Particle::rotate( double mu0, double rand )
{
  //xout << "Rotation! mu = " << mu0 << " rand = " << rand << endl;
  if(mu0 == 1)
    return; //no scattering
  
  double pi = 3.1415926535897;
  
  point d = getDir();
  double u = d.x;
  double v = d.y;
  double w = d.z;
  
  double phi = 2*pi*rand; 
  double us = cos(phi);
  double vs = sin(phi);  
  
  double sts = sqrt((1-mu0)*(1+mu0)); //sin(theta)
  
  us = us*sts;
  vs = vs*sts;
  
  double u2v2 = u*u+v*v;
  
  if(u2v2 == 0) //if particle is (0,0,1)
  {
    //cout << "z-direction!" << endl;
    setDir(us,vs,mu0);
    return;
  }
  
  double sintheta = sqrt(u2v2);
  double sinthetai = 1.0/sintheta;
  double cosphi = u*sinthetai;
  double sinphi = v*sinthetai;
  
  double u_new = u*mu0 + us*w*cosphi - vs*sinphi;
  double v_new = v*mu0 + us*w*sinphi + vs*cosphi;
  double w_new = w*mu0 - us*sintheta;
  
  setDir(u_new,v_new,w_new);
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
