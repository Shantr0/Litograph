#include "StdAfx.h"
#include "Node.h"
//#include <fstream>

Node::Node(void)
{
	x=y=angle=energy=0;
}
Node::Node(double x,double y,double angle){
	this->x=x;
	this->y=y;
	this->angle=angle;
	energy=0;
}

bool Node::operator < (Node node){
	return x<node.x;
}
bool Node::operator == (Node node){
	return (x=node.x)&&(y==node.y) && (node.energy==energy) && (node.angle==angle);
}
void Node::operator = (Node node){
	x=node.x;
	y=node.y;
	angle=node.angle;
	energy=node.energy;
}
//void Node::write(ofstream& of){
//	of.write((char*)&x,sizeof(double));
//	of.write((char*)&y,sizeof(double));
//	of.write((char*)&angle,sizeof(double));
//	of.write((char*)&energy,sizeof(double));
//}
void Node::output(ofstream& of){
	of<<x<<" ";
	of<<y<<" ";
	of<<angle<<" ";
	of<<energy<<"\n";
}
//
void Node::input(ifstream& in){
	in>>x;
	in>>y;
	in>>angle;
	in>>energy;
}
Node::~Node()
{
	//x=y=energy=angle=0;
}
