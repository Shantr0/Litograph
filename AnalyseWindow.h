#pragma once
#include "SampleParameters.h"
#include <limits>
#include <cmath>

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
		double width,height;
		//void *analyseFunction;

	private: System::Windows::Forms::CheckBox^  checkBoxUp;
	private: System::Windows::Forms::CheckBox^  checkBoxDown;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownY;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  анализToolStripMenuItem;

	public:

		AnalyseWindow(SampleParameters* sample,double width,double height,int type)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			this->sample=sample;
			this->width=width;
			this->height=height;
			numericUpDownIntervalsCount->Maximum=LONG_MAX;
		}
	protected:
		double sqr(double x){
			return x*x;
		};
		void maxXY(double &maxX,double &minY,SampleParameters* sample){
			list<Node>::iterator point=sample->rays[0].points->begin();
			//list<double>::iterator itY=sample->rays[0].y->begin();
			maxX=point->x;
			minY=point->y;
			int n=sample->getRaysCount();
			for(int i=0;i<n;i++){
				point=sample->rays[i].points->begin();
				//itY=sample->rays[i].y->begin();
				for(;point!=sample->rays[i].points->end();point++){
					if (maxX<abs(point->x)) maxX=abs(point->x);
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
						//double r=sqrt(sqr(x1-x0)+sqr(y1-y0));// квадрат расстояния до следующей точки
						//dE*=r;// потеря энергии
						//eSum[m]+=dE;// добавляем поетрю энергии для точки ym
						//elossI+=dE;
						//double dE2=E-itp->energy;
						//E-=dE;
					} 
					else if(y1 <= Y[m])// следующий узел находится ниже
					{
						double k=(y1-y0)/(x1-x0);
						//double l=sqrt(sqr(y1-y0)+sqr(x1-x0));
						//double dE1=sample->energieLossUnit(E)*l;
						//elossI+=dE1;
						m++;
						double r,E0;
						//double dE2=0;
						//double s=0;
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
		void getNM(int& n,int& m,double X,double Y,double* x,double* y){// определяет индексы n m точки (X,Y) в интервалах x y  
			while(y[m]>Y)m++;   // 
			if(m>0 && y[m]!=Y)m--;
			while(x[n]>X)n++;
			if(n>0 && x[n]!=X)n--;
		}
		double** allocation(int intervCountX,int intervCountY,double x0,double width,double y0,double height){
			double* x=new double[intervCountX+1];
			double* y=new double[intervCountY+1];
			double dx=width/intervCountX;
			double dy=height/intervCountY;
			double** result=new double*[intervCountY];
			for(int i=0;i<intervCountY;i++){// инициализация нулями всех ячеек 
				result[i]=new double[intervCountX];
				y[i]=y0+i*dy;// и разбиение на у интервалы
			}
			y[intervCountY]=height;
			for(int i=0;i<intervCountY;i++)
				for(int j=0;j<intervCountY;j++) result[i][j]=0.0;
			int raysCount=sample->getRaysCount();
			for(int i=0;i<intervCountX+1;i++) x[i]=x0+i*dx; // разбиение на х интервалы
			for(int i=0;i<raysCount;i++){// проход по лучам
				list<Node>::iterator itp=sample->rays[i].points->begin();
				list<Node>::iterator prEnd=--sample->rays[i].points->end();
				double E=itp->energy;
				while (itp!=prEnd)// проход по узлам
				{
					double X0=itp->x;
					double Y0=itp->y;
					E=itp->energy;
					int m=0;
					int n=0;
					getNM(n,m,X0,Y0,x,y);
					//list<Node>::iterator itPrev=itp;
					itp++;
					double x1=itp->x;
					double y1=itp->y;
					double dE=sample->energieLossUnit(E);// энергия на единичный участок  до следующего узла
					if (y1 <= y[m] && y1 > y[m+1] && x1 >= x[n] && x1 < x[n+1])// следующий узел в этой же ячейке
					{
						double r=sqrt(sqr(x1-X0)+sqr(y1-Y0));// квадрат расстояния до следующей точки
						result[m][n]+=r*dE;
					} 
					else if(y1 > y[m] || y1 < y[m+1])// следующий узел находится ниже или выше 
					{
						double k=(y1-Y0)/(x1-X0);
						//if(y1 < y[m+1])m++;
						//else m--;
						double r,E0,fi;
						do{
							//y1=(itp->y<=y[m+1]) ? y[m+1] : y[m];
							fi=itp->angle+Math::PI;
							if(fi>=0 && fi<Math::PI) y1= y[m];
							else y1=y[m+1];
							x1=(y1-Y0)/k+X0;// новая координата на границе
							if(x1 >= x[n] && x1 <= x[n+1]){// в том же х интервале
								r=sqrt(sqr(x1-X0)+sqr(y1-Y0));//  расстояние до следующей точки
								result[m][n]+=r*dE;
								if(itp->y <= y[m+1])m++;
								else m--;
								Y0=y1;
								X0=x1;
							}else {// левее или правее
								x1= (x1<=x[n]) ? x[n] : x[n+1];
								y1=k*x1+y[m+1];
								r=sqrt(sqr(x1-X0)+sqr(y1-Y0));//  расстояние до следующей точки
								result[m][n]+=r*dE;
								X0=x1;
								Y0=y1;
								if(itp->x<=x[n])n--;
								else n++;
							}

						} while((itp->y < y[m+1] || itp->y > y[m]) && !(itp->x > x[n] && itp->x < x[n+1]) && m<intervCountY  && n<intervCountX);
						x1=itp->x;
						y1=itp->y;
						r=sqrt(sqr(x1-X0)+sqr(y1-Y0));// расстояние до следующей точки
						result[m][n]+=r*dE;
					}
					else{// на том же у уровне
						double k=(y1-Y0)/(x1-X0);
						//m++;
						double r,E0;
						do{
							x1=(itp->x<=x[n]) ? x[n] : x[n+1];
							y1=k*x1+y[m+1];
							r=sqrt(sqr(x1-X0)+sqr(y1-Y0));//  расстояние до следующей точки
							Y0=y1;
							X0=x1;
							if(x1<=x[n])n--;
							else n++;
						}while((itp->x <= x[n] || itp->x > x[n+1]) && n<intervCountX);
					}
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
private: System::Windows::Forms::NumericUpDown^  numericUpDownIntervalsCount;


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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::Title^  title2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->Histogram = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->numericUpDownIntervalsCount = (gcnew System::Windows::Forms::NumericUpDown());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->checkBoxUp = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxDown = (gcnew System::Windows::Forms::CheckBox());
			this->numericUpDownY = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->анализToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Histogram))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownIntervalsCount))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownY))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// Histogram
			// 
			this->Histogram->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			chartArea1->AxisX->LabelStyle->Format = L"E2";
			chartArea1->AxisX->LineColor = System::Drawing::Color::LightGray;
			chartArea1->AxisX->MajorGrid->LineColor = System::Drawing::Color::LightGray;
			chartArea1->AxisX->Minimum = 0;
			chartArea1->AxisY->MajorGrid->LineColor = System::Drawing::Color::LightGray;
			chartArea1->Name = L"ChartArea1";
			this->Histogram->ChartAreas->Add(chartArea1);
			legend1->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			legend1->Name = L"Legend1";
			this->Histogram->Legends->Add(legend1);
			this->Histogram->Location = System::Drawing::Point(12, 26);
			this->Histogram->Name = L"Histogram";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->Color = System::Drawing::Color::Black;
			series1->Enabled = false;
			series1->Legend = L"Legend1";
			series1->Name = L"Доза";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->Enabled = false;
			series2->Legend = L"Legend1";
			series2->Name = L"Промежуточная доза";
			this->Histogram->Series->Add(series1);
			this->Histogram->Series->Add(series2);
			this->Histogram->Size = System::Drawing::Size(605, 283);
			this->Histogram->TabIndex = 0;
			this->Histogram->Text = L"chart1";
			title1->Alignment = System::Drawing::ContentAlignment::TopLeft;
			title1->Name = L"Title1";
			title1->Text = L"E, кэВ";
			title2->Alignment = System::Drawing::ContentAlignment::TopCenter;
			title2->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			title2->Name = L"Title2";
			title2->Text = L"y, см";
			this->Histogram->Titles->Add(title1);
			this->Histogram->Titles->Add(title2);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(635, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(123, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"число интервалов по X";
			// 
			// numericUpDownIntervalsCount
			// 
			this->numericUpDownIntervalsCount->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->numericUpDownIntervalsCount->Location = System::Drawing::Point(638, 55);
			this->numericUpDownIntervalsCount->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDownIntervalsCount->Name = L"numericUpDownIntervalsCount";
			this->numericUpDownIntervalsCount->Size = System::Drawing::Size(120, 20);
			this->numericUpDownIntervalsCount->TabIndex = 2;
			this->numericUpDownIntervalsCount->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(650, 285);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(108, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"расчет";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &AnalyseWindow::button1_Click);
			// 
			// checkBoxUp
			// 
			this->checkBoxUp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->checkBoxUp->AutoSize = true;
			this->checkBoxUp->Checked = true;
			this->checkBoxUp->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxUp->Location = System::Drawing::Point(712, 176);
			this->checkBoxUp->Name = L"checkBoxUp";
			this->checkBoxUp->Size = System::Drawing::Size(46, 17);
			this->checkBoxUp->TabIndex = 4;
			this->checkBoxUp->Text = L"по х";
			this->checkBoxUp->UseVisualStyleBackColor = true;
			this->checkBoxUp->CheckedChanged += gcnew System::EventHandler(this, &AnalyseWindow::checkBoxUp_CheckedChanged);
			// 
			// checkBoxDown
			// 
			this->checkBoxDown->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->checkBoxDown->AutoSize = true;
			this->checkBoxDown->Checked = true;
			this->checkBoxDown->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxDown->Location = System::Drawing::Point(712, 199);
			this->checkBoxDown->Name = L"checkBoxDown";
			this->checkBoxDown->Size = System::Drawing::Size(46, 17);
			this->checkBoxDown->TabIndex = 5;
			this->checkBoxDown->Text = L"по y";
			this->checkBoxDown->UseVisualStyleBackColor = true;
			this->checkBoxDown->CheckedChanged += gcnew System::EventHandler(this, &AnalyseWindow::checkBoxDown_CheckedChanged);
			// 
			// numericUpDownY
			// 
			this->numericUpDownY->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->numericUpDownY->Location = System::Drawing::Point(638, 127);
			this->numericUpDownY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDownY->Name = L"numericUpDownY";
			this->numericUpDownY->Size = System::Drawing::Size(120, 20);
			this->numericUpDownY->TabIndex = 7;
			this->numericUpDownY->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(635, 98);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(92, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"число точек по Y";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->анализToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(770, 24);
			this->menuStrip1->TabIndex = 8;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// анализToolStripMenuItem
			// 
			this->анализToolStripMenuItem->Name = L"анализToolStripMenuItem";
			this->анализToolStripMenuItem->Size = System::Drawing::Size(59, 20);
			this->анализToolStripMenuItem->Text = L"Анализ";
			// 
			// AnalyseWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(770, 320);
			this->Controls->Add(this->numericUpDownY);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->checkBoxDown);
			this->Controls->Add(this->checkBoxUp);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->numericUpDownIntervalsCount);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Histogram);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"AnalyseWindow";
			this->Text = L"AnalyseWindow";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->Histogram))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownIntervalsCount))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownY))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void f(int a) { }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 //void (*pf)(int) = AnalyseWindow::&f;
				 Histogram->Series[0]->Points->Clear();
				 Histogram->Series[1]->Points->Clear();
				 int n=sample->getRaysCount();
				 int kx=(int)numericUpDownIntervalsCount->Value;
				 int ky=(int)numericUpDownY->Value;
				 double* energy;
				 //energy=new double*[2];
				 
				 //double E=0;
				 int* intervalsX,*intervalsY,*specter;
				 //intervals=allocationParticle(n,kx,specter);
				 list<Node>::iterator begin=sample->rays[0].points->begin();
				 list<Node>::iterator end=sample->rays[0].points->end();
				 end--;
				 double x0,y0;
				 maxXY(x0,y0,sample);
				 double** a=allocation(kx,ky,-x0,width,sample->rays[0].points->begin()->y,y0);
				 //double dE= begin->energy - end->energy;
				 //allocationParticleByY(n,ky,specter,energy);
				 //distributeRaysCount(kx,ky,intervalsX,intervalsY);
				 //allocationElectronsCount(ky,specter);
				 //
				 int type=0;
				 switch(type){
				 case DOSE_DISTRIBUTION:
					 //void (*analyseFunction)(int,int,int*,double*)= & allocationParticleByY;
					 break;
				 }

				 //int i=0;
				 double* es=new double[ky];
				 double* Y=new double[ky];
				 //for(int i=0;i<ky;i++)Y[i]=i*dy;
				 ////double y;
				 //for(int i=0;i<ky;i++){
					// //y=Y[i];
					// if(specter[i]==0){
					//	 ky--;
					//	 break;
					// };
					// es[i]=energy[i]/specter[i];
					// Histogram->Series[0]->Points->AddXY(-Y[i],es[i]);
					// 
				 //}
				 //double s=0.0;
				 //Histogram->Series[1]->Points->AddXY(-Y[ky-1],0);
				 //for (int i=ky-1;i>0;i--)
				 //{	 
					// s+=-(es[i-1]+es[i])/2*dy;
					// Histogram->Series[1]->Points->AddXY(-Y[i-1],s);
					// //y-=dy;
					// //i--;
					//	 //Histogram->Series[1]->Points->AddXY(0,0);
		
				 //}
				 char str[4][3]={"Al","Cu","Ag","Au"};
				 //char name1="Al";
				 double A[]={26.98,63.546,107.86,197};
				 double ro[]={2.7,8.92,10.5,19.3};
				 int Z[]={13,29,47,79};
				 for(int i=0;i<4;i++){
					 String^ st=gcnew String(str[i]);
					 Series^s=gcnew Series(st);
					 Histogram->Series->Add(s);
					 Histogram->Series[i+2]->ChartType=DataVisualization::Charting::SeriesChartType::Spline;
					 for(double E=1;E<30.0;E+=1){
						 double R0=0.0276*A[i]*Math::Pow(E,1.67)/(ro[i]*Math::Pow(Z[i],0.889));
						 Histogram->Series[i+2]->Points->AddXY(E,R0);
					 }
				 }
				 delete Y;
				 delete es;
				 delete specter;
				 /* for(double E=E0;i<ky;E-=dE){
				 Histogram->Series[0]->Points->AddXY(E/E0,specter[i]);
				 i++;
				 }*/
				 //delete specter;
				 //label1->Text=Convert::ToString(E-dE);
			 }
private: System::Void checkBoxUp_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 Histogram->Series[0]->Enabled=checkBoxUp->Checked;
			 Histogram->Refresh();
		 }
private: System::Void checkBoxDown_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			  Histogram->Series[1]->Enabled=checkBoxDown->Checked;
			  Histogram->Refresh();
		 }
};
}
