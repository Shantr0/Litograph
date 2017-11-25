#pragma once
//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h> 
#include <ctime>
#include "DetectorWindow.h"
#include "SampleParameters.h"
#include "Detector.h"
#include "cutGraphic.h"


namespace Litography {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for Scan3DWindow
	/// </summary>
	public ref class Scan3DWindow : public System::Windows::Forms::Form
	{
	public:
		SampleParameters* sample;
		Detector* detectors;
		int intervCountX,interCountZ,detectorsCount;
		double thickness;
		double yBeam,widthBeam;
		double*** I;
		Bitmap^ topog;
		Bitmap^ comp;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::Label^  labelSec;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownRaysCount;

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	public: 
	private: System::Windows::Forms::Button^  button2;
			 
			 
		//Bitmap^ toImage(double **I,int n,int m,int N,int M){
		//	Bitmap^ bmp=gcnew Bitmap(M,N);
		//	double maxI,minI;
		//	int k1=N/n;
		//	int k2=M/m;
		//	int a=min(k1,k2);
		//	maxmin(I,n,m,maxI,minI);
		//	double k=255/(maxI-minI);
		//	for (int l=0;l<a;l++)
		//	{
		//		for(int i=0;i<n;i++)
		//			for(int j=0;j<m;j++){
		//				int color=k*(I[i][j]-minI);
		//				bmp->SetPixel(j,i,Color::FromArgb(color,color,color));
		//			}
		//	}
		//		return bmp;
		//}
		/*	Bitmap^ scaleIM(Bitmap^ im,int n,int m,int N,int M){
		Bitmap^ bmp=gcnew Bitmap(N,M);
		int k1=N/n;
		int k2=M/m;
		for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
		bmp->SetPixel(i*k1,j*k2,)im->GetPixel(i,j);	
		return bmp;
		}*/

	public: 
	private: System::Windows::Forms::TextBox^  textBoxBegin;
	private: System::Windows::Forms::TextBox^  textBoxEnd;

	private: System::Windows::Forms::Label^  labelWaveLength;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  textBoxCriticalEnergy;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::TextBox^  textBoxInitialEnergy;
	private: System::Windows::Forms::Button^  buttonContinue;
	private: System::Windows::Forms::RadioButton^  radioButtonTopograph;
	private: System::Windows::Forms::RadioButton^  radioButtonCompos;
	private: System::Windows::Forms::TextBox^  textBoxZ;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button3;




	private: System::Windows::Forms::ProgressBar^  progressBar1;
	public:	Scan3DWindow(SampleParameters* sample,Detector* det,int count,double yBeam,double widthBeam)
		{
			InitializeComponent();
			this->sample=sample;
			//detector=new Detector();
			//*detector=*det;
			detectors=det;
			detectorsCount=count;
			intervCountX=10;
			thickness=0.001;
			//this->xBeam=xBeam;
			this->yBeam=yBeam;
			this->widthBeam=widthBeam;
			topog=nullptr;
			comp=nullptr;
			//initialize();
		}
			void maxmin(double** arr,int n,int m,double &max,double &min){
				max=min=arr[0][0];
				for(int i=0;i<n;i++){
					for(int j=0;j<m;j++){
						if (max<arr[i][j]) max=arr[i][j];
						if (min>arr[i][j]) 
							min=arr[i][j];
					}
				}
			}
			Bitmap^ toImage(double **I,int n,int m){
				Bitmap^ bmp=gcnew Bitmap(m,n);
				double maxI,minI;	
				maxmin(I,n,m,maxI,minI);
				double k=255/(maxI-minI);
				for(int i=0;i<n;i++)
					for(int j=0;j<m;j++){
						int color=k*(I[i][j]-minI);
						bmp->SetPixel(j,i,Color::FromArgb(color,color,color));
					}
					return bmp;
			}
	protected:
		bool isInf(double val){
			double zero=0.0;
			double inf=1/zero;
			return abs(val)==inf;
		}
		void addTraectory(Node* node,double teta,double ds){// новая траеткория электрона
			//p=&points->back();// последняя точка
			double alpha=node->angle;//angle->back();// поворот СК
			double xn=sin(teta)*ds;// координаты
			double yn=-cos(teta)*ds;// в новой системе
			double xi,yi;
			xi=xn*cos(alpha)-yn*sin(alpha)+node->x;
			yi=xn*sin(alpha)+yn*cos(alpha)+node->y;
			alpha+=teta;
			if(!node) node=new Node(xi,yi,alpha);
			else{
				node->x=xi;
				node->y=yi;
				node->angle=alpha;
			}
			//points->insert(points->end(),*node);
		}
		void calculateTraectory(Node* node,double E0,double Ecr,Relief2D* relief,Detector* dets,int n){
			double E=E0;
			double y0=node->y;// точка вылета эл. из пушки
			Node* nod=new Node();
			addTraectory(nod,0,y0-relief->getY(node->x));// пролет в вакууме до образца
			node->energy=E0;
			//firstPath(rays,E);// пробег под нулевым углом
			while (E>Ecr)// расчет траектории
			{
				double a=3.4e-3*pow(sample->getZNumber(),0.67)/E;
				double fi=Ray::generateAngle(a);// угол отклонения
				double s=sample->runDistance(fi,E,a);//  пробег
				addTraectory(nod,fi,s);// добавление траектории 
				double dE=abs(sample->energieLoss(E,s));// потеря энергии
				E-=dE;// потеря энергии
				//list<Node>::iterator p=--rays[0].points->end();
				nod->energy=E;
				//bool isInDet=false;
				double maxYdet=Detector::maxY(dets,n);
				if (!relief->isInMaterial(nod->x,nod->y)) {// вылет из образца
					//list<Node>::iterator prev=std::prev(p);
					double k=(nod->y-node->y)/(nod->x-node->x);
					double px=nod->x;
					if(nod->x>node->x)nod->x=relief->xIntersect(k,nod->x,nod->y,1);// проверка на повторное 
					else nod->x=relief->xIntersect(k,nod->x,nod->y,-1);// попадание в образец
					if(isInf(nod->x)){// луч не идет в образец
						for(int i=0;i<n;i++){// проверка попадания в детектор
							double *point=dets[i].sec(px,nod->y,nod->angle);// точка пересечения с линией детектора
							if(dets[i].isActive() && dets[i].isIn(point[0],point[1])){// в случае попадания в детектор
								dets[i].incCount();
								nod->x=point[0];
								nod->y=point[1];
								nod->energy=node->energy;
								nod->angle=node->angle;
								//break;
								return;
							}	
						}
						// если не попадает ни в 1 детектор
						if(k>0 && node->x<px || k<0 && node->x>px)nod->y=maxYdet;// ???
						else nod->y=0;//-rays[0].points->begin()->y;
						nod->x=node->x+(nod->y-node->y)/k;
						nod->energy=node->energy;
						nod->angle=node->angle;
						break;
					}else{// есть попадание в образец
						nod->y=relief->getY(nod->x);
						nod->energy=node->energy;
						nod->angle=node->angle;
						if(relief->getX(0)> nod->x || nod->x>relief->getX(relief->getSize()-1))
							break;
						//firstPath(rays,E);
					}
				}
				node->x=nod->x;
				node->y=nod->y;
				node->energy=nod->energy;
				node->angle=nod->angle;
				if(dE<=1e-16)break;
			}
			delete nod;
		}
		void traceRays(int raysCount,double E0,double Ecr,double widthBundle,double distance,double displace,Detector* dets,int n){
			Node *node=new Node();
			srand(time(0));
			double dx=widthBundle/raysCount;
			for(int i=0;i<n;i++) dets[i].resetCount();
			for(int i=0;i<raysCount;i++){	// для всех лучей
				node->energy=E0;// энергия на старте
				node->x=i*dx+displace;// координата х с учетом смещения
				node->y=distance;// начальное положение ЭП
				calculateTraectory(node,E0,Ecr,sample->relief,dets,n);// расчет траектории
			}
		}
		/*void initialize(){
		textBoxX->Text=Convert::ToString(detector->x);
		textBoxY->Text=Convert::ToString(detector->y);
		textBoxAngle1->Text=Convert::ToString(detector->angle);
		textBoxLength->Text=Convert::ToString(detector->getSize());
		}*/
		void writeData(ofstream& of,double begin,double end,int j,int k,double z,int i,int n,double thickness,int rayscount,double ***arr,String^ name){
			//int m=sample->getRaysCount();
			sample->clear();
			char* fname=(char*)(void*)Marshal::StringToHGlobalAnsi(name);
			of.open(fname,ios::out);
			of<<begin<<" ";
			of<<j<<" ";// текущий индекс из
			of<<k<<" ";// n
			of<<end<<"\n";
			of<<z<<" ";// z координата
			of<<++i<<" ";
			of<<n<<" ";
			of<<z+thickness<<"\n";
			//запись сигналов
			of<<detectorsCount;
			for(int s=0;s<detectorsCount;s++){
				for (int l=0;l<i;l++){
					for(int m=0;m<j;m++)
						of<<arr[s][l][m]<<" ";
					of<<"\n";
				}
			}
			// вещество
			of<<sample->getZNumber()<<" ";
			of<<sample->getMass()<<" ";
			of<<sample->getDensity()<<"\n";
			of<<rayscount<<"\n";	 
			if(sample->relief) sample->relief->write(of);
			for(int i=0;i<detectorsCount;i++)detectors[i].output(of);
			of.close();
		}
		double random(double min,double max){
			double rnd=rand()/((double) RAND_MAX);
			double k=max-min;
			rnd=rnd*k+min;
			return rnd;
		}
		void indexInit(int& i1,int& i2){
			i1=i2=-1;
			for(int i=0;i<detectorsCount;i++){
				if(detectors[i].isActive())
					if(i1==-1)i1=i;
					else if(i2==-1)i2=i;
					else break;
			}
		}
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Scan3DWindow()
		{
			if (components)
			{
				delete components;
			}
		}
		private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownIntervalsCount;
	protected: 

	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBoxThickness;

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
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->numericUpDownIntervalsCount = (gcnew System::Windows::Forms::NumericUpDown());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxThickness = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->textBoxBegin = (gcnew System::Windows::Forms::TextBox());
			this->textBoxEnd = (gcnew System::Windows::Forms::TextBox());
			this->labelWaveLength = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBoxCriticalEnergy = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->textBoxInitialEnergy = (gcnew System::Windows::Forms::TextBox());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->labelSec = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->numericUpDownRaysCount = (gcnew System::Windows::Forms::NumericUpDown());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->buttonContinue = (gcnew System::Windows::Forms::Button());
			this->radioButtonTopograph = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonCompos = (gcnew System::Windows::Forms::RadioButton());
			this->textBoxZ = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownIntervalsCount))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownRaysCount))->BeginInit();
			this->SuspendLayout();
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(706, 55);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(98, 13);
			this->label3->TabIndex = 15;
			this->label3->Text = L"число интервалов";
			// 
			// numericUpDownIntervalsCount
			// 
			this->numericUpDownIntervalsCount->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->numericUpDownIntervalsCount->Location = System::Drawing::Point(709, 71);
			this->numericUpDownIntervalsCount->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100000, 0, 0, 0});
			this->numericUpDownIntervalsCount->Name = L"numericUpDownIntervalsCount";
			this->numericUpDownIntervalsCount->Size = System::Drawing::Size(108, 20);
			this->numericUpDownIntervalsCount->TabIndex = 14;
			this->numericUpDownIntervalsCount->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Location = System::Drawing::Point(709, 303);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(108, 23);
			this->button1->TabIndex = 13;
			this->button1->Text = L"расчет";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Scan3DWindow::button1_Click);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(706, 6);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(71, 13);
			this->label1->TabIndex = 16;
			this->label1->Text = L"толщина(см)";
			// 
			// textBoxThickness
			// 
			this->textBoxThickness->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBoxThickness->Location = System::Drawing::Point(709, 22);
			this->textBoxThickness->Name = L"textBoxThickness";
			this->textBoxThickness->Size = System::Drawing::Size(108, 20);
			this->textBoxThickness->TabIndex = 17;
			this->textBoxThickness->Text = L"0.1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox1->Location = System::Drawing::Point(129, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(513, 272);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 30;
			this->pictureBox1->TabStop = false;
			// 
			// progressBar1
			// 
			this->progressBar1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->progressBar1->Location = System::Drawing::Point(127, 290);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(515, 10);
			this->progressBar1->TabIndex = 31;
			this->progressBar1->Visible = false;
			// 
			// textBoxBegin
			// 
			this->textBoxBegin->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->textBoxBegin->Location = System::Drawing::Point(251, 305);
			this->textBoxBegin->Name = L"textBoxBegin";
			this->textBoxBegin->Size = System::Drawing::Size(48, 20);
			this->textBoxBegin->TabIndex = 33;
			this->textBoxBegin->Text = L"-0.00015";
			// 
			// textBoxEnd
			// 
			this->textBoxEnd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->textBoxEnd->Location = System::Drawing::Point(477, 305);
			this->textBoxEnd->Name = L"textBoxEnd";
			this->textBoxEnd->Size = System::Drawing::Size(44, 20);
			this->textBoxEnd->TabIndex = 35;
			this->textBoxEnd->Text = L"0.0003";
			// 
			// labelWaveLength
			// 
			this->labelWaveLength->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->labelWaveLength->AutoSize = true;
			this->labelWaveLength->Location = System::Drawing::Point(803, 138);
			this->labelWaveLength->Name = L"labelWaveLength";
			this->labelWaveLength->Size = System::Drawing::Size(0, 13);
			this->labelWaveLength->TabIndex = 40;
			// 
			// label11
			// 
			this->label11->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(706, 150);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(130, 13);
			this->label11->TabIndex = 39;
			this->label11->Text = L"энергия ионизации(кэВ)";
			// 
			// textBoxCriticalEnergy
			// 
			this->textBoxCriticalEnergy->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBoxCriticalEnergy->Location = System::Drawing::Point(709, 172);
			this->textBoxCriticalEnergy->Name = L"textBoxCriticalEnergy";
			this->textBoxCriticalEnergy->Size = System::Drawing::Size(108, 20);
			this->textBoxCriticalEnergy->TabIndex = 38;
			this->textBoxCriticalEnergy->Text = L"0,2";
			// 
			// label12
			// 
			this->label12->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(706, 102);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(131, 13);
			this->label12->TabIndex = 37;
			this->label12->Text = L"Начальная энергия, кэВ";
			// 
			// textBoxInitialEnergy
			// 
			this->textBoxInitialEnergy->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBoxInitialEnergy->Location = System::Drawing::Point(709, 120);
			this->textBoxInitialEnergy->Name = L"textBoxInitialEnergy";
			this->textBoxInitialEnergy->Size = System::Drawing::Size(108, 20);
			this->textBoxInitialEnergy->TabIndex = 36;
			this->textBoxInitialEnergy->Text = L"10";
			// 
			// trackBar1
			// 
			this->trackBar1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->trackBar1->Location = System::Drawing::Point(648, 12);
			this->trackBar1->Minimum = 1;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->trackBar1->Size = System::Drawing::Size(45, 272);
			this->trackBar1->TabIndex = 41;
			this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->trackBar1->Value = 1;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &Scan3DWindow::trackBar1_Scroll);
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button2->Location = System::Drawing::Point(709, 261);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(108, 23);
			this->button2->TabIndex = 42;
			this->button2->Text = L"сечение";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Scan3DWindow::button2_Click);
			// 
			// labelSec
			// 
			this->labelSec->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->labelSec->AutoSize = true;
			this->labelSec->Location = System::Drawing::Point(661, 287);
			this->labelSec->Name = L"labelSec";
			this->labelSec->Size = System::Drawing::Size(13, 13);
			this->labelSec->TabIndex = 43;
			this->labelSec->Text = L"0";
			// 
			// label13
			// 
			this->label13->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(710, 201);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(67, 13);
			this->label13->TabIndex = 44;
			this->label13->Text = L"число лучей";
			// 
			// numericUpDownRaysCount
			// 
			this->numericUpDownRaysCount->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->numericUpDownRaysCount->Location = System::Drawing::Point(713, 226);
			this->numericUpDownRaysCount->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000000, 0, 0, 0});
			this->numericUpDownRaysCount->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDownRaysCount->Name = L"numericUpDownRaysCount";
			this->numericUpDownRaysCount->Size = System::Drawing::Size(120, 20);
			this->numericUpDownRaysCount->TabIndex = 45;
			this->numericUpDownRaysCount->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// buttonContinue
			// 
			this->buttonContinue->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->buttonContinue->Location = System::Drawing::Point(337, 306);
			this->buttonContinue->Name = L"buttonContinue";
			this->buttonContinue->Size = System::Drawing::Size(75, 23);
			this->buttonContinue->TabIndex = 46;
			this->buttonContinue->Text = L"continue";
			this->buttonContinue->UseVisualStyleBackColor = true;
			this->buttonContinue->Visible = false;
			this->buttonContinue->Click += gcnew System::EventHandler(this, &Scan3DWindow::buttonContinue_Click);
			// 
			// radioButtonTopograph
			// 
			this->radioButtonTopograph->AutoSize = true;
			this->radioButtonTopograph->Checked = true;
			this->radioButtonTopograph->Location = System::Drawing::Point(9, 53);
			this->radioButtonTopograph->Name = L"radioButtonTopograph";
			this->radioButtonTopograph->Size = System::Drawing::Size(114, 17);
			this->radioButtonTopograph->TabIndex = 49;
			this->radioButtonTopograph->TabStop = true;
			this->radioButtonTopograph->Text = L"топографический";
			this->radioButtonTopograph->UseVisualStyleBackColor = true;
			this->radioButtonTopograph->CheckedChanged += gcnew System::EventHandler(this, &Scan3DWindow::radioButtonTopograph_CheckedChanged);
			// 
			// radioButtonCompos
			// 
			this->radioButtonCompos->AutoSize = true;
			this->radioButtonCompos->Location = System::Drawing::Point(9, 76);
			this->radioButtonCompos->Name = L"radioButtonCompos";
			this->radioButtonCompos->Size = System::Drawing::Size(113, 17);
			this->radioButtonCompos->TabIndex = 50;
			this->radioButtonCompos->Text = L"композиционный";
			this->radioButtonCompos->UseVisualStyleBackColor = true;
			this->radioButtonCompos->CheckedChanged += gcnew System::EventHandler(this, &Scan3DWindow::radioButtonCompos_CheckedChanged);
			// 
			// textBoxZ
			// 
			this->textBoxZ->Location = System::Drawing::Point(9, 261);
			this->textBoxZ->Name = L"textBoxZ";
			this->textBoxZ->Size = System::Drawing::Size(100, 20);
			this->textBoxZ->TabIndex = 51;
			this->textBoxZ->Text = L"0.0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 233);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(65, 13);
			this->label2->TabIndex = 52;
			this->label2->Text = L"начало по z";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(12, 306);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 53;
			this->button3->Text = L"детекторы";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Scan3DWindow::button3_Click);
			// 
			// Scan3DWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(845, 352);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBoxZ);
			this->Controls->Add(this->radioButtonCompos);
			this->Controls->Add(this->radioButtonTopograph);
			this->Controls->Add(this->buttonContinue);
			this->Controls->Add(this->numericUpDownRaysCount);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->labelSec);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->labelWaveLength);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->textBoxCriticalEnergy);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->textBoxInitialEnergy);
			this->Controls->Add(this->textBoxEnd);
			this->Controls->Add(this->textBoxBegin);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->textBoxThickness);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->numericUpDownIntervalsCount);
			this->Controls->Add(this->button1);
			this->Name = L"Scan3DWindow";
			this->Text = L"Сканирование";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Scan3DWindow::Scan3DWindow_FormClosing);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownIntervalsCount))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownRaysCount))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 int n=(int)numericUpDownIntervalsCount->Value;
				 trackBar1->Maximum=n;
				 //int ind=n-trackBar1->Value;
				 thickness=Convert::ToDouble(textBoxThickness->Text->Replace('.',','));
				 //detector[0].x=Convert::ToDouble(textBoxX->Text->Replace('.',','));
				 /* detector[0].y=Convert::ToDouble(textBoxY->Text->Replace('.',','));
				 detector[0].angle=Convert::ToDouble(textBoxAngle1->Text->Replace('.',','));
				 detector[0].setSize(Convert::ToDouble(textBoxLength->Text->Replace('.',',')));*/
				 double z=Convert::ToDouble(textBoxZ->Text->Replace('.',','));
				 double begin=Convert::ToDouble(textBoxBegin->Text->Replace('.',','));
				 double end=Convert::ToDouble(textBoxEnd->Text->Replace('.',','));
				 int count=(int)numericUpDownRaysCount->Value;
				 double ds=thickness/n;// шаг по толщине
				 double di=100/n;
				 int k=10;
				 double E0=Convert::ToDouble(textBoxInitialEnergy->Text->Replace('.',','));
				 double Ecr=Convert::ToDouble(textBoxCriticalEnergy->Text->Replace('.',','));
				 double dx=(end-begin)/k;// шаг сканирования
				 for(int d=0;d<detectorsCount;d++)I[d]=new double*[n];
				 progressBar1->Visible=true;
				 //labelSec->Text=Convert::ToString(ind);
				 int j;
				 int i=0;
				 ofstream of;
				 progressBar1->Value=0;
				 for (;i<n;i++)
				 {
					 j=0;
					 for(int d=0;d<detectorsCount;d++)I[d][i]=new double[k];
					 //double s=ds*i;

					 for(double x=begin;x<=end;x+=dx,j++){
						 //I[i][j]=0.0;
						 traceRays(count,E0,Ecr,widthBeam,yBeam,x,detectors,detectorsCount);
						 for(int d=0;d<detectorsCount;d++)
							 I[d][i][j]=(double)detectors[d].getCount()/count;
						 sample->clear();
					 }
					 progressBar1->Value=(i+1)*di;
					 writeData(of,begin,end,j,k,z,i,n,thickness,count,I,"scan.txt");// "scan "+i+".txt"
				 }
				 int i1,i2;
				 indexInit(i1,i2);
				 if(i2!=-1){			 
					 double** topograph=new double*[n];
					 double** compos=new double*[n];
					 for(int i=0;i<n;i++){
						 topograph[i]=new double[k];
						 compos[i]=new double[k];
						 for (int j=0;j<k;j++){
							 topograph[i][j]=0;
							 compos[i][j]=0;
							 if(detectorsCount>1){
								 topograph[i][j]=I[i1][i][j]-I[i2][i][j];
								 compos[i][j]=I[i1][i][j]+I[i2][i][j];
							 }else{
								 topograph[i][j]=I[i1][i][j];
								 compos[i][j]=I[i1][i][j]+I[1][i][j];
							 }
						 }
					 }
					 topog=toImage(topograph,n,k);
					 comp=toImage(compos,n,k);
				 }else if(i1!=-1){
					 double** topograph=new double*[n];
					 for(int i=0;i<n;i++){
						 topograph[i]=new double[k];
						 for (int j=0;j<k;j++){
							 //topograph[i][j]=0;
							 topograph[i][j]=I[0][i][j];
						 }
					 }
					 topog=toImage(topograph,n,k);
				 }
				 of.close();
				 if(radioButtonTopograph->Checked)pictureBox1->Image=topog;
				 else pictureBox1->Image=comp;

			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 int ind=trackBar1->Maximum-trackBar1->Value-1;
			 int k=intervCountX;
			 double* x=new double[k];
			 double begin=Convert::ToDouble(textBoxBegin->Text->Replace('.',','));
			 double end=Convert::ToDouble(textBoxEnd->Text->Replace('.',','));
			 double dx=(end-begin)/k;
			 for(int i=0;i<k;i++){
				 x[i]=begin+i*dx;
			 }
			 
			 CutGraphic^ win=gcnew CutGraphic(x,I[0][ind],k);
			 win->Show();
		 }
