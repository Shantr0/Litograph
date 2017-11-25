#pragma once
#include "Ray3D.h"
#include "SampleParameters.h"
#include "Relief3D.h"
#include "Detector3D.h"


class SampleParameters3D : public SampleParameters
{
public:
	Ray3D* rays;
	Relief3D* relief;
	SampleParameters3D();
	SampleParameters3D(int Z,double m,double ro);
	void calculateTraectory(Ray3D* rays,double E0,double Ecr);
	void calculateTraectory(Ray3D* rays,double E0,double Ecr,Detector* dets,int n);
	void traceRays(int count,double E0,double Ecr,double widthBundle,double distance,double displace);
	void traceRays(int count,double E0,double Ecr,double widthBundle,double distance,double displace,Detector* dets,int n);
	void output(char* name);
	void input(char* name);
	~SampleParameters3D(void);
};

