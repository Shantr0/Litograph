#include <fstream>
using namespace std;

class Node3D 
{
public:
	double x;// координата х
	double y;// координата у
	double angle;// угол
	double energy;// энергия в узле
	double z;
	double azimutAngle;

	//double s;

	Node3D(void);
	Node3D(double x,double y,double z,double angle,double azimutAngle);
	bool operator < (Node3D node);
	bool operator == (Node3D node);
	void input(ifstream& in);
	void output(ofstream& of);
	~Node3D(void);
};

