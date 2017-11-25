#pragma once
#include "relief2d.h"
class Relief3D
{
protected:
	double* x;
	double* y;
	double* z;
	int size1,size2;
public:
	Relief3D(void);
	Relief3D(double* X,double* Y,double* Z,int size1,int size2);
	Relief3D(double** X,double** Y,double** Z,int size1,int size2);
	double getY(double X,double Z);
	double getX(int i);
	double getY(int i);
	double getZ(int i);
	int getSize1();
	int getSize2();
	bool isInMaterial(double X,double Y,double Z);
	//Relief3D(double minX,double maxX,double* Y,int n);
	static Relief3D* generationSteps(double height,double widthHigh,double widthLow,double period,double thickness,int n,int m){
		double** X=new double*[m];
		double** Y=new double*[m];
		double** Z=new double*[m];
		int size1=m;
		 int size2=4*n+2;
		//size=size1*size2;
		double dx=(widthLow-widthHigh)/2;
		double dz=thickness/m;
		for(int j=0;j<m;j++){
			X[j]=new double[size2];
			Y[j]=new double[size2];
			Z[j]=new double[size2];
			X[j][0]=-0.0001;
			Y[j][0]=0.0;
			Z[j][0]=thickness/2;
			for (int i=0;i<n;i++)
			{
				X[j][i*4+1]=i*(widthHigh+period);
				Y[j][i*4+1]=0.0;
				Z[j][i*4+1]=Z[j][0]+j*dz;
				X[j][i*4+2]=X[j][i*4+1]+dx;
				Y[j][i*4+2]=height;
				Z[j][i*4+2]=Z[j][0]+j*dz;
				X[j][i*4+3]=X[j][i*4+2]+widthHigh;
				Y[j][i*4+3]=height;
				Z[j][i*4+3]=Z[j][0]+j*dz;
				X[j][i*4+4]=X[j][i*4+3]+dx;
				Y[j][i*4+4]=0.0;
				Z[j][i*4+4]=Z[j][0]+j*dz;
			}
			X[j][4*n+1]=X[j][4*n]<0.001 ? 0.001 : X[j][4*n];
			Y[j][4*n+1]=Y[j][0]=0.0;
			Z[j][4*n+1]=Z[j][0]+j*dz;
			//X[0]=-X[4*n+1];
		}
		Relief3D* rel=new Relief3D(X,Y,Z,size1,size2);
		delete X;
		delete Y;
		delete Z;
		return rel;
	}
	static Relief3D* defaultRelief(){
		double* x=new double[4];
		double* y=new double[4];
		double* z=new double[4];
		x[0]=x[3]=-8e-3;
		z[0]=z[1]=8e-3;
		x[1]=x[2]=8e-3;
		z[2]=z[3]=-8e-3;
		y[0]=y[1]=y[2]=y[3]=0.0;
		Relief3D* rel=new Relief3D(x,y,z,2,2);
		delete x;
		delete y;
		delete z;
		return rel;
	}
	static Relief3D* generationSteps(double height,double width,double period,double thickness,int n,int m){
		double size1=m;
		double** X=new double*[m];
		double** Y=new double*[m];
		double** Z=new double*[m];
		double size2=4*n+2;
		double dz=thickness/m;
		for (int j=0;j<m;j++)
		{
			X[j]=new double[size2];
			Y[j]=new double[size2];
			Z[j]=new double[size2];
			X[j][0]=-0.0001;
			Y[j][0]=0.0;
			Z[j][0]=thickness/2;
			for (int i=0;i<n;i++)
			{
				X[j][i*4+1]=i*(width+period);
				Y[j][i*4+1]=0.0;
				Z[j][i*4+1]=Z[0][0]+j*dz;
				X[j][i*4+2]=X[j][i*4+1];
				Y[j][i*4+2]=height;
				Z[j][i*4+2]=Z[0][0]+j*dz;
				X[j][i*4+3]=X[j][i*4+2]+width;
				Y[j][i*4+3]=height;
				Z[j][i*4+3]=Z[0][0]+j*dz;
				X[j][i*4+4]=X[j][i*4+3];
				Y[j][i*4+4]=0.0;
				Z[j][i*4+4]=Z[0][0]+j*dz;
			}
			X[j][4*n+1]=X[j][4*n]<0.001 ? 0.001 : X[j][4*n];
			Y[j][4*n+1]=Y[j][0]=0.0;
			X[j][0]=-X[j][4*n+1];
			Z[j][4*n+1]=Z[0][0]+j*dz;
		}
		Relief3D* rel=new Relief3D(X,Y,Z,size1,size2);
		delete X;
		delete Y;
		delete Z;
		return rel;
	}
	void read(ifstream& in);
	void write(ofstream& of);
	~Relief3D(void);
};

