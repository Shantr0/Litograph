//#include "StdAfx.h"
#include "SampleParameters3D.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
#include "Detector3D.h"

SampleParameters3D::SampleParameters3D(void)
{
	Znum=1;
	atomMass=1;// а.е.м
	raysCount=0;
	density=90; // г/см^3
	rays=NULL;
	
}
SampleParameters3D::SampleParameters3D(int Z,double m,double ro)
{
	Znum=Z;
	atomMass=m;// а.е.м
	raysCount=0;
	density=ro; // г/см^3
	rays=NULL;

}

void SampleParameters3D::calculateTraectory(Ray3D* rays,double E0,double Ecr){// расчет ход луча
	double E=E0;
	double y0=rays[0].points->begin()->y;// точка вылета эл. из пушки
	double s=y0-relief->getY(rays[0].points->begin()->x,rays[0].points->begin()->z);
	double cosA=1,cosB=1,cosG=-1;
	rays[0].addTraectory(0.0,0.0,s);// пролет в вакууме до образца
	//rays[0].addTraectory(0.0,0.0,s,cosA,cosB,cosG);// пролет в вакууме до образца
	(--rays[0].points->end())->energy=E0;
	double s0=s;
	while (E>Ecr)// расчет траектории
	{
		double a=3.4e-3*pow(Znum,0.67)/E;
		double fi=Ray3D::generateAngle(a);// угол отклонения
		double psi=rand()/((double) RAND_MAX)*2*M_PI;
		s=runDistance(fi,E,a);//  пробег
		//double k;
		//if(s>s0)
		//	k=s/s0;
		rays[0].addTraectory(fi,psi,s);// добавление траектории 
		double dE=abs(energieLoss(E,s));// потеря энергии
		E-=dE;// потеря энергии
		list<Node3D>::iterator p=--rays[0].points->end();
		p->energy=E;
		//bool isInDet=false;
		if (!relief->isInMaterial(p->x,p->y,p->z)) {// вылет из образца
			list<Node3D>::iterator prev=std::prev(p);
			p->y=rays[0].points->begin()->y;
			double r=-(p->y-prev->y)/cos(fi);
			p->x=prev->x+r*sin(fi)*cos(psi);
			p->z=prev->z+r*sin(fi)*sin(psi);
			p->energy=prev->energy;
			p->angle=prev->angle;
			p->azimutAngle=prev->azimutAngle;

			//double y=rays[0].points->begin()->y;
			//double r=y/cos(fi);
			//rays[0].addTraectory(0,0,r);
			break;
		}
		if(dE<=0.000001)break;
		s0=s;
	}
		
}
void SampleParameters3D::calculateTraectory(Ray3D* rays,double E0,double Ecr,Detector* dets,int n){
	double E=E0;
	double y0=rays[0].points->begin()->y;// точка вылета эл. из пушки
	rays[0].addTraectory(0.0,0.0,y0-relief->getY(rays[0].points->begin()->x,rays[0].points->begin()->z));// пролет в вакууме до образца
	(--rays[0].points->end())->energy=E0;
	while (E>Ecr)// расчет траектории
	{
		double fi=Ray3D::generateAngle();// угол отклонения
		double psi=rand()/((double) RAND_MAX)*2*M_PI;
		double s=runDistance(fi,E);//  пробег
		rays[0].addTraectory(fi,psi,s);// добавление траектории 
		double dE=abs(energieLoss(E,s));// потеря энергии
		E-=dE;// потеря энергии
		list<Node3D>::iterator p=--rays[0].points->end();
		p->energy=E;
		bool isInDet=false;
		if (!relief->isInMaterial(p->x,p->y,p->z)) {// вылет из образца
			list<Node3D>::iterator prev=std::prev(p);
			for(int i=0;i<n;i++){
				if(dets[i].isIn(prev->x,prev->y,prev->angle)){
					dets[i].incCount();
					double *point=dets[i].sec(prev->x,prev->y,prev->angle);
					p->x=point[0];
					p->y=point[1];
					p->energy=prev->energy;
					p->angle=prev->angle;
					break;
				}
			}
			p->y=Detector::maxY(dets,n);// rays[0].points->begin()->y;
			p->x=prev->x+(p->y-prev->y)/tan(p->angle);
			p->energy=prev->energy;
			p->angle=prev->angle;
			break;
		}
		if(dE<=1e-16)break;
	}
}
void SampleParameters3D::traceRays(int count,double E0,double Ecr,double widthBundle,double distance,double displace){// трассировка лучей с начальной энергией Е0 
	//из эл. пушки диаметром widthBundle и координатами (displace,distance)
	rays=new Ray3D[raysCount];// генерация лучей
	srand(time(0));
	double dx;
	Node3D* p=new Node3D();
	int n1,n2;
	if(raysCount>10){
		n1=10;
		n2=raysCount/n1;
	}else{
		n1=1;
		n2=raysCount;
	}
	dx=widthBundle/n1;
	double dfi=2*M_PI/n2;
	for(int i=0;i<n1;i++){	// для всех лучей
		double p0=-widthBundle/2+i*dx+displace;
		for(int j=0;j<n2;j++){
			rays[i*n2+j].points->insert(rays[i*n2+j].points->end(),*p);
			rays[i*n2+j].points->back().energy=E0;// энергия на старте
			rays[i*n2+j].points->back().x=p0*cos(j*dfi);// координата х с учетом смещения
			rays[i*n2+j].points->back().y=distance;// начальное положение ЭП
			rays[i*n2+j].points->back().z=p0*sin(j*dfi);
			calculateTraectory(rays+i*n2+j,E0,Ecr);// расчет траектории
		}
	}
}
void SampleParameters3D::traceRays(int count,double E0,double Ecr,double widthBundle,double distance,double displace,Detector* dets,int n){
	rays=new Ray3D[raysCount];// генерация лучей
	srand(time(0));
	for(int i=0;i<n;i++) dets[i].resetCount();
	int n1=10;
	int n2=raysCount/n1;
	double dx=widthBundle/n2;
	double dfi=M_PI/n1;
	Node3D* p=new Node3D();
	
	for(int i=0;i<n1;i++){	// для всех лучей
		double p0=-widthBundle/2+i*dx+displace;
		for(int j=0;j<n2;j++){
			rays[i].points->insert(rays[i].points->end(),*p);
			rays[i*n2+j].points->back().energy=E0;// энергия на старте
			rays[i*n2+j].points->back().x=p0*cos(j*dfi);// координата х с учетом смещения
			rays[i*n2+j].points->back().y=distance;// начальное положение ЭП
			rays[i*n2+j].points->back().z=p0*sin(j*dfi);	
			calculateTraectory(rays+i,E0,Ecr,dets,n);// расчет траектории
		}
	}
}

void SampleParameters3D::input(char* name){
	ifstream in;
	in.open(name,ios::in);
	in>>Znum;
	in>>atomMass;
	in>>density;
	in>>raysCount;
	rays=new Ray3D[raysCount];
	for(int i=0;i<raysCount;i++){
		rays[i].input(in);
	}
	if(relief) relief->read(in);
	in.close();
}
void SampleParameters3D::output(char* name){
	ofstream of;
	of.open(name,ios::out);
	of<<Znum<<"\n";
	of<<atomMass<<"\n";
	of<<density<<"\n";
	of<<raysCount<<"\n";
	for(int i=0;i<raysCount;i++){
		rays[i].output(of);
	}
	if(relief) relief->write(of);

	of.close();
}
SampleParameters3D::~SampleParameters3D()
{
	delete [] rays;
	rays=NULL;
	raysCount=0;
}
