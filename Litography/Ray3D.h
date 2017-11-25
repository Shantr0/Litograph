#pragma once

#include "Node3D.h"
#include <list>

class Ray3D 
{
public:
	
	list<Node3D>* points;
	//list<double>* azimutAngle;
	static double waveLength(double E){
		double l=1.2398419739/E;// êýÂ*íì hc/E
		return l/1000;// ìêì
	}
	static double random(){
		return rand()/((double) RAND_MAX);
	}
	static double random(double min,double max){
		double r=rand()/((double) RAND_MAX);
		return r*(max-min)+min;
	}
	static double generateAngle();
	static double generateAngle(double alpha);
	Ray3D(void);
	Ray3D(double E0);
	void output(ofstream& of);
	void input(ifstream& in);
	int getTraectoryCount();
	void addTraectory(double teta,double fi,double r);
	//void addTraectory(double fi,double teta,double r,double& cosA0,double& cosB0,double& cosG0);
	Ray3D operator = (Ray3D ray);
	~Ray3D(void);
};

