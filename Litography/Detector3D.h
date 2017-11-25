#pragma once
#include "detector.h"
class Detector3D :
	public Detector
{
public:
	double z;
	Detector3D();
	Detector3D(double x,double y,double z,double size);
	bool isIn(double x0,double y0,double z0,double fi,double psi);
	~Detector3D(void);
};

