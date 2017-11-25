#pragma once
#include "SampleParameters.h"
#include <limits>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "Detector.h"

#define DOSE_DISTRIBUTION 0
namespace Litography {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms::DataVisualization::Charting;

	/// <summary>
	/// Summary for AnalyseWindow
	/// </summary>
	public ref class AnalyseWindow : public System::Windows::Forms::Form
	{
	private: 		
		SampleParameters* sample;
		double width,height,minX,maxY;
		Detector* det;
		int type;
		double E0,Ecr;
		double widthBundle,xBundle,yBundle;
		int count;	
		//void *analyseFunction;




	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::TextBox^  textBoxBegin;
	private: System::Windows::Forms::TextBox^  textBoxEnd;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownIntervalsCount;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownX;

	private: System::Windows::Forms::NumericUpDown^  numericUpDownY;
	private: System::Windows::Forms::ProgressBar^  progressBar1;





	public:

		AnalyseWindow(SampleParameters* sample,double minX,double width,double maxY,double height)
		{
			InitializeComponent();
			this->sample=sample;
			this->minX=minX;
			this->maxY=maxY;
			this->width=width;
			this->height=height;
			count=sample->getRaysCount();
			type=0;// распределение доз
			numericUpDownIntervalsCount->Visible=false;
			label3->Visible=false;
		}
		AnalyseWindow(SampleParameters* sample,double E0,double Ecr,double widthBundle,double xBundle,double yBundle,Detector* det)
		{
			InitializeComponent();
			this->sample=sample;
			this->E0=E0;
			this->Ecr=Ecr;
			this->widthBundle=widthBundle;
			this->xBundle=xBundle;
			this->yBundle=yBundle;
			this->det=det;
			count=sample->getRaysCount();
			type=1;//сканирование 
			numericUpDownX->Visible=false;
			numericUpDownY->Visible=false;
			label1->Visible=false;
			label2->Visible=false;
		}
		AnalyseWindow(int type)
		{
			InitializeComponent();
			this->type=type;// длины пробега

		}
	protected:
		double sqr(double x){
			return x*x;
		};
		double isodose(double e0,double e1,double r){
			return e0-e1;
		}
		void maxXY(double &maxX,double &minY,SampleParameters* sample){
			list<Node>::iterator point=sample->rays[0].points->begin()++;
			//list<double>::iterator itY=sample->rays[0].y->begin();
			maxX=point->x;
			minY=point->y;
			int n=sample->getRaysCount();
			for(int i=0;i<n;i++){
				point=sample->rays[i].points->begin();
				//itY=sample->rays[i].y->begin();
				for(;point!=sample->rays[i].points->end();point++){
					if (maxX<abs(point->x) && sample->relief->isInMaterial(point->x,point->y)) maxX=abs(point->x);
					if (minY>(point->y)) minY=point->y;
				}
			}
		}
		void incByCondition(bool &cond,int &val){
			if(!cond){
				val++;
				cond=true;
			}
		}
		void allocationParticleByY(int raysCount,int pointsCount,int*& rays,double*& eSum){// распределение доз по глубине образца
			rays=new int[pointsCount];// объявление и инициализация
			bool* isIn=new bool[pointsCount];
			double* Y=new double[pointsCount];
			eSum=new double[pointsCount];
			eSum[0]=0.0;
			Y[0]=0.0;
			rays[0]=raysCount;
			isIn[0]=true;
			double dy=height/(pointsCount-1);

			for(int i=1;i<pointsCount;i++){
				rays[i]=0;
				eSum[i]=0.0;
				Y[i]=Y[i-1]+dy;
			}
			for(int i=0;i<raysCount;i++){// проход по лучам
				list<Node>::iterator itp=sample->rays[i].points->begin();
				list<Node>::iterator prEnd=sample->rays[i].points->end();
				prEnd--;
				for(int j=1;j<pointsCount;j++) isIn[j]=false;
				int a=0;
				double E=itp->energy;
				eSum[0]+=E;
				//double Ei=E;//  
				while (itp!=prEnd)// проход по узлам
				{
					double x0=itp->x;
					double y0=itp->y;
					E=itp->energy;
					int m=0;
					int n=0;
					while(Y[m]>y0)m++;// определяем номер точки через которую проходит луч
					if(m>0 && Y[m]!=y0)m--;
					incByCondition(isIn[m],rays[m]);

					//list<Node>::iterator itPrev=itp;
					itp++;
					double x1=itp->x;
					double y1=itp->y;
					double s=sqrt(sqr(x1-x0)+sqr(y1-y0));
					double l=0;
					while(Y[n]>=y1)n++;n--;
					double dE=sample->energieLossUnit(E);// энергия на единичный участок  до следующего узла
					if (y1 <= Y[m] && y1 > Y[m+1])// следующий узел в этом же интервале
					{
						if(y1==Y[m]){
							eSum[m]+=E;
							incByCondition(isIn[m],rays[i]);
						}
						a++;
						continue;
					} 
					else if(y1 <= Y[m])// следующий узел находится ниже
					{
						double k=(y1-y0)/(x1-x0);
						m++;
						double r,E0;
						do{
							
							y1=Y[m];
							x1=(y1-y0)/k+x0;// новая координата на границе
							r=sqrt(sqr(x1-x0)+sqr(y1-y0));// квадрат расстояния до следующей точки
							l+=r;
							//dE*=r;// потеря энергии
							E-=r*dE;
							eSum[m]+=E;// энергия в точке ym
							//elossI+=dE;
							x0=x1;
							y0=y1;
							incByCondition(isIn[m],rays[m]);
							m++;
							//s+=r;
							//dE2+=dE;
						} while(itp->y <= Y[m] && m<pointsCount);
						x1=itp->x;
						y1=itp->y;
						r=sqrt(sqr(x1-x0)+sqr(y1-y0));// расстояние до следующей точки
						//dE=sample->energieLossUnit(E)*r;// потеря энергии
						//E=itp->energy;
						//eSum[m]+=dE;
						//dE2+=dE;
					}
					else{// узел выше
						double k=(y1-y0)/(x1-x0);
						double r;
						//m--;
						//double l=sqrt(sqr(y1-y0)+sqr(x1-x0));
						//s=0;
						do{
							//m++;
							y1=Y[m];
							x1=(y1-y0)/k+x0;// новая координата на границе
							r=sqrt(sqr(x1-x0)+sqr(y1-y0));//  расстояниe до следующей точки
							E-=dE*r;// потеря энергии
							eSum[m]+=E;
							//elossI+=dE;
							x0=x1;
							y0=y1;
							incByCondition(isIn[m],rays[m]);
							m--;
							l+=r;
						}
						while(itp->y >= Y[m] && m>=0);
						x1=itp->x;
						y1=itp->y;
						r=sqrt(sqr(x1-x0)+sqr(y1-y0));// квадрат расстояния до следующей точки
						//dE*=r;// потеря энергии
						//E-=dE;
						//eSum[m]+=dE;
					}
					//rays[m]++;
					a++;
				}
			}
			delete isIn;
			delete Y;
			//return rays;
		}
		void allocationParticle(int raysCount,int intervCountX,int intervCountY,double**& eSum){
			eSum[0]=new double[intervCountX];
			eSum[1]=new double[intervCountY];
			int* intervalsY=new int[intervCountY];
			double dx=width/intervCountX;
			double dy=height/intervCountY;
			if(intervCountX>intervCountY){
				for(int i=0;i<intervCountY;i++){
			//		intervalsX[i]=0;
					intervalsY[i]=0;
					eSum[0][i]=0.0;
					eSum[1][i]=0.0;
				} 
				for(int i=intervCountY;i<intervCountX;i++){
				//	intervalsX[i]=0;
					eSum[0][i]=0.0;
				}
			}else{
				for(int i=0;i<intervCountX;i++){
				//	intervalsX[i]=0;
					intervalsY[i]=0;
					eSum[0][i]=0.0;
					eSum[1][i]=0.0;
				} 
				for(int i=intervCountX;i<intervCountY;i++){
					intervalsY[i]=0;
					eSum[1][i]=0.0;
				}
			}
			for(int i=0;i<raysCount;i++){// проход по лучам
				list<Node>::iterator itp=sample->rays[i].points->begin();
				list<Node>::iterator prEnd=sample->rays[i].points->end();
				//double E0=itp->energy;
				prEnd--;
				//int a=0;
				int m,k;
				bool isAddedX,isAddedY;
				isAddedY=isAddedX=false;
				while (itp!=prEnd)// проход по узлам
				{
					double E=itp->energy;
					double x0=itp->x;
					double y0=itp->y;
					m=k=0;
					itp++;
					double x1,y1;
					x1=itp->x;
					y1=itp->y;
					for(double x=-width/2+dx ; x<x0 ; x+=dx) m++;// определяем номер интервала
					for(double y=dy;y0<y;y+=dy) k++;
					if(m==intervCountX) m--;// корректировка
					if(k==intervCountY) k--;
					if (!isAddedY){
						intervalsY[k]++;
						isAddedY=true;
					}
					//eSum[0][m]+=E;// потеря энергии в интервале
					//eSum[1][k]+=E;
					eSum[0][m]+=(E-itp->energy);// потеря энергии в интервале
					eSum[1][k]+=(E-itp->energy);
					//double dE1=0;
					//for(int i=0;i<intervCount;i++) dE1+=eSum[i];
					//double dE2=E0-itp->energy;
					//a++;
				}
			}
			//for(int i=0;i<raysCount;i++){}
		}
		void distributeRaysCount(int intervCountX,int intervCountY,int*& intervalsX,int*& intervalsY){// распределение числа частиц по интервалам
			intervalsX=new int[intervCountX];
			intervalsY=new int[intervCountY];
			double dx=width/intervCountX;
			double dy=height/intervCountY;
			double y0,y1;
			y0=0.0;
			y1=dy;
			for (int i=0;i<intervCountY;i++)
			{
				intervalsY[i]=0;
				for(int j=0;j<sample->getRaysCount();j++){
					list<Node>::iterator itp=sample->rays[j].points->begin();
					list<Node>::iterator prEnd=sample->rays[j].points->end();
					prEnd--;
					while((itp->y>y0 || itp->y<y1) && itp!=prEnd) 
						itp++;
					if(itp->y>=y1 && itp->y<=y0) intervalsY[i]++;
				}
				y0=(i+1)*dy;
				y1=y0+dy;
			}
		}
		void allocationElectronsCount(int intervCountE,int*& nSum){ // распределение частиц по спектру
			double E0=sample->rays[0].points->begin()->energy;
			double E,dE;
			dE=E0/intervCountE;
			nSum=new int[intervCountE];
			for(int i=0;i<intervCountE;i++) nSum[i]=0;
			for(int i=0;i<sample->getRaysCount();i++){
				list<Node>::iterator itp=sample->rays[i].points->begin();
				list<Node>::iterator itEnd=sample->rays[i].points->end();
				itEnd--;
				if(itEnd->y<0) continue;
				int j=0;
				E=E0;
				while(itp!=itEnd && j<intervCountE) {
					if(itp->energy<=E && itp->energy>=E-dE){
						E-=dE;
						nSum[j]++;
						j++;
					}else if(itp->energy<E-dE){
						E-=dE;
						j++;
						continue;
					}
					itp++;
				}
			}
		}
		void getNM(int& n,int& m,int N,int M,double X,double Y,double* x,double* y){// определяет индексы n m точки (X,Y) в интервалах x y  
			m=n=0;
			if(Y>=y[M] && Y<=y[0]) {
				while(y[m]>Y && m<M)m++;
				if(m>0)m--;
			}
			else m=-1;   // точка вне рассматриваемой области
			if(X>=x[0] && X<=x[M]){
				while(x[n+1]<X) 
					n++;
			}
			else n=-1;
			//if(x[n]==X)n--;
		}
		void calculateX(double** result,double& x0,double& y0,double x1,double *x,double *y,int& n,int m,double k,double E0,double E1){// рассчитать распределение изодоз(неправильно)
		// изодозы dE  отрезка [x0,x1] E x[n] x[n+1]  
			while(x1 < x[n] || x1 > x[n+1]){// луч уходит вправо или влево 
				//x1=(itp->x<x[n]) ? x[n] : x[n+1];
				double xloc,yloc;
				if(x1<x[n])xloc=x[n];// влево 
				else xloc=x[n+1];// вправо
				yloc=k*xloc+y[m+1];
				double r=sqrt(sqr(xloc-x0)+sqr(yloc-y0));//  расстояние до следующей точки
				result[m][n]+=isodose(E0,E1,r);
				y0=yloc;
				y0=xloc;
				if(x1<x[n])n--;
				else n++;
			}
		}
		double** allocation(int intervCountX,int intervCountY,double x0,double width,double y0,double height){//  распределение потерь энергии по ячейкам
			double* x=new double[intervCountX+1];
			double* y=new double[intervCountY+1];
			double dx=width/intervCountX;
			double dy=height/intervCountY;
			double** result=new double*[intervCountY];
			for(int i=0;i<intervCountY;i++){// инициализация нулями всех ячеек 
				result[i]=new double[intervCountX];
				y[i]=y0+i*dy;// и разбиение на у интервалы
			}
			y[intervCountY]=y[intervCountY-1]+dy;
			for(int i=0;i<intervCountY;i++)
				for(int j=0;j<intervCountX;j++) result[i][j]=0.0;
			int raysCount=sample->getRaysCount();
			for(int i=0;i<intervCountX+1;i++) x[i]=x0+i*dx; // разбиение на х интервалы
			for(int i=0;i<raysCount;i++){// проход по лучам
				list<Node>::iterator itp=++sample->rays[i].points->begin();
				list<Node>::iterator prEnd=--sample->rays[i].points->end();
				double E0,E1;
				while (itp!=prEnd)// проход по узлам
				{
					double X0=itp->x;
					double Y0=itp->y;
					E0=itp->energy;
					int m=0;
					int n=0;
					int i,j;
					//getNM(n,m,X0,Y0,x,y);// предыдущий индекс (не факт что нужен)
					//list<Node>::iterator itPrev=itp;
					itp++;
					double x1=itp->x;
					double y1=itp->y;
					E1=itp->energy;
					getNM(i,j,intervCountX,intervCountY,x1,y1,x,y);// индекс ячейки
					if(i!=-1 && j!=-1)result[i][j]+=E0-E1;
					double dE=sample->energieLossUnit(E0);// энергия на единичный участок  до следующего узла
					//double k=(y1-Y0)/(x1-X0);
					//if (y1 <= y[m] && y1 > y[m+1] && x1 >= x[n] && x1 <= x[n+1])// следующий узел в этой же ячейке
					//{
					//	double r=sqrt(sqr(x1-X0)+sqr(y1-Y0));// квадрат расстояния до следующей точки
					//	result[m][n]+=isodose(E0,E1,r);
					//} 
					//else if(y1 > y[m])// следующий узел находится выше  
					//{
					//	do{
					//		y1=y[m];	
					//		x1=(y1-Y0)/k+X0;// новая координата на границе
					//		calculateX(result,X0,Y0,x1,x,y,n,m,k,E0,E1);
					//		double r=sqrt(sqr(x1-X0)+sqr(y1-Y0));//  расстояние до следующей точки
					//		E1=E0-r*dE;
					//		result[m][n]+=isodose(E0,E1,r);
					//		X0=x1;
					//		Y0=y1;
					//		E0=E1;
					//		m--;
					//	}while(((itp->y > y[m]) || !(itp->x >= x[n] && itp->x < x[n+1])) && m<intervCountY  && n<intervCountX && m>=0 && n>=0 && sample->relief->isInMaterial(itp->x,itp->y));
					//	x1=itp->x;
					//	y1=itp->y;
					//	double r=sqrt(sqr(x1-X0)+sqr(y1-Y0));// расстояние до следующей точки
					//	E1=E0-r*dE;
					//	if(m>=0 && n>=0 && m<intervCountY  && n<intervCountX && sample->relief->isInMaterial(itp->x,itp->y)) result[m][n]+=isodose(E0,E1,r);
					//}else if(y1 < y[m+1])// узел ниже
					//{
					//	do{
					//		y1=y[m+1];	
					//		x1=(y1-Y0)/k+X0;// новая координата на границе
					//		calculateX(result,X0,Y0,x1,x,y,n,m,k,E0,E1);
					//		double r=sqrt(sqr(x1-X0)+sqr(y1-Y0));//  расстояние до следующей точки
					//		E1=E0-r*dE;
					//		result[m][n]+=isodose(E0,E1,r);
					//		X0=x1;
					//		Y0=y1;
					//		E0=E1;
					//		m++;
					//	}while(y1 < y[m+1] && m<intervCountY  && n<intervCountX && m>=0 && n>=0 && sample->relief->isInMaterial(itp->x,itp->y));
					//	x1=itp->x;
					//	y1=itp->y;
					//	E1=itp->energy;
					//	double r=sqrt(sqr(x1-X0)+sqr(y1-Y0));// расстояние до следующей точки
					//	if(m>=0 && n>=0 && m<intervCountY  && n<intervCountX && sample->relief->isInMaterial(itp->x,itp->y)) result[m][n]+=isodose(E0,E1,r);
					//	//while(((itp->y < y[m+1] || itp->y > y[m]) || !(itp->x >= x[n] && itp->x < x[n+1])) && m<intervCountY  && n<intervCountX && m>=0 && n>=0 && sample->relief->isInMaterial(itp->x,itp->y));
					//}else// на том же у уровне
					//{
					//	double k=(y1-Y0)/(x1-X0);
					//	//m++;
					//	double r;
					//	calculateX(result,X0,Y0,x1,x,y,n,m,k,E0,E1);
					//	x1=itp->x;
					//	y1=itp->y;
					//	E1=itp->energy;
					//	r=sqrt(sqr(x1-X0)+sqr(y1-Y0));// расстояние до следующей точки
					//	result[m][n]+=isodose(E0,E1,r);
					//}
				}
			}
			delete x;
			delete y;
			return result;
		}
		list<Node>** allocationEnergyDose(int countAlloc){  // распределение энергии по краям
			countAlloc=5;
			list<Node>** nodeList=new list<Node>*[countAlloc];
			for(int i=0;i<countAlloc;i++){
				nodeList[i]=new list<Node>();
			}
			int raysCount=sample->getRaysCount();
			double E0=sample->rays[0].points->begin()->energy;
			double E[]={0.5*E0,0.25*E0,0.15*E0,0.1*E0,0.05*E0};
			for(int i=0;i<raysCount;i++){
				int j=0;
				list<Node>::iterator itp=sample->rays[i].points->begin();
				list<Node>::iterator prEnd=sample->rays[i].points->end();
				prEnd--;
				while(itp!=prEnd && itp->energy>E[5] && j<countAlloc){
					if(itp->energy<E[j]){
						itp--;
						nodeList[j]->insert(nodeList[j]->end(),*itp);// добавление предыдущего узла
						itp++;
						j++;
					}
					itp++;
				}
			}
			return nodeList;
		}
		void filter(list<Node>** &nodes,int n){
			for (int i=0;i<n;i++)
			{
				nodes[i]->sort();
				list<Node>::iterator it1=nodes[i]->begin();
				list<Node>::iterator it2=it1;
				it1++;
				list<Node>::iterator end=nodes[i]->end();
				while(it1!=end){
					if(it2->y < it1->y)nodes[i]->remove(*it1);
					it2++;
					it1=*((&it2)-1);
				}
			}
		}
		int middle(list<Node>* node){
			list<Node>::iterator itp=node->begin();
			list<Node>::iterator itEnd=node->end();
			double min=itp->y;
			int mid=0;
			int i=0;
			for(;itp!=itEnd;itp++){
				if(itp->y<min){
					min=itp->y;
					mid=i;
				}
				i++;
			}
			return mid;
		}
		void visualizeDoseAlloc(){
			double E0=sample->rays[0].points->begin()->energy;
			//double dE=E0/ky;
			int m=5;
			short r[]={255,0,0,0,128,128};
			short g[]={0,255,0,128,0,128};
			short b[]={0,0,255,128,128,0};
			double E[]={0.5*E0,0.25*E0,0.15*E0,0.1*E0,0.05*E0};
			list<Node>** nodes=allocationEnergyDose(m);
			for(int i=0;i<m;i++){
				nodes[i]->sort();
				list<Node>::iterator it;
				list<Node>::iterator itBegin=nodes[i]->begin();
				list<Node>::iterator itEnd=nodes[i]->end();
				itEnd--;
				String^ name=100*(E[i]/E0)+"%";
				if(Histogram->Series->IndexOf(name)==-1)  Histogram->Series->Add(name);
				else Histogram->Series[i]->Points->Clear();
				Histogram->Series[i]->Color=Color::FromArgb(r[i],g[i],b[i]);
				Histogram->Series[i]->ChartType=DataVisualization::Charting::SeriesChartType::Line;
				int mid=middle(nodes[i]);
				int k;
				list<Node>::iterator itPrev;
				//Histogram->Series[i]->Points->AddXY(0,0);

				it=itBegin;
				Histogram->Series[i]->Points->AddXY(it->x,it->y);
				it++;
				k=1;
				itPrev=std::prev(it);
				while(k<mid){
					if((it->y < itPrev->y)){
						Histogram->Series[i]->Points->AddXY(it->x,it->y);
						itPrev=it;
					}
					it++;
					k++;
				}

				it=itEnd;
				Histogram->Series[i]->Points->AddXY(it->x,it->y);
				itPrev=it;
				it--;
				k=nodes[i]->size()-2;
				while(k>mid){
					if (it->y < itPrev->y)
					{
						Histogram->Series[i]->Points->AddXY(it->x,it->y);
						itPrev=it;
					}
					it--;
					k--;
				}
				Histogram->Series[i]->Sort(PointSortOrder::Ascending,"X");// сортировка по Х
				Histogram->Series[i]->Points->InsertXY(0,0,0);
				Histogram->Series[i]->Points->AddXY(0,0);
			}
		}
		
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AnalyseWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  Histogram;
	protected: 
	private: 

	protected: 
	private: System::Windows::Forms::Label^  label1;



	private: System::Windows::Forms::Button^  button1;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::Title^  title4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->Histogram = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->textBoxBegin = (gcnew System::Windows::Forms::TextBox());
			this->textBoxEnd = (gcnew System::Windows::Forms::TextBox());
			this->numericUpDownIntervalsCount = (gcnew System::Windows::Forms::NumericUpDown());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->numericUpDownX = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDownY = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Histogram))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownIntervalsCount))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownX))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownY))->BeginInit();
			this->SuspendLayout();
			// 
			// Histogram
			// 
			this->Histogram->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			chartArea2->AxisX->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::True;
			chartArea2->AxisX->IsStartedFromZero = false;
			chartArea2->AxisX->LabelStyle->Format = L"e2";
			chartArea2->AxisX->MajorGrid->LineColor = System::Drawing::Color::LightGray;
			chartArea2->AxisX->Maximum = 1;
			chartArea2->AxisX->Minimum = -1;
			chartArea2->AxisY->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::True;
			chartArea2->AxisY->IsStartedFromZero = false;
			chartArea2->AxisY->MajorGrid->LineColor = System::Drawing::Color::LightGray;
			chartArea2->Name = L"ChartArea1";
			this->Histogram->ChartAreas->Add(chartArea2);
			legend2->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			legend2->Name = L"Legend1";
			this->Histogram->Legends->Add(legend2);
			this->Histogram->Location = System::Drawing::Point(12, 27);
			this->Histogram->Name = L"Histogram";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->Color = System::Drawing::Color::Black;
			series3->Legend = L"Legend1";
			series3->Name = L"Доза";
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series4->Enabled = false;
			series4->Legend = L"Legend1";
			series4->Name = L"Промежуточная доза";
			this->Histogram->Series->Add(series3);
			this->Histogram->Series->Add(series4);
			this->Histogram->Size = System::Drawing::Size(590, 384);
			this->Histogram->TabIndex = 0;
			this->Histogram->Text = L"chart1";
			title3->Alignment = System::Drawing::ContentAlignment::TopLeft;
			title3->Name = L"Title1";
			title3->Text = L"E, кэВ";
			title4->Alignment = System::Drawing::ContentAlignment::TopCenter;
			title4->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			title4->Name = L"Title2";
			title4->Text = L"y, мкм";
			this->Histogram->Titles->Add(title3);
			this->Histogram->Titles->Add(title4);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(616, 31);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(123, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"число интервалов по X";
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(631, 425);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(108, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"расчет";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &AnalyseWindow::button1_Click);
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(616, 98);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(123, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"число интервалов по Y";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(751, 24);
			this->menuStrip1->TabIndex = 8;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// textBoxBegin
			// 
			this->textBoxBegin->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->textBoxBegin->Location = System::Drawing::Point(12, 425);
			this->textBoxBegin->Name = L"textBoxBegin";
			this->textBoxBegin->Size = System::Drawing::Size(66, 20);
			this->textBoxBegin->TabIndex = 9;
			this->textBoxBegin->Text = L"-0.00015";
			// 
			// textBoxEnd
			// 
			this->textBoxEnd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->textBoxEnd->Location = System::Drawing::Point(524, 425);
			this->textBoxEnd->Name = L"textBoxEnd";
			this->textBoxEnd->Size = System::Drawing::Size(78, 20);
			this->textBoxEnd->TabIndex = 10;
			this->textBoxEnd->Text = L"0.0003";
			// 
			// numericUpDownIntervalsCount
			// 
			this->numericUpDownIntervalsCount->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->numericUpDownIntervalsCount->Location = System::Drawing::Point(631, 391);
			this->numericUpDownIntervalsCount->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100000, 0, 0, 0});
			this->numericUpDownIntervalsCount->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDownIntervalsCount->Name = L"numericUpDownIntervalsCount";
			this->numericUpDownIntervalsCount->Size = System::Drawing::Size(108, 20);
			this->numericUpDownIntervalsCount->TabIndex = 11;
			this->numericUpDownIntervalsCount->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(628, 360);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(98, 13);
			this->label3->TabIndex = 12;
			this->label3->Text = L"число интервалов";
			// 
			// progressBar1
			// 
			this->progressBar1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->progressBar1->Location = System::Drawing::Point(84, 425);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(434, 20);
			this->progressBar1->TabIndex = 13;
			// 
			// numericUpDownX
			// 
			this->numericUpDownX->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->numericUpDownX->Location = System::Drawing::Point(619, 55);
			this->numericUpDownX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100000, 0, 0, 0});
			this->numericUpDownX->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDownX->Name = L"numericUpDownX";
			this->numericUpDownX->Size = System::Drawing::Size(120, 20);
			this->numericUpDownX->TabIndex = 2;
			this->numericUpDownX->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			// 
			// numericUpDownY
			// 
			this->numericUpDownY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->numericUpDownY->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {100000, 0, 0, 0});
			this->numericUpDownY->Location = System::Drawing::Point(619, 127);
			this->numericUpDownY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100000, 0, 0, 0});
			this->numericUpDownY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDownY->Name = L"numericUpDownY";
			this->numericUpDownY->Size = System::Drawing::Size(120, 20);
			this->numericUpDownY->TabIndex = 7;
			this->numericUpDownY->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			// 
			// AnalyseWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(751, 460);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->numericUpDownIntervalsCount);
			this->Controls->Add(this->textBoxEnd);
			this->Controls->Add(this->textBoxBegin);
			this->Controls->Add(this->numericUpDownY);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->numericUpDownX);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Histogram);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"AnalyseWindow";
			this->Text = L"AnalyseWindow";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Histogram))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownIntervalsCount))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownX))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownY))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void save(double* I,int n) {
			ofstream of;
			of.open("results.txt",ios::out);
			of<<n<<"\n";
			//of<<m<<"\n";
			/*for(int i=0;i<n;i++){
			for(int j=0;j<m;j++)
			of<<I[i][j]<<" ";
			}*/
			for(int j=0;j<n;j++)
				of<<I[j]<<" ";
			of<<"\n";
		}

		bool exist(String^ name){
			int ind= Histogram->Series->IndexOf(name);
			return ind!=-1;
		}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 //void (*pf)(int) = AnalyseWindow::&f;
				 Histogram->Series[0]->Points->Clear();
				 Histogram->Series[1]->Points->Clear();
				 int n;
				 switch(type)
				 {
				 case 0:// изодозы
					 {
						 int kx=(int)numericUpDownX->Value;
						 int ky=(int)numericUpDownY->Value;
						 n=sample->getRaysCount();
						 //double* energy;
						 int* intervalsX,*intervalsY,*specter;
						 //intervals=allocationParticle(n,kx,specter);
						 list<Node>::iterator begin=sample->rays[0].points->begin();
						 list<Node>::iterator end=sample->rays[0].points->end();
						 end--;
						 //double x0,y0;
						 //maxXY(x0,y0,sample);
						 //x0=Histogram->ChartAreas[0]->AxisX->Minimum;
						 //y0=Histogram->ChartAreas[0]->AxisY->Maximum;
						 double** a=allocation(kx,ky,minX,width,maxY,-height);
						 //double dE= begin->energy - end->energy;
						 //allocationParticleByY(n,ky,specter,energy);
						 //distributeRaysCount(kx,ky,intervalsX,intervalsY);
						 //allocationElectronsCount(ky,specter);
						 //
						 Graphics^ g=Histogram->CreateGraphics();
						 int sizeX,sizeY;
						 sizeX=Histogram->Width/kx;// размеры 1-го 
						 sizeY=Histogram->Height/ky;// прямоугольника
						 double maX,miN;
						 maX=miN==a[0][0];
						 Bitmap^ bmp=gcnew Bitmap(kx,ky);
						 for (int i=0;i<ky;i++)
							 for(int j=0;j<kx;j++){
								 if(a[i][j]>maX)maX=a[i][j];
								 if(a[i][j]<miN)miN=a[i][j];
							 }
							 for (int x=0;x<kx;x++)
							 {
								 for(int y=0;y<ky;y++){
									 int rgb=255-255*(a[x][y]/maX);
									 bmp->SetPixel(x,y,Color::FromArgb(rgb,rgb,rgb));
									 //Rectangle* rect=new Rectangle(x*sizeX,y*sizeY,sizeX,sizeY);
									 //Histogram->Series[0]->s(gcnew Pen(Color::FromArgb(rgb,rgb,rgb)),x*sizeX,y*sizeY,sizeX,sizeY);
									 g->FillRectangle(gcnew SolidBrush(Color::FromArgb(rgb,rgb,rgb)),x*sizeX,y*sizeY,sizeX,sizeY);
								 }
							 }
							 bmp->Save("im.bmp",Drawing::Imaging::ImageFormat::Bmp);
							 //Histogram->Images->Add();
							 for (int i=0;i<ky;i++)
							 {
								 delete a[i];
							 }
							 delete [] a;
							 break;
					 }
				 case 1:
					 {// сканирование сечения
						 Histogram->Series[0]->Points->Clear();
						 double begin=Convert::ToDouble(textBoxBegin->Text->Replace('.',','));
						 double end=Convert::ToDouble(textBoxEnd->Text->Replace('.',','));
						 n=Convert::ToInt32(numericUpDownIntervalsCount->Value);	

						 double ds=(end-begin)/n;

						 //double E0=sample->rays[0].points->begin()->energy;
						 double* I=new double[n];
						 int k=0;
						 int di=100/n;
						 progressBar1->Visible=true;
						 for(double x=begin;x<end;x+=ds,k++){
							 sample->traceRays(count,E0,Ecr,widthBundle,yBundle,x,det,1);
							 I[k]=(double)det->getCount()/count;
							 sample->clear();
							 progressBar1->Value=k*di;
							 //Histogram->Series[0]->Points->AddXY(x,det->getCount());
						 }
						 progressBar1->Value=100;
						 double maxY=I[0];
						 for (int i=0;i<n;i++)
						 {
							 double x=begin+i*ds;
							 Histogram->Series[0]->Points->AddXY(x,I[i]);
							 if(I[i]>maxY)maxY=I[i];
						 }
						 Histogram->ChartAreas[0]->AxisX->Minimum=begin;
						 Histogram->ChartAreas[0]->AxisX->Maximum=end;
						 Histogram->ChartAreas[0]->AxisY->Minimum=0;
						 Histogram->ChartAreas[0]->AxisY->Maximum=1.0;
						 progressBar1->Visible=false;
						 //Histogram->Refresh();
						 save(I,n);
						 delete I;
						 I=NULL;
						 break;	
					 }
				 case 2:// длины пробегов
					 {
						 double E0=50;
						 char str[6][3]={"Al","Cu","Ag","Au","Pb","W"};
						 double A[]={26.98,63.546,107.86,197,207.19,183.85};// молярная масса
						 double ro[]={2.7,8.92,10.5,19.3,11.3415,19.25};// плотность
						 int Z[]={13,29,47,79,82,74};
						 double r0=0.0276*A[0]*Math::Pow(E0,1.67)/(ro[0]*Math::Pow(Z[0],0.889));
						 Histogram->ChartAreas[0]->AxisX->Minimum=0;
						 Histogram->ChartAreas[0]->AxisX->Maximum=E0;
						 Histogram->ChartAreas[0]->AxisY->Minimum=0;
						 Histogram->ChartAreas[0]->AxisY->Maximum=r0;


						 for(int i=0;i<6;i++){
							 String^ st=gcnew String(str[i]);
							 //Series^s=gcnew Series(st);
							 Histogram->Series->Add(st);
							 Histogram->Series[i+2]->ChartType=DataVisualization::Charting::SeriesChartType::Spline;
							 for(double E=0;E<50.0;E+=1){
								 double R0=0.0276*A[i]*Math::Pow(E,1.67)/(ro[i]*Math::Pow(Z[i],0.889));
								 Histogram->Series[i+2]->Points->AddXY(E,R0);
							 }
						 }
						 break;
					 }
					 
				 case 3:{// 
					 ifstream in;
					 double** I;
					 double avg;
					 in.open("results2.txt",ios::in);
					 int n,m;
					 m=4;
					 in>>n;
					 string str;
					 double a;
					 int k=0;
					 I=new double*[m];
					 vector<string> vec;
					 for(int i=0;i<m;i++){
						 I[i]=new double[n];
						 for(int j=0;j<n;j++)
							 in>>I[i][j];
					 }
					 in.close();
					 //char str[6][3]={"Al","Cu","Ag","Au","Pb","W"};
					 char st[4][3]={"Si","Ag","Au","Fe"};
					 cli::array<String^>^ strs=gcnew cli::array<String^>(4);
					 Histogram->ChartAreas[0]->AxisX->Minimum=-0.0001;
					 Histogram->ChartAreas[0]->AxisX->Maximum=0.0007;
					 Histogram->ChartAreas[0]->AxisY->Minimum=0.0;
					 Histogram->ChartAreas[0]->AxisY->Maximum=1.0;
					 double dx=0.0002/n;
					 double x0=-0.0001;
					 Histogram->Series->Add("avg");
					 Histogram->Series["avg"]->ChartType=DataVisualization::Charting::SeriesChartType::Doughnut;
					 for(int i=0;i<m;i++){
						 strs[i]=gcnew String(st[i]);
						 Histogram->Series->Add(strs[i]);
						
						 //int ind=Histogram->Series->IndexOf(st);
						 Histogram->Series[strs[i]]->ChartType=DataVisualization::Charting::SeriesChartType::Line;
						 
						 if(i>0)Histogram->Series[strs[i]]->Points->AddXY(x0+(i*n-1)*dx,I[i-1][n-1]);
						 avg=0.0;
						 for(int j=0;j<n;j++)avg+=I[i][j];
						 avg/=n;
						 for(int j=0;j<n;j++){
							 Histogram->Series["avg"]->Points->AddXY(x0+(i*n+j)*dx,avg);
							 Histogram->Series[strs[i]]->Points->AddXY(x0+(i*n+j)*dx,I[i][j]);
						 }
						 
					 }
					 Histogram->Series[strs[0]]->Color=Color::Green;
					 Histogram->Series[strs[1]]->Color=Color::Red;
					 Histogram->Series[strs[2]]->Color=Color::Gold;
					 Histogram->Series[strs[3]]->Color=Color::Gray;
					 break;
						}
				 }
			 
}
//private: System::Void checkBoxUp_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
//			 Histogram->Series[0]->Enabled=checkBoxUp->Checked;
//			 Histogram->Refresh();
//		 }
//private: System::Void checkBoxDown_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
//			  Histogram->Series[1]->Enabled=checkBoxDown->Checked;
//			  Histogram->Refresh();
//		 }
private: System::Void продолжитьToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		 }
};
}
