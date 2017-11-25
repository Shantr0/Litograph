//#include "StdAfx.h"
#include "SampleParameters.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
#include "Detector.h"



#define e4 6.5893345919429927536586336586641E-76
#define NA 6.02e+23
#define e05 exp(0.5)
#define e_05 1/e05
#define pi_6 M_PI/6
#define pi_90 M_PI/90

double sqr(double x){
	return x*x;
};
SampleParameters::SampleParameters(void)
{
	Znum=1;
	atomMass=1;// а.е.м
	raysCount=0;
	density=90; // г/см^3
	rays=NULL;
}
SampleParameters::SampleParameters(int z,double m,double ro){
	Znum=z;
	atomMass=m;
	density=ro;
	rays=NULL;
}

int SampleParameters::getRaysCount(){
	return raysCount;
}
int SampleParameters::getZNumber(){
	return Znum;
}
double SampleParameters::getMass(){
	return atomMass;
}
double SampleParameters::getDensity(){
	return density;
}

void SampleParameters::setRaysCount(long newCount){raysCount=newCount;}
void SampleParameters::setZNumber(int number){Znum=number;}
void SampleParameters::setMass(double mass){atomMass=mass;}
void SampleParameters::setDensity(double density){this->density=density;}

double SampleParameters::scatteringAngle(int i){
	double k=i/raysCount;
	return k*cos(M_PI+k);
}
double SampleParameters::energieLoss(double Em,double s){ // потеря энергии
	double E0=energieLossUnit(Em);
	return E0*s;
}
double SampleParameters::energieLossUnit(double Em){
	double J=(9.76*Znum+58.5*pow(Znum,-0.19))/1000;
	double E =-7.85e+4*Znum*density/(atomMass*Em)*log(1.1658*Em/J);
	return E;
}
double SampleParameters::scattering(double fi,double E){
	return 1.62e-20*sqr(Znum/(E*tan(fi/2)));
}
double SampleParameters::scattering2(double a,double E){
	a=1/(a*(1+a));
	return 6.547e-20*a*sqr(Znum/E)*sqr((E+511)/(E+1022));
}
double SampleParameters::meanFreePath(double fi,double E){// ДЛИНА свободного пробега
	double s=10*scattering(fi,E);// сечение рассеяния резерфорда
	return atomMass/(density*s*NA);// в cм
}
double SampleParameters::meanFreePath(double fi,double E,double a){// ДЛИНА свободного пробега
	double s=scattering2(a,E);// сечение рассеяния резерфорда
	return atomMass/(density*s*NA);// в cм
}

bool isInf(double val){
	double zero=0.0;
	double inf=1/zero;
	return abs(val)==inf;
}

