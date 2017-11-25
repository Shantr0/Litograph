#include "StdAfx.h"
#include "Ray3D.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>

using namespace std;


Ray3D::Ray3D()
{
	points=new list<Node3D>();
	//Node3D* p=new Node3D();
	//points->insert(points->end(),*p);
}
int Ray3D::getTraectoryCount(){
	return points->size();
}
double Ray3D::generateAngle(){
	double angle;
	double a=random();
	if (a<0.8) angle=random(M_PI/90,M_PI/18);
	else angle=random(M_PI/18,M_PI);
	if(random()<0.5)angle=-angle;
	return angle;
}
double Ray3D::generateAngle(double alpha){
	double angle;
	double a=random();
	angle=1-(2*alpha*a/(1+alpha-a));
	angle=acos(angle);
	if(random()>0.5)angle=-angle;
	return angle;
}
void Ray3D::addTraectory(double teta,double fi,double r){// новая траектория электрона
	Node3D* p=&points->back();// последняя точка
	double alpha=p->angle;//angle->back();// поворот СК
	double beta=p->azimutAngle;
	double xn=r*sin(teta)*cos(fi);// координаты
	double yn=-r*cos(teta);// в новой системе
	double zn=r*sin(teta)*sin(fi);
	double xi,yi,zi,cosA,sinA;
	cosA=cos(alpha);
	sinA=sin(alpha);
	// вращение вокруг оси z
	xi=xn*cosA-yn*sinA;
	yi=xn*sinA+yn*cosA;
	xn=xi;
	yn=yi;
	// вращение вокруг оси y
	xi=xn*cos(beta)+zn*sin(beta)+p->x;
	yi=yn+p->y;
	zi=-xn*sin(beta)+zn*cos(beta)+p->z;

	alpha+=teta;
	beta+=fi;
	Node3D* node=new Node3D(xi,yi,zi,alpha,beta);
	//node->s=r;// для отладки
	points->insert(points->end(),*node);
}
//void Ray3D::addTraectory(double fi,double teta,double r,double& cosA0,double& cosB0,double& cosG0){// новая траектория электрона 
//	Node3D* p=&points->back();// последняя точка
//	double alpha=p->angle;//angle->back();// поворот СК
//	double beta=p->azimutAngle;
//	double x1,y1,z1,cosA1,cosB1,cosG1;
//	//double cosA0=cos(alpha);
//	if(abs(cosG0)>0.9999){
//		cosA1=cos(teta)*sin(fi);
//		cosB1=sin(teta)*sin(fi);
//		cosG1=cos(fi)*cosG0/abs(cosG0);
//	}else{
//		double sinF=sin(fi);
//		double sinG0=sqrt(1-cosG0*cosG0);
//		double cosW=cos(teta);
//		double cosF=cos(fi);
//		cosA1=sinF*(cosA0*cosG0*cosW-cosB0*sin(teta))+cosA0*cosF/sinG0;
//		cosB1=sinF*sinG0*(cosB0*cosG0*cosW-cosA0*sin(teta))+cosB0*cosF;
//		cosG1=-sin(fi)*cos(teta)*sinG0+cosG0*cosF;
//	}
//	
//	x1=p->x+cosA1*r;
//	y1=p->y+cosG1*r;
//	z1=p->z+cosB1*r;
//	cosA0=cosA1;
//	cosB0=cosB1;
//	cosG0=cosG1;
//	alpha+=teta;
//	beta+=fi;
//
//	Node3D* node=new Node3D(x1,y1,z1,alpha,beta);
//	//node->s=r;// для отладки
//	points->insert(points->end(),*node);
//}
void Ray3D::output(ofstream& of){
	list<Node3D>::iterator p=points->begin();
	list<Node3D>::iterator prEnd=points->end();
	//copy(p,prEnd, ostream_iterator<Node>(of,"\n"));
	int n=getTraectoryCount();
	of<<n;
	of<<"\n";
	while(p!=prEnd){
		p->output(of);
		p++;
	}
}
void Ray3D::input(ifstream& in){
	//points=new list<Node>();
	Node3D* node=new Node3D();
	int n;
	in>>n;
	for(int i=0;i<n;i++){
		node->input(in);
		points->insert(points->end(),*node);
	}
}
Ray3D Ray3D::operator = (Ray3D ray){
	this->points=ray.points;
	return *this;
}
Ray3D::~Ray3D(void)
{
	points->clear();
	delete points;
}
