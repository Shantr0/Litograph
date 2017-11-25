#include "StdAfx.h"
#include "Relief2D.h"


	
Relief2D::Relief2D(){
	x=y=0;
	size=0;
}
Relief2D::Relief2D(double minX,double maxX,double* Y,int n){
	double dx=(maxX-minX)/(n-1);
	size=n;
	x=new double[n];
	y=new double[n];
	x[0]=minX;
	for (int i=1;i<n;i++)
	{
		x[i]=x[i-1]+dx;
		y[i]=Y[i];
	}
}
Relief2D::Relief2D(double* X,double* Y,int n){
	x=new double[n];
	y=new double[n];
	size=n;
	for (int i=0;i<n;i++)
	{
		x[i]=X[i];
		y[i]=Y[i];
	}
}

double Relief2D::getX(int i){return x[i];}
double Relief2D::getY(int i){return y[i];}
double Relief2D::getY(double xi){
	int i=1;
	while (xi>x[i] && i<size)i++;
	double k=(y[i]-y[i-1])/(x[i]-x[i-1]);
	double Yx=k*(xi-x[i-1])+y[i-1];
	return Yx;
}
void Relief2D::setX(int i,double val){x[i]=val;}
void Relief2D::setY(int i,double val){y[i]=val;}
void Relief2D::setXY(double* X,double *Y,int n){
	x=X;
	y=Y;
	size=n;
}
double* Relief2D::getX(){return x;}
double* Relief2D::getY(){return y;}
bool Relief2D::isInMaterial(double X,double Y){// находится ли частица с соот. координатами в образце
	if(X<x[0] || X>x[size-1])return false;
	return Y<=getY(X);
}
bool Relief2D::isInMaterial(Node* p){
	if(p->x<x[0] || p->x>x[size-1])return false;
	return p->y<=getY(p->x);
}
double Relief2D::getMaxY(){
	double m=y[0];
	for(int i=1;i<size;i++)
		if (y[i]>m)
			m=y[i];
	return m;
}
double Relief2D::xIntersect(double k,double x0,double y0,short step){
	double x1=x0;
	int start=0;
	if(x0<x[0])start=0;
	else if(x0>x[size-1])start=size;
	else while( x0>x[start])start++;
	int i=start;
	if (step>0)
	{
		i--;
		do{
			i++;
			double kr=(y[i]-y[i-1])/(x[i]-x[i-1]);
			x1=(k*x0-kr*x[i-1]+y[i-1]-y0)/(k-kr);// точка пересечения интервала рельефа и прямой
			
		}while(i<size && (x0>x1 || x1>x[i] || x1<x[i-1]));// цикл продолжится если точка в интервале
		if(x1<x[i]&& x1>x[i-1] && x1>x0)return x1;
		else return std::numeric_limits<double>::infinity();
	}else{
		do{
			i--;
			double kr=(y[i+1]-y[i])/(x[i+1]-x[i]);
			x1=(k*x0-kr*x[i]+y[i]-y0)/(k-kr);// точка пересечения интервала рельефа и прямой
		}while((x1>x[i+1] || x1<x[i] || x0<x1)&& i>0 );// цикл продолжится если точка не в интервале
		if(x1<x[i+1]&& x1>x[i] && x1<x0)return x1;
		else return -std::numeric_limits<double>::infinity();
	}
}
double Relief2D::getSize(){return size;}
void Relief2D::clear(){
	if(x)delete x;
	if(y)delete y;
	size=0;
}
void Relief2D::write(ofstream& of){
	of<<size<<"\n";
	for (int i=0;i<size;i++)
	{
		of<<x[i]<<" ";
		of<<y[i]<<"\n";
	}
}
void Relief2D::read(ifstream& in){
	in>>size;
	x=new double[size];
	y=new double[size];
	for (int i=0;i<size;i++)
	{
		in>>x[i];
		in>>y[i];
	}
}
Relief2D::~Relief2D(){
	if(x)delete x;
	if(y)delete y;
	size=0;
	x=y=0;
}
