#include "StdAfx.h"
#include "Ray.h"
#include <list>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

double random(){
	return rand()/((double) RAND_MAX);
}
double random(double min,double max){
	double r=rand()/((double) RAND_MAX);
	return r*(max-min)+min;
}

Ray::Ray(double initialEnergy)
{
	Ray();
	points->back().energy=initialEnergy;
	//energy->insert(energy->begin(),0);
}
Ray::Ray()
{
	points=new list<Node>();
	Node* p=new Node();
	points->insert(points->end(),*p);
}
Ray::Ray(Node** nodes,int count){
	points=new list<Node>();

	for(int i=0;i<count;i++)points->insert(points->end(),*nodes[i]);
}
void Ray::addTraectory(double teta,double ds){// новая траеткория электрона
	Node* p=&points->back();// последняя точка
	double alpha=p->angle;//angle->back();// поворот СК
	double xn=sin(teta)*ds;// координаты
	double yn=-cos(teta)*ds;// в новой системе
	double xi,yi;
	xi=xn*cos(alpha)-yn*sin(alpha)+p->x;
	yi=xn*sin(alpha)+yn*cos(alpha)+p->y;
	alpha+=teta;
	Node* node=new Node(xi,yi,alpha);
	//node->s=ds;// для отладки
	points->insert(points->end(),*node);
}
int Ray::getTraectoryCount(){
	return points->size();
}
double Ray::generateAngle(){
	double angle;
	double a=random();
	if (a<0.99) angle=random(M_PI/90,M_PI/18);
	else angle=random(M_PI/18,M_PI/2);
	if(random()<0.5)angle=-angle;
	return angle;
}
double Ray::generateAngle(double alpha){
	double angle,k;
	double a=random();
	k=1-(2*alpha*a/(1-a+alpha));
	//if(k<-1 || a==1.0)k=-1;
	angle=acos(k);
	if(random()>0.5)angle=-angle;

	return angle;
}
//void Ray::addEnergy(double E){
//	energy->insert(energy->end(),E);
//}
Ray Ray::operator = (Ray ray){
	this->points=ray.points;
	return *this;
}
//void Ray::write(ofstream& of){
//	list<Node>::iterator p=points->begin();
//	list<Node>::iterator prEnd=points->end();
//	//copy(p,prEnd, ostream_iterator<Node>(of,"\n"));
//	int n=getTraectoryCount();
//	of.write((char*)&n,sizeof(int));
//	while(p!=prEnd){
//		p->write(of);
//		p++;
//	}
//}
//void Ray::read(ifstream& in){
//	points=new list<Node>();
//	Node* node=new Node();
//	int n;
//	in.read((char*)&n, sizeof(int));
//	for(int i=0;i<n;i++){
//		node->read(in);
//		points->insert(points->end(),*node);
//	}
//}
void Ray::output(ofstream& of){
	list<Node>::iterator p=points->begin();
	list<Node>::iterator prEnd=points->end();
	//copy(p,prEnd, ostream_iterator<Node>(of,"\n"));
	int n=getTraectoryCount();
	of<<n;
	of<<"\n";
	while(p!=prEnd){
		p->output(of);
		p++;
	}
}
void Ray::input(ifstream& in){
	//points=new list<Node>();
	Node* node=new Node();
	int n;
	in>>n;
	node->input(in);
	points->begin()->operator = (*node);
	for(int i=1;i<n;i++){
		node->input(in);
		points->insert(points->end(),*node);
	}
}
void Ray::clear(){
	//list<Node>::iterator end=points->end();
	//list<Node>::iterator it=points->begin();
	//list<Node>::iterator del;
	points->clear();
	//delete points;
	
	//while (it!=end)
	//{
	//	//p=(Node*)(&points->erase(it1))->_Ptr;
	//	//delete p;
	//	points->erase(it);
	//	it++;
	//}
	//points->erase(points->begin(),points->begin());
}
Ray::~Ray(){
	//points->erase(points->begin(),points->begin());
	clear();
	delete points;
	points=NULL;
}