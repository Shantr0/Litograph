#pragma once
#include "Node.h"

class Relief2D
{
protected:
	double* x;
	double* y;
	int size;
public:
	Relief2D(void);
	Relief2D(double* X,double* Y,int size);
	Relief2D(double minX,double maxX,double* Y,int n);
	static Relief2D* generationSteps(double height,double widthHigh,double widthLow,double period,int n){
		double* X=new double[4*n+2];
		double* Y=new double[4*n+2];
		X[0]=-0.0001;
		Y[0]=0.0;
		double d=(widthLow-widthHigh)/2;
		for (int i=0;i<n;i++)
		{
			X[i*4+1]=i*(widthHigh+period);
			Y[i*4+1]=0.0;
			X[i*4+2]=X[i*4+1]+d;
			Y[i*4+2]=height;
			X[i*4+3]=X[i*4+2]+widthHigh;
			Y[i*4+3]=height;
			X[i*4+4]=X[i*4+3]+d;
			Y[i*4+4]=0.0;
		}
		X[4*n+1]=X[4*n]<0.001 ? 0.001 : X[4*n];
		Y[4*n+1]=Y[0]=0.0;
		X[0]=-X[4*n+1];
		Relief2D* rel=new Relief2D(X,Y,4*n+2);
		delete X;
		delete Y;
		return rel;
	}
	static Relief2D* defaultRelief(){
		double* x=new double[2];
		double* y=new double[2];
		x[0]=-8e-1;
		x[1]=8e-1;
		y[0]=y[1]=0.0;
		return new Relief2D(x,y,2);
	}
	double getMaxY();
	static Relief2D* generationSteps(double height,double width,double period,int n){
		double* X=new double[4*n+2];
		double* Y=new double[4*n+2];
		X[0]=-0.0001;
		Y[0]=0.0;
		for (int i=0;i<n;i++)
		{
			X[i*4+1]=i*(width+period);
			Y[i*4+1]=0.0;
			X[i*4+2]=X[i*4+1];
			Y[i*4+2]=height;
			X[i*4+3]=X[i*4+2]+width;
			Y[i*4+3]=height;
			X[i*4+4]=X[i*4+3];
			Y[i*4+4]=0.0;
		}
		X[4*n+1]=X[4*n]<0.001 ? 0.001 : X[4*n];
		Y[4*n+1]=Y[0]=0.0;
		X[0]=-X[4*n+1];

		return new Relief2D(X,Y,4*n+2);
	}
	static Relief2D* generateRandom(double minHeight,double maxHeight, double width,int intervalsCount){
		Relief2D* relief;
		double dx=width/intervalsCount;
		int size=intervalsCount+1;
		double* x=new double[size];
		double* y=new double[size];
		double x0=-width/2;
		for (int i=0;i<size;i++){
			x[i]=x0+i*dx;
			y[i]=random(minHeight,maxHeight);
		}
		relief=new Relief2D(x,y,size);
		return relief;
	}
	static double random(double min,double max){
		double rnd=rand()/((double) RAND_MAX);
		double k=max-min;
		rnd=rnd*k+min;
		return rnd;
	}
	double getX(int i);
	double getY(int i);
	double getY(double xi);
	void setX(int i,double val);
	void setY(int i,double val);
	void setXY(double* X,double *Y,int n);
	double* getX();
	double* getY();
	bool isInMaterial(double X,double Y);
	bool isInMaterial(Node* p);
	double xIntersect(double k,double x0,double y0,short step); // пресечение kx+y0 рельефа
	double getSize();
	void clear();
	void write(ofstream& of);
	void read(ifstream& in);
	~Relief2D(void);
};

