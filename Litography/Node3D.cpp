#include "StdAfx.h"
#include "Node3D.h"


Node3D::Node3D(void)
{
	x=y=z=energy=angle=azimutAngle=0;
}
Node3D::Node3D(double x,double y,double z,double angle,double azimutAngle){
	this->x=x;
	this->y=y;
	this->z=z;
	this->angle=angle;
	this->azimutAngle=azimutAngle;
	energy=0;
}
bool Node3D::operator < (Node3D node){
	return y<node.y;
}
bool Node3D::operator == (Node3D node){
	return (x=node.x)&&(y==node.y)&&(z==node.z) && (node.energy==energy) &&(node.angle==angle)&&(node.azimutAngle==azimutAngle);
}

void Node3D::input(ifstream& in){
	in>>x;
	in>>y;
	in>>z;
	in>>angle;
	in>>azimutAngle;
	in>>energy;
}
void Node3D::output(ofstream& of){
	of<<x<<" ";
	of<<y<<" ";
	of<<z<<" ";
	of<<angle<<" ";
	of<<azimutAngle<<" ";
	of<<energy<<"\n";
}
Node3D::~Node3D(void)
{
}
