#pragma once
#include <list>
#include "Node.h"
using namespace std;
class Ray
{
public:
	static double waveLength(double E){
		double l=1.2398419739/E;// êıÂ*íì hc/E
		return l/1000;// ìêì
	}
	
	list<Node>* points;
	Ray();
	Ray(double initialEnergy);
	Ray(Node** nodes,int count);
	void addTraectory(double teta,double ds);
	int getTraectoryCount();
	static double generateAngle();
	static double generateAngle(double alpha);
	Ray operator = (Ray ray);
	//void write(ofstream& of);
	void read(ifstream& in);
	void output(ofstream& of);
	void input(ifstream& in);
	void clear();
	~Ray();
};

