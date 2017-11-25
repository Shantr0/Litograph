#include "StdAfx.h"
#include "Detector.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

Detector::Detector(void)
{
	x=0.0;
	y=0.0;
	angle=0.0;
	width=1.0;
	count=0;
	active=true;
}
Detector::Detector(double x,double y,double size)
{
	this->x=x;
	this->y=y;
	width=size;
	angle=0.0;
	count=0;
	active=true;
}
double Detector::getSize(){
	return width;
}
void Detector::setSize(double w){
	width=w;
}
int Detector::getCount(){
	return count;
}
void Detector::setCount(int n){
	count=n;
}
void Detector::incCount(){
	count++;
}
double * Detector::borders(){// границы детектора
	double w2cos=getSize()/2*cos(angle);// w/2*cos(alpha)
	double x0=x-w2cos;
	double x1=x+w2cos;
	double w2sin=getSize()/2*sin(angle);
	double y0=y+w2sin;
	double y1=y-w2sin;
	double p[]={x0,y0,x1,y1};
	double* points=new double[4];
	for(int i=0;i<4;i++)points[i]=p[i];
	return points;
}
double* Detector::sec(double x,double y,double fi){// проверка на попадание в детектор электрона вылетевшего из точки (x,y) под углом fi
	double* p=borders();
	double x0=p[0];
	double y0=p[1];
	double x1=p[2];
	double y1=p[3];
	double k=tan(fi-M_PI/2);
	//k=M_PI/2-k;
	double l=(y0-y-k*(x0-x))/(k*(x1-x0)-(y1-y0));
	x=x0+l*(x1-x0);
	y=y0+l*(y1-y0);
	delete p;
	p=new double[2];
	p[0]=x;
	p[1]=y;
	return p;
	//double Y=max(y0,y1);
	//double X=(Y-y)/k+x;
}

bool Detector::isIn(double x,double y,double fi){
	double *p=sec(x,y,fi);// пересечение с линией детектора
	double *border=borders();
	if(border[0]<=p[0] && p[0]<=border[2]){
		delete p;
		delete border;
		return true;
	}else {
		delete p;
		delete border;
		return false;
	}
}
bool Detector::isIn(double x,double y){
	double *border=borders();
	if(border[0]<=x && x<=border[2]){
		delete border;
		return true;
	}else {
		delete border;
		return false;
	}

}
void Detector::resetCount(){count=0;}

void Detector::output(ofstream& of){
	of<<x<<" ";
	of<<y<<" ";
	of<<angle<<" ";
	of<<width<<" ";
	of<<count<<"\n";
}
void Detector::input(ifstream& in){
	//Detector* det=new Detector();
	in>>x;
	in>>y;
	in>>angle;
	in>>width;
	in>>count;
}
Detector::~Detector(void)
{
}