double SampleParameters::runDistance(double fi,double E){// расстояние до следующего взаимодействия
	double s=meanFreePath(fi,E);
	double ln=0.0;
	double a;
	do 
	{
		a=rand()/((double) RAND_MAX);
		ln=log(a);
	} while (isInf(ln));
	double res=abs(s*ln);
	return abs(s*ln);
}
double SampleParameters::runDistance(double fi,double E,double al){// расстояние до следующего взаимодействия
	double s=meanFreePath(fi,E,al);
	double ln;
	double a;
	do 
	{
		a=rand()/((double) RAND_MAX);
		ln=log(a);
	} while (isInf(ln));
	double res=abs(s*ln);
	return abs(s*ln);
}
double SampleParameters::depthOfPenetration(double E0){
	double J=(9.76*Znum+58.5*pow(Znum,-0.19))/1000;
	return atomMass*sqr(E0)/(-7.85e+4*Znum*density*log(1.1658*E0/J));
	//return 0.0276*atomMass*pow(E0,1.67)/(density*pow(Znum,0.889));
}
void SampleParameters::clear(){
	//for(int i=0;i<raysCount;i++)rays[i].clear();
	delete [] rays;
	raysCount=0;
	rays=NULL;
}
void SampleParameters::traceRays(int count,double E0,double Ecr){
	rays=new Ray[raysCount];// генерация лучей
	srand(time(0));
	for(int i=0;i<raysCount;i++){	// для всех лучей
		calculateTraectory(rays+i,E0,Ecr);// расчет траектории
	}
}
void SampleParameters::traceRays(int count,double E0,double Ecr,double widthBundle,double distance,double displace){// трассировка лучей с начальной энергией Е0 
	//из эл. пушки диаметром widthBundle и координатами (displace,distance)
	rays=new Ray[raysCount];// генерация лучей
	srand(time(0));
	double dx=widthBundle/raysCount;
	for(int i=0;i<raysCount;i++){	// для всех лучей
		rays[i].points->back().energy=E0;// энергия на старте
		rays[i].points->back().x=i*dx+displace;// координата х с учетом смещения
		rays[i].points->back().y=distance;// начальное положение ЭП
		calculateTraectory(rays+i,E0,Ecr);// расчет траектории
	}
}
void SampleParameters::traceRays(int count,double E0,double Ecr,double widthBundle,double distance,double displace,Detector* dets,int n){
	raysCount=count;
	rays=new Ray[raysCount];// генерация лучей
	srand(time(0));
	double dx=widthBundle/raysCount;
	for(int i=0;i<n;i++) dets[i].resetCount();
	for(int i=0;i<raysCount;i++){	// для всех лучей
		rays[i].points->back().energy=E0;// энергия на старте
		rays[i].points->back().x=i*dx+displace;// координата х с учетом смещения
		rays[i].points->back().y=distance;// начальное положение ЭП
		calculateTraectory(rays+i,E0,Ecr,dets,n);// расчет траектории
	}
}
//void SampleParameters::calculateTraectory(Ray* rays,double E0,double Ecr){// ход луча
//	double E=E0;
//	while (E>Ecr)
//	{
//		double fi=Ray::generateAngle();// угол отклонения
//		double s=runDistance(fi,E);// средний пробег
//		rays[0].addTraectory(fi,s);// добавление траектории 
//		double dE=energieLoss(E,s);
//		E-=dE;// потеря энергии
//		Node* p=&rays[0].points->back();
//		p->energy=E;
//		if ((p->y)>0) {// вылет из образца
//			p->y=0;
//			break;
//		}
//	}
//	//dist->clear();
//}
void SampleParameters::firstPath(Ray* rays,double& E){
	double a=3.4e-3*pow(Znum,0.67)/E;
	double s=runDistance(0.0,E,a);//  пробег
	rays[0].addTraectory(0.0,s);// добавление траектории 
	double dE=abs(energieLoss(E,s));// потеря энергии
	E-=dE;// потеря энергии
	list<Node>::iterator p=--rays[0].points->end();
	p->energy=E;
}
void SampleParameters::calculateTraectory(Ray* rays,double E0,double Ecr){// расчет ход луча
	double E=E0;
	double y0=rays[0].points->begin()->y;// точка вылета эл. из пушки
	rays[0].addTraectory(0,y0-relief->getY(rays[0].points->begin()->x));// пролет в вакууме до образца
	(--rays[0].points->end())->energy=E0;
	double s;
	firstPath(rays,E);// пробег под нулевым углом
	while (E>Ecr)// расчет траектории
	{
		double a=3.4e-3*pow(Znum,0.67)/E;
		double fi=Ray::generateAngle(a);// угол отклонения
		s=runDistance(fi,E,a);//  пробег
		rays[0].addTraectory(fi,s);// добавление траектории 
		double dE=abs(energieLoss(E,s));// потеря энергии
		E-=dE;// потеря энергии
		list<Node>::iterator p=--rays[0].points->end();
		p->energy=E;
		if (!relief->isInMaterial(p->x,p->y)) {// вылет из образца
			list<Node>::iterator prev=std::prev(p);
			double k=(p->y-prev->y)/(p->x-prev->x);
			double px=p->x;
			if(p->x>prev->x)p->x=relief->xIntersect(k,p->x,p->y,1);// проверка на повторное 
			else p->x=relief->xIntersect(k,p->x,p->y,-1);// попадание в образец
			if(isInf(p->x)){// луч не идет в образец
				if(k>0 && prev->x<px || k<0 && prev->x>px)p->y=rays[0].points->begin()->y;
				else p->y=-rays[0].points->begin()->y;// ???
				p->x=prev->x+(p->y-prev->y)/k;
				p->energy=prev->energy;
				p->angle=prev->angle;
				break;
			}else{// есть попадание в образец
				p->y=relief->getY(p->x);
				p->energy=prev->energy;
				p->angle=prev->angle;
				if(relief->getX(0)> p->x || p->x>relief->getX(relief->getSize()-1))break;
				firstPath(rays,E);
			}
		}
		if(dE<=1e-16 || s<=1e-18)break;
	}
}
void SampleParameters::calculateTraectory(Ray* rays,double E0,double Ecr,Detector* dets,int n){
	double E=E0;
	double y0=rays[0].points->begin()->y;// точка вылета эл. из пушки
	rays[0].addTraectory(0,y0-relief->getY(rays[0].points->begin()->x));// пролет в вакууме до образца
	(--rays[0].points->end())->energy=E0;
	firstPath(rays,E);// пробег под нулевым углом
	while (E>Ecr)// расчет траектории
	{
		double a=3.4e-3*pow(Znum,0.67)/E;
		double fi=Ray::generateAngle(a);// угол отклонения
		double s=runDistance(fi,E,a);//  пробег
		rays[0].addTraectory(fi,s);// добавление траектории 
		double dE=abs(energieLoss(E,s));// потеря энергии
		E-=dE;// потеря энергии
		list<Node>::iterator p=--rays[0].points->end();
		p->energy=E;
		//bool isInDet=false;
		double maxYdet=Detector::maxY(dets,n);
		if (!relief->isInMaterial(p->x,p->y)) {// вылет из образца
			list<Node>::iterator prev=std::prev(p);
			double k=(p->y-prev->y)/(p->x-prev->x);
			double px=p->x;
			if(p->x>prev->x)p->x=relief->xIntersect(k,p->x,p->y,1);// проверка на повторное 
			else p->x=relief->xIntersect(k,p->x,p->y,-1);// попадание в образец
			if(isInf(p->x)){// луч не идет в образец
				for(int i=0;i<n;i++){// проверка попадания в детектор
					double *point=dets[i].sec(px,p->y,p->angle);// точка пересечения с линией детектора
					if(dets[i].isActive() && dets[i].isIn(point[0],point[1])){// в случае попадания
						dets[i].incCount();
						p->x=point[0];
						p->y=point[1];
						p->energy=prev->energy;
						p->angle=prev->angle;
						//break;
						return;
					}	
				}
				// если не попадает ни в 1 детектор
				if(k>0 && prev->x<px || k<0 && prev->x>px)p->y=maxYdet;// ???
				else p->y=0;//-rays[0].points->begin()->y;
				p->x=prev->x+(p->y-prev->y)/k;
				p->energy=prev->energy;
				p->angle=prev->angle;
				break;
			}else{// есть попадание в образец
				p->y=relief->getY(p->x);
				p->energy=prev->energy;
				p->angle=prev->angle;
				if(relief->getX(0)> p->x || p->x>relief->getX(relief->getSize()-1))
					break;
				//firstPath(rays,E);
			}
		}
		if(dE<=1e-16)break;
	}
}

