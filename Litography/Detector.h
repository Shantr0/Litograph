#pragma once
#include <fstream>
using namespace std;
class Detector
{
protected:
	double width;// характеризует размер детектора см 
	int count;// число элктронов попавших в детектор
public:
	double x;
	double y; 
	double angle;
	bool active;

	Detector(void);
	Detector(double x,double y,double size);

	bool isActive()  { return active; }
	void setActive(bool val) { active = val; }
	double getSize();
	void setSize(double w);
	int getCount();
	void setCount(int n);

	void incCount();
	double* sec(double x,double y,double fi);
	bool isIn(double x,double y,double fi);
	bool Detector::isIn(double x,double y);
	double* borders();// границы детектора
	void resetCount();
	static double maxY(Detector* det,int n){
		double max=det[0].y;
		for (int i=1;i<n;i++)
		{
			if(det[i].y>max) max=det[i].y;
		}
		return max;
	};
	void output(ofstream& of);
	void input(ifstream& in);
	~Detector(void);
};

