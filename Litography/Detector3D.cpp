#include "StdAfx.h"
#include "Detector3D.h"


Detector3D::Detector3D(void)
{
	x=0.0;
	y=0.0;
	z=0.0;
	angle=0.0;
	width=1.0;
	count=0;
}
Detector3D::Detector3D(double x,double y,double z,double size){
	this->x=x;
	this->y=y;
	this->z=z;
	width=size;
	angle=0.0;
	count=0;
}
double sqr1(double x){
	return x*x;
}
bool Detector3D::isIn(double x0,double y0,double z0,double fi,double psi){
	double *p=sec(x0,y0,fi);// пересечение с линией детектора в плоскости ХУ
	double *border=borders();
	double x1,y1,z1;
	x1=p[0];
	y1=p[1];
	if(border[0]<=p[0] && p[0]<=border[2]){
		double dx2=sqr1(x1-x0);
		double dy2=sqr1(y1-y0);
		z1=(dx2+dy2)/sqr1(cos(psi))+dx2+dy2;
		z1=sqrt(z1)+z0;
		delete p;
		delete border;
		bool res=sqr1(x-x1)+sqr1(y-y1)+sqr1(z-x1)<sqr1(width/2);
		return true;
	}else {
		delete p;
		delete border;
		return false;
	}

}

Detector3D::~Detector3D(void)
{

}
