#include "StdAfx.h"
#include "Relief3D.h"


Relief3D::Relief3D(void)
{
	x=y=z=0;
	size1=0;
	size2=0;
}
Relief3D::Relief3D(double* X,double* Y,double* Z,int size1,int size2){
	int n=size1*size2;
	this->size1=size1;
	this->size2=size2;
	x=new double[n];
	y=new double[n];
	z=new double[n];
	for (int i=0;i<n;i++)
	{
		x[i]=X[i];
		y[i]=Y[i];
		z[i]=Z[i];
	};
}
Relief3D::Relief3D(double** X,double** Y,double** Z,int size1,int size2){
	int size=size1*size2;
	this->size1=size1;
	this->size2=size2;
	x=new double[size];
	y=new double[size];
	z=new double[size];
	for(int i=0;i<size1;i++)
		for (int j=0;j<size2;j++)
		{
			x[i*size2+j]=X[i][j];
			y[i*size2+j]=Y[i][j];
			z[i*size2+j]=Z[i][j];
		};
}
double Relief3D::getX(int i){return x[i];}
double Relief3D::getY(int i){return y[i];}
double Relief3D::getZ(int i){return z[i];}
int Relief3D::getSize1(){
	return size1;
}
int Relief3D::getSize2(){
	return size2;
}
void Relief3D::write(ofstream& of){
	of<<size1<<" ";
	of<<size2<<"\n";
	int size=size1*size2;
	for (int i=0;i<size;i++)
	{
		of<<x[i]<<" ";
		of<<y[i]<<" ";
		of<<z[i]<<"\n";
	}
}
void Relief3D::read(ifstream& in){
	in>>size1;
	in>>size2;
	int n=size1*size2;
	x=new double[n];
	y=new double[n];
	z=new double[n];
	for (int i=0;i<n;i++)
	{
		in>>x[i];
		in>>y[i];
		in>>z[i];
	}
}
bool Relief3D::isInMaterial(double X,double Y,double Z){
	bool res=(Y<getY(X,Z));
	return res;
}


double Relief3D::getY(double X,double Z){
	int i,j;
	j=i=1;
	while (X>x[i] && i<size1)i++;// x[i] x[i-1]
	while (Z>z[j*size1+i] && j<size2)j++;// z[(j-1)n1] z[jn1]
	int ind0=(j-1)*size1+i;
	int ind1=j*size1+i;
	double k=(y[ind0]-y[ind0-1])/(x[ind0]-x[ind0-1]);// на отрезке x[i-1] x[i] => z[j-1]
	double Y0=k*(X-x[ind0-1])+y[ind0-1];
	k=(y[ind1]-y[ind1-1])/(x[ind1]-x[ind1-1]);
	double Y1=k*(X-z[ind1-1])+y[ind1-1];
	k=(Y1-Y0)/(z[ind1]-z[ind0]);
	double Y=k*(Z-z[ind0])+Y0;
	return Y;
}


Relief3D::~Relief3D(void)
{
	delete x;
	delete y;
	delete z;
}