bool SampleParameters::isTraced(){
	return (rays!=NULL);
}
void SampleParameters::deleteRay(int i){
	for(int j=i;i<raysCount;i++){
		rays[i]=rays[i+1];
	}
}
//void SampleParameters::writeToFile(char* name){
//	//FILE* f=fopen(name,ios::out);
//	ofstream of;
//	of.open(name,ios::out );
//	of.write((char*)&Znum,sizeof(int));
//	of.write((char*)&atomMass,sizeof(double));
//	of.write((char*)&density,sizeof(double));
//	of.write((char*)&citicalEnergy,sizeof(double));
//	of.write((char*)&raysCount,sizeof(int));
//	for(int i=0;i<raysCount;i++){
//		rays[i].write(of);
//	}
//	//if(relief) relief->write(&of);
//	of.close();
//}
void SampleParameters::output(char* name){
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
void SampleParameters::output(char* name,int detectorsCount,Detector* detectors){
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
	if (detectorsCount>0)
	{
		of<<detectorsCount;
		for (int i=0;i<detectorsCount;i++)
		{
			detectors[i].output(of);
		}
	}
	of.close();
}
//void SampleParameters::readFromFile(char* name){
//	ifstream in;
//	in.open(name,ios::in|ios::binary);
//	in.read((char*)&Znum,sizeof(int));
//	in.read((char*)&atomMass,sizeof(double));
//	in.read((char*)&density,sizeof(double));
//	in.read((char*)&citicalEnergy,sizeof(double));
//	in.read((char*)&raysCount,sizeof(int));
//	rays=new Ray[raysCount];
//	for (int i=0;i<raysCount;i++)
//	{
//		rays[i].read(in);
//	}
//	if(!in.eof()){
//		//relief->read(&in);
//	}
//}
void SampleParameters::input(char* name){
	ifstream in;
	in.open(name,ios::in);
	in>>Znum;
	in>>atomMass;
	in>>density;
	in>>raysCount;
	rays=new Ray[raysCount];
	for(int i=0;i<raysCount;i++){
		rays[i].input(in);
	}
	if(relief) relief->read(in);
	in.close();
}
void SampleParameters::input(char* name,int& detectorsCount,Detector* detectors){
	ifstream in;
	in.open(name,ios::in);
	in>>Znum;
	in>>atomMass;
	in>>density;
	in>>raysCount;
	rays=new Ray[raysCount];
	for(int i=0;i<raysCount;i++){
		rays[i].input(in);
	}
	if(relief) relief->read(in);
	else {
		relief=new Relief2D();
		relief->read(in);
	}
	//detectorsCount=0;
	if(!in.eof()){
		in>>detectorsCount;
		for(int i=0;i<detectorsCount;i++) 
			detectors[i].input(in);
	}
	in.close();
}
SampleParameters::~SampleParameters(){
	//for(int i=0;i<raysCount;i++)delete rays[i];
	delete [] rays;
	rays=NULL;
	raysCount=0;
	Znum=1;
	atomMass=1;
	density=1;
}

