#pragma once
#include "Ray.h"
#include "Detector.h"
#include "Relief2D.h"

 class SampleParameters
{
protected:
	int Znum;// порядковый номер
	long int raysCount;// количество лучей
	double atomMass;// атомная масса
	double density;// плотность

	void firstPath(Ray* rays,double& E);
public:
	Ray* rays;	
	double citicalEnergy;
	Relief2D* relief;
	SampleParameters();
	SampleParameters(int Z,double m,double ro);
	int getRaysCount();
	int getZNumber();
	double getMass();
	double getDensity();

	void setRaysCount(long count);
	void setZNumber(int numb);
	void setMass(double mass);
	void setDensity(double dens);
	// упругое рассеяние
	double scattering(double teta,double E);
	double scattering2(double a,double E);
	double scatteringAngle(int i);// угол рассеяния
	double meanFreePath(double fi,double E);// средняя длина свободного пробега
	double meanFreePath(double fi,double E,double a);
	double runDistance(double fi,double E);
	double runDistance(double fi,double E,double a);
	double energieLoss(double Em,double s);// потеря энергии на участке 
	double energieLossUnit(double Em);
	void calculateTraectory(Ray* rays,double E0,double Ecr);
	void calculateTraectory(Ray* rays,double E0,double Ecr,Detector* dets,int n);
	//void calculateTraectory(Ray* rays,double E0,double Ecr,double y0); // координата эл. пушки у0 
	void traceRays(int count, double E0,double Ecr);// трассировка лучей
	void traceRays(int count,double E0,double Ecr,double widthBundle,double distance,double displace);
	void traceRays(int count,double E0,double Ecr,double widthBundle,double distance,double displace,Detector* dets,int n);
	double depthOfPenetration(double E0);
	void generateRelief2D();
	// очистка
	void clear();
	void deleteRay(int i);
	bool isTraced();

	//void writeToFile(char* name);
	//void readFromFile(char* name);
	void output(char* name);
	void output(char* name,int detectorsCount,Detector* detectors);
	void input(char* name);
	void input(char* name,int& detectorsCount,Detector* detectors);
	~SampleParameters();
};