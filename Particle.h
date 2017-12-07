/*
	Author: Blake
	Date: 11/8/17
	Req. Files: point.h
*/ 

#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Point.h"
#include <memory>
#include <iostream>



typedef std::shared_ptr<ray> r_ptr;

class Particle
{
	private:
		bool alive;
		r_ptr r;
		int cellNum;
		int group;
	public:
	//constructor
		Particle(r_ptr ri, int regioni, int gi);
		//functions
		bool isAlive();
		int getCell();
		p_ptr getPos();
		p_ptr getDir();
		r_ptr getray();
		int   getGroup();
		
		void setCell(int c);
		void setGroup(int g);
		void setPos(p_ptr posi);
		void setDir(p_ptr diri);
		void setPos(double xi, double yi, double zi);
		void setDir(double ui, double vi, double wi);
		void move(double dist);
		void kill();

		void printState();
};


#endif