private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 int ind=trackBar1->Maximum-trackBar1->Value;
			 labelSec->Text=Convert::ToString(ind);
		 }
private: System::Void Scan3DWindow_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 //delete sample;
			 //delete detectors;
			 if(I)
				 for (int i=0;i<3;i++)
				 {
					 for(int j=0;j<intervCountX;j++) delete [] I[i][j];
					 delete [] I[i];
				 }
				 delete I;
		 }
private: System::Void buttonContinue_Click(System::Object^  sender, System::EventArgs^  e) {
			 ifstream in;
			 double Im[4][20][50];
			 double** image;
			 in.open("results2.txt",ios::in);
			 int n,m;
			 m=4;
			 in>>n;
			 string str;
			 double a;
			 int k=20;
			 
			 //for(int i=0;i<m;i++){
				// Im[i]=new double*[k];
				// for(int j=0;j<k;j++){
				//	 Im[i][j]=new double[n];
				// }
			 //}
			 for(int i=0;i<m;i++)
				 for(int j=0;j<n;j++)
					 in>>Im[i][0][j];

			 in.close();
			 //char str[6][3]={"Al","Cu","Ag","Au","Pb","W"};
			 char st[4][3]={"Si","Ag","Au","Fe"};
			 cli::array<String^>^ strs=gcnew cli::array<String^>(4);
			 double max,min;
			 double dx=0.0002/n;
			 double x0=-0.0001;
			 double z=0,dz=0.0001;
			 image=new double*[k];
			 for(int j=0;j<k;j++)
				 image[j]=new double[m*n];
			 for(int i=0;i<m;i++){
				 max=min=Im[i][0][0];

				 for(int j=0;j<n;j++){// поиск минмакс
					 if(Im[i][0][j]>max)max=Im[i][0][j];
					 else if(Im[i][0][j]<min) min=Im[i][0][j];
				 } 
				 for(int l=0;l<n;l++)	 
						 image[0][i*n+l]=Im[i][0][l];  
				 for(int j=1;j<k;j++)
						 for(int l=0;l<n;l++){
							 //Im[i][j][l]=;
							 image[j][i*n+l]=random(min,max);
						 }

						 //Histogram->Series[strs[i]]->Points->AddXY(x0+(i*n+j)*dx,I[i][j]);
			 }
			 Bitmap^ bmp=toImage(image,k,m*n);
			 pictureBox1->Image=bmp;
			 //double** I;
			 //double begin,end,z,thickness,zEnd;
			 //int i,j,k,n,detsCount;
			 //ifstream in;
			 //char* name;
			 //if(openFileDialog1->ShowDialog()== Windows::Forms::DialogResult::OK)
				// name=(char*)(void*)Marshal::StringToHGlobalAnsi(openFileDialog1->FileName);
			 //else return;
			 //
			 //in.open(name,ios::in);
			 //in>>begin;// начало
			 //in>>j;// текущий индекс из
			 //in>>k;// n
			 //in>>end;// конец
			 //in>>z;// z координата
			 //in>>i;
			 //in>>n;
			 //in>>zEnd;
			 //thickness=zEnd-z;
			 //in>>detsCount;
			 //detectorsCount=detsCount;
			 //I=new double**[detsCount];
			 //for(int s=0;s<detsCount;s++){
				// for (int l=0;l<i;l++){
				//	 I[s][l]=new double[k];
				//	 for(int m=0;m<j;m++)
				//		 in>>I[s][l][m];
				// }
			 //}
			 //int Z,m;
			 //double aMass,density;
			 //in>>Z;
			 //in>>aMass;
			 //in>>density;
			 //sample=new SampleParameters(Z,aMass,density);
			 //detector=new Detector[detectorsCount];
			 //sample->relief=new Relief2D();
			 //in>>m;	 
			 //sample->relief->read(in);
			 //for(int d=0;d<detectorsCount;d++)
				// detector[d].read(in);
			 //in.close();
			 //sample->setRaysCount(0);
			 //numericUpDownIntervalsCount->Value=n;
			 //trackBar1->Maximum=n;
			 ////int ind=n-trackBar1->Value;
			 //textBoxThickness->Text=Convert::ToString(thickness);
			 //textBoxX->Text=Convert::ToString(detector[0].x);
			 ////detector[0].x=Convert::ToDouble(textBoxX->Text->Replace('.',','));
			 //textBoxY->Text=Convert::ToString(detector[0].y);
			 //textBoxAngle1->Text=Convert::ToString(detector[0].angle);
			 //textBoxLength->Text=Convert::ToString(detector[0].getSize());
			 //textBoxZ->Text=Convert::ToString(z);
			 //textBoxBegin->Text=Convert::ToString(begin);
			 //textBoxEnd->Text=Convert::ToString(end);
			 //numericUpDownRaysCount->Value=m;
			 //double ds=thickness/n;// шаг по толщине
			 //double di=100/n;
			 //double E0,Ecr;
			 //E0=Convert::ToDouble(textBoxInitialEnergy->Text);//sample->rays[0].points->begin()->energy;
			 //textBoxInitialEnergy->Text=Convert::ToString(E0);
			 //Ecr=0.2;
			 //textBoxCriticalEnergy->Text=Convert::ToString(Ecr);
			 //double dx=(end-begin)/k;// шаг сканирования
			 //progressBar1->Visible=true;
			 //progressBar1->Value=(i+1)*di;
			 ////labelSec->Text=Convert::ToString(ind);
			 //ofstream of;
			 //try{
				// for (;i<n;i++)
				// {
				//	 j=0;
				//	 //I[i]=new double[k];
				//	 //double s=ds*i;

				//	 for(double x=begin;x<=end;x+=dx,j++){
				//		 sample->traceRays(m,E0,Ecr,widthBeam,yBeam,x,detector,1);
				//		 for(int d=0;d<detectorsCount;d++)
				//			 I[d][i][j]=(double)detector[d].getCount()/m;
				//		 sample->clear();
				//	 }
				//	 writeData(of,begin,end,j,k,z,i,n,thickness,m,I,"scan "+i+".txt");// 
				//	 progressBar1->Value=(i+1)*di;
				// }
			 //}catch(...){
				// //_CrtMemBlockHeader;
				// //_CrtDumpMemoryLeaks();
				//  writeData(of,begin,end,j,k,z,i,n,thickness,m,I,"scanerr.txt");
			 //}
			 //progressBar1->Value=false;
			 //double** topograph=new double*[n];
			 //double** compos=new double*[n];
			 //for(int i=0;i<n;i++){
				// topograph[i]=new double[k];
				// compos[i]=new double[k];
				// for (int j=0;j<k;j++){
				//	 topograph[i][j]=0;
				//	 compos[i][j]=0;
				//	 if(detectorsCount>1){
				//		 topograph[i][j]=(I[0][i][j]-I[1][i][j]);
				//		 compos[i][j]=I[0][i][j]+I[1][i][j];
				//	 }
				// }
			 //}
			 //Bitmap^ bmp=toImage(compos,n,k);
			 ////Graphics^ g=pictureBox1->CreateGraphics();
			 ////delete I;
			 ////of.close();
			 //pictureBox1->Image=bmp;
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 pin_ptr<int> var=&detectorsCount;
			 DetectorWindow^ win=gcnew DetectorWindow(detectors,var);
			 win->ShowDialog();
		 }
private: System::Void radioButtonTopograph_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(radioButtonTopograph->Checked)pictureBox1->Image=topog;
		 }
private: System::Void radioButtonCompos_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(radioButtonCompos->Checked)pictureBox1->Image=comp;
		 }
};
}
