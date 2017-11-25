#pragma once
#include <iostream>
#include <cstring>
#include <windows.h>
#include <gl\GL.h>
#include <gl\glu.h>              // Заголовочные файлы для библиотеки GLu32
#include <gl\glaux.h>  
#include "SampleParameters.h"
#include "ParametersWindow.h"
#include "AnalyseWindow.h"
#include "RayParameterWindow.h"
#include "DetectorWindow.h"
#include "Detector.h"
#include "Scan3DWindow.h"
#include "SampleParameters3D.h"

//#ifdef _DEBUG
//#include <crtdbg.h>
//#define _CRTDBG_MAP_ALLOC
//#endif

namespace Litography {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace System::Windows;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
		SampleParameters* sample; // образец в 2d 
		SampleParameters3D* sample3D;
		Detector* detectors;// детекторы
		int detectorsCount;// число активных детекторов
		Graphics^ g;
		Bitmap^ bmp;
		int xPrev;
		int yPrev;
		int emmitedElectronsCount;// число вылетевших электронов
		double width,height;// ширина высота
		//double section;// сечение
		int raysCount;
		double* diameterRay; //ширина пучка
		double* rayDistance; // расстояние от эл. пушки до образца
		double* displaceX; // смещение пушки по х
		double scaleX,scaleY;

	private: System::Windows::Forms::ToolStripMenuItem^  сохранитьИзображениеToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^  saveFileImage;


	private: System::Windows::Forms::TextBox^  textBoxInitialEnergy;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBoxCriticalEnergy;


	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  labelEmission;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  labelElectronCount2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::NumericUpDown^  numericRays;





	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem;


	private: System::Windows::Forms::Label^  labelError;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBoxDisplace;

	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::Windows::Forms::Label^  labelWaveLength;
	private: System::Windows::Forms::ToolStripMenuItem^  детекторыToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  дополнительноToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  распределениеДозToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  сканированиеToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dСканированиеToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  сохранитьДанныеToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^  загрузитьДанныеToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;

	private: System::Windows::Forms::Label^  labelMessage;
	private: System::Windows::Forms::ToolStripMenuItem^  пробеговToolStripMenuItem;

	private: System::Windows::Forms::Label^  label2;
	public:
		Form1(void)
		{
			InitializeComponent();
			sample=new SampleParameters(14,28,2.33);
			sample3D=new SampleParameters3D(14,28,2.33);
			raysCount=10;
			sample->setRaysCount(raysCount);
			sample->relief=Relief2D::defaultRelief(); 
			sample3D->relief=Relief3D::defaultRelief();
			numericRays->Value=raysCount;
			balance(0,raysCount);
			numericRays->Maximum=LONG_MAX;
//			bmp=gcnew Bitmap(pictureBoxTrace->Width,pictureBoxTrace->Height);
			//g=pictureBoxTrace->CreateGraphics();
			width=height=0;
			diameterRay=new double[1];
			rayDistance=new double[1];
			displaceX=new double[1];
			diameterRay[0]=5.0E-7;
			rayDistance[0]=5.0e-1;
			displaceX[0]=0.0;
			scaleX=scaleY=1.0;
			detectorsCount=3;
			detectorsInit();
			
			//createReliefLine();
			//g=Graphics::FromImage(bmp);
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		void detectorsInit(){
			detectors=new Detector[detectorsCount];
			detectors[0].x=0.0;
			detectors[1].x=0.5;
			detectors[2].x=-0.5;
			detectors[0].y=detectors[1].y=detectors[2].y=0.5;
			detectors[0].setSize(0.5);
			detectors[1].setSize(0.5);
			detectors[2].setSize(0.5);
			detectors[0].angle=0.0;
			detectors[1].angle=Math::PI/4;
			detectors[2].angle=-Math::PI/4;
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^  calculateButton;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  опцииToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  изменитьПараметрыToolStripMenuItem;
	private: System::ComponentModel::IContainer^  components;
	protected: 


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


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
			this->calculateButton = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->опцииToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьИзображениеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьДанныеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->загрузитьДанныеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->изменитьПараметрыToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->детекторыToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->дополнительноToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->распределениеДозToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сканированиеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dСканированиеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->пробеговToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveFileImage = (gcnew System::Windows::Forms::SaveFileDialog());
			this->textBoxInitialEnergy = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBoxCriticalEnergy = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->labelEmission = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->labelElectronCount2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->numericRays = (gcnew System::Windows::Forms::NumericUpDown());
			this->labelError = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBoxDisplace = (gcnew System::Windows::Forms::TextBox());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->labelWaveLength = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->labelMessage = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericRays))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// calculateButton
			// 
			this->calculateButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->calculateButton->Location = System::Drawing::Point(734, 425);
			this->calculateButton->Name = L"calculateButton";
			this->calculateButton->Size = System::Drawing::Size(120, 27);
			this->calculateButton->TabIndex = 1;
			this->calculateButton->Text = L"расчет";
			this->calculateButton->UseVisualStyleBackColor = true;
			this->calculateButton->Click += gcnew System::EventHandler(this, &Form1::calculateButton_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->опцииToolStripMenuItem, 
				this->дополнительноToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(873, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// опцииToolStripMenuItem
			// 
			this->опцииToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->сохранитьИзображениеToolStripMenuItem, 
				this->сохранитьДанныеToolStripMenuItem, this->загрузитьДанныеToolStripMenuItem, this->изменитьПараметрыToolStripMenuItem, this->ToolStripMenuItem, 
				this->детекторыToolStripMenuItem});
			this->опцииToolStripMenuItem->Name = L"опцииToolStripMenuItem";
			this->опцииToolStripMenuItem->Size = System::Drawing::Size(56, 20);
			this->опцииToolStripMenuItem->Text = L"Опции";
			// 
			// сохранитьИзображениеToolStripMenuItem
			// 
			this->сохранитьИзображениеToolStripMenuItem->Name = L"сохранитьИзображениеToolStripMenuItem";
			this->сохранитьИзображениеToolStripMenuItem->Size = System::Drawing::Size(233, 22);
			this->сохранитьИзображениеToolStripMenuItem->Text = L"Сохранить изображение";
			this->сохранитьИзображениеToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::сохранитьИзображениеToolStripMenuItem_Click);
			// 
			// сохранитьДанныеToolStripMenuItem
			// 
			this->сохранитьДанныеToolStripMenuItem->Name = L"сохранитьДанныеToolStripMenuItem";
			this->сохранитьДанныеToolStripMenuItem->Size = System::Drawing::Size(233, 22);
			this->сохранитьДанныеToolStripMenuItem->Text = L"Сохранить данные";
			this->сохранитьДанныеToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::сохранитьДанныеToolStripMenuItem_Click);
			// 
			// загрузитьДанныеToolStripMenuItem
			// 
			this->загрузитьДанныеToolStripMenuItem->Name = L"загрузитьДанныеToolStripMenuItem";
			this->загрузитьДанныеToolStripMenuItem->Size = System::Drawing::Size(233, 22);
			this->загрузитьДанныеToolStripMenuItem->Text = L"Загрузить данные";
			this->загрузитьДанныеToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::загрузитьДанныеToolStripMenuItem_Click);
			// 
			// изменитьПараметрыToolStripMenuItem
			// 
			this->изменитьПараметрыToolStripMenuItem->Name = L"изменитьПараметрыToolStripMenuItem";
			this->изменитьПараметрыToolStripMenuItem->Size = System::Drawing::Size(233, 22);
			this->изменитьПараметрыToolStripMenuItem->Text = L"Вещество";
			this->изменитьПараметрыToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::изменитьПараметрыToolStripMenuItem_Click);
			// 
			// ToolStripMenuItem
			// 
			this->ToolStripMenuItem->Name = L"ToolStripMenuItem";
			this->ToolStripMenuItem->Size = System::Drawing::Size(233, 22);
			this->ToolStripMenuItem->Text = L"Параметры пучка и рельефа";
			this->ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::параметрыПучкаToolStripMenuItem_Click);
			// 
			// детекторыToolStripMenuItem
			// 
			this->детекторыToolStripMenuItem->Name = L"детекторыToolStripMenuItem";
			this->детекторыToolStripMenuItem->Size = System::Drawing::Size(233, 22);
			this->детекторыToolStripMenuItem->Text = L"Детекторы";
			this->детекторыToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::детекторыToolStripMenuItem_Click);
			// 
			// дополнительноToolStripMenuItem
			// 
			this->дополнительноToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->распределениеДозToolStripMenuItem1, 
				this->сканированиеToolStripMenuItem, this->dСканированиеToolStripMenuItem, this->пробеговToolStripMenuItem});
			this->дополнительноToolStripMenuItem->Name = L"дополнительноToolStripMenuItem";
			this->дополнительноToolStripMenuItem->Size = System::Drawing::Size(59, 20);
			this->дополнительноToolStripMenuItem->Text = L"Анализ";
			// 
			// распределениеДозToolStripMenuItem1
			// 
			this->распределениеДозToolStripMenuItem1->Name = L"распределениеДозToolStripMenuItem1";
			this->распределениеДозToolStripMenuItem1->Size = System::Drawing::Size(179, 22);
			this->распределениеДозToolStripMenuItem1->Text = L"Распределение доз";
			this->распределениеДозToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::распределениеДозToolStripMenuItem1_Click);
			// 
			// сканированиеToolStripMenuItem
			// 
			this->сканированиеToolStripMenuItem->Name = L"сканированиеToolStripMenuItem";
			this->сканированиеToolStripMenuItem->Size = System::Drawing::Size(179, 22);
			this->сканированиеToolStripMenuItem->Text = L"Сканирование";
			this->сканированиеToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::сканированиеToolStripMenuItem_Click);
			// 
			// dСканированиеToolStripMenuItem
			// 
			this->dСканированиеToolStripMenuItem->Name = L"dСканированиеToolStripMenuItem";
			this->dСканированиеToolStripMenuItem->Size = System::Drawing::Size(179, 22);
			this->dСканированиеToolStripMenuItem->Text = L"3D Сканирование";
			this->dСканированиеToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::dСканированиеToolStripMenuItem_Click);
			// 
			// пробеговToolStripMenuItem
			// 
			this->пробеговToolStripMenuItem->Name = L"пробеговToolStripMenuItem";
			this->пробеговToolStripMenuItem->Size = System::Drawing::Size(179, 22);
			this->пробеговToolStripMenuItem->Text = L"Длины пробегов";
			this->пробеговToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::пробеговToolStripMenuItem_Click);
			// 
			// textBoxInitialEnergy
			// 
			this->textBoxInitialEnergy->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBoxInitialEnergy->Location = System::Drawing::Point(668, 77);
			this->textBoxInitialEnergy->Name = L"textBoxInitialEnergy";
			this->textBoxInitialEnergy->Size = System::Drawing::Size(78, 20);
			this->textBoxInitialEnergy->TabIndex = 3;
			this->textBoxInitialEnergy->Text = L"10";
			this->textBoxInitialEnergy->TextChanged += gcnew System::EventHandler(this, &Form1::textBoxInitialEnergy_TextChanged);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(665, 48);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(131, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Начальная энергия, кэВ";
			// 
			// textBoxCriticalEnergy
			// 
			this->textBoxCriticalEnergy->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBoxCriticalEnergy->Location = System::Drawing::Point(668, 145);
			this->textBoxCriticalEnergy->Name = L"textBoxCriticalEnergy";
			this->textBoxCriticalEnergy->Size = System::Drawing::Size(78, 20);
			this->textBoxCriticalEnergy->TabIndex = 5;
			this->textBoxCriticalEnergy->Text = L"0,2";
			this->textBoxCriticalEnergy->TextChanged += gcnew System::EventHandler(this, &Form1::textBoxCriticalEnergy_TextChanged);
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(665, 117);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(116, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Критическая энергия";
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(668, 190);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(188, 13);
			this->label3->TabIndex = 9;
			this->label3->Text = L"коэффициент обратного рассеяния";
			// 
			// labelEmission
			// 
			this->labelEmission->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->labelEmission->AutoSize = true;
			this->labelEmission->Location = System::Drawing::Point(668, 216);
			this->labelEmission->Name = L"labelEmission";
			this->labelEmission->Size = System::Drawing::Size(13, 13);
			this->labelEmission->TabIndex = 10;
			this->labelEmission->Text = L"0";
			// 
			// label5
			// 
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(668, 240);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(120, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"электронов в образце";
			// 
			// labelElectronCount2
			// 
			this->labelElectronCount2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->labelElectronCount2->AutoSize = true;
			this->labelElectronCount2->Location = System::Drawing::Point(668, 264);
			this->labelElectronCount2->Name = L"labelElectronCount2";
			this->labelElectronCount2->Size = System::Drawing::Size(13, 13);
			this->labelElectronCount2->TabIndex = 12;
			this->labelElectronCount2->Text = L"0";
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(668, 295);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(67, 13);
			this->label4->TabIndex = 13;
			this->label4->Text = L"число лучей";
			// 
			// numericRays
			// 
			this->numericRays->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->numericRays->Location = System::Drawing::Point(671, 322);
			this->numericRays->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericRays->Name = L"numericRays";
			this->numericRays->Size = System::Drawing::Size(115, 20);
			this->numericRays->TabIndex = 14;
			this->numericRays->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericRays->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown1_ValueChanged);
			// 
			// labelError
			// 
			this->labelError->AutoSize = true;
			this->labelError->ForeColor = System::Drawing::Color::Red;
			this->labelError->Location = System::Drawing::Point(657, 423);
			this->labelError->Name = L"labelError";
			this->labelError->Size = System::Drawing::Size(0, 13);
			this->labelError->TabIndex = 18;
			// 
			// label6
			// 
			this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(668, 354);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(60, 13);
			this->label6->TabIndex = 19;
			this->label6->Text = L"Сдвиг по х";
			// 
			// textBoxDisplace
			// 
			this->textBoxDisplace->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBoxDisplace->Location = System::Drawing::Point(668, 370);
			this->textBoxDisplace->Name = L"textBoxDisplace";
			this->textBoxDisplace->Size = System::Drawing::Size(118, 20);
			this->textBoxDisplace->TabIndex = 20;
			this->textBoxDisplace->Text = L"0";
			// 
			// comboBox3
			// 
			this->comboBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"см", L"мм", L"мкм", L"нм"});
			this->comboBox3->Location = System::Drawing::Point(794, 370);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(43, 21);
			this->comboBox3->TabIndex = 21;
			this->comboBox3->Text = L"см";
			// 
			// labelWaveLength
			// 
			this->labelWaveLength->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->labelWaveLength->AutoSize = true;
			this->labelWaveLength->Location = System::Drawing::Point(746, 80);
			this->labelWaveLength->Name = L"labelWaveLength";
			this->labelWaveLength->Size = System::Drawing::Size(0, 13);
			this->labelWaveLength->TabIndex = 22;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// chart1
			// 
			this->chart1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			chartArea1->AxisX->IsStartedFromZero = false;
			chartArea1->AxisX->LabelStyle->Format = L"e2";
			chartArea1->AxisX->MajorGrid->Enabled = false;
			chartArea1->AxisX->Maximum = 1;
			chartArea1->AxisX->Minimum = -1;
			chartArea1->AxisX->ScaleView->Zoomable = false;
			chartArea1->AxisX->ScrollBar->BackColor = System::Drawing::Color::Black;
			chartArea1->AxisX->ScrollBar->Enabled = false;
			chartArea1->AxisY->IsStartedFromZero = false;
			chartArea1->AxisY->LabelStyle->Format = L"E2";
			chartArea1->AxisY->MajorGrid->Enabled = false;
			chartArea1->AxisY->ScaleView->Zoomable = false;
			chartArea1->AxisY->ScrollBar->Enabled = false;
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Enabled = false;
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(12, 36);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(647, 364);
			this->chart1->TabIndex = 23;
			this->chart1->Text = L"chart1";
			this->chart1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::chart1_KeyPress);
			this->chart1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::chart1_MouseClick);
			this->chart1->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::chart1_MouseDoubleClick);
			this->chart1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::chart1_MouseWheel);
			// 
			// labelMessage
			// 
			this->labelMessage->AutoSize = true;
			this->labelMessage->Location = System::Drawing::Point(469, 432);
			this->labelMessage->Name = L"labelMessage";
			this->labelMessage->Size = System::Drawing::Size(0, 13);
			this->labelMessage->TabIndex = 25;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(873, 461);
			this->Controls->Add(this->labelMessage);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->labelWaveLength);
			this->Controls->Add(this->comboBox3);
			this->Controls->Add(this->textBoxDisplace);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->labelError);
			this->Controls->Add(this->numericRays);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->labelElectronCount2);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->labelEmission);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBoxCriticalEnergy);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBoxInitialEnergy);
			this->Controls->Add(this->calculateButton);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->MinimumSize = System::Drawing::Size(850, 250);
			this->Name = L"Form1";
			this->Text = L"MCSimulator";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericRays))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		double random(){
			return rand()/(double) RAND_MAX;
		}
		void createReliefLine(){
			chart1->Series->Add("relief");
			chart1->Series["relief"]->Color=Color::Red;
			chart1->Series["relief"]->ChartType=DataVisualization::Charting::SeriesChartType::Line;
		}
		void balance(int oldCount,int newCount){
			if (oldCount<newCount)
			{
				try{
					for(int i=oldCount;i<newCount;i++){
						int ind=chart1->Series->IndexOf("Series "+i);
						if (ind==-1)
						{
							chart1->Series->Add("Series "+i);
							chart1->Series[i]->Color=Color::Black;
							chart1->Series[i]->ChartType=DataVisualization::Charting::SeriesChartType::Line;
						}
					}
					int rel= chart1->Series->IndexOf("relief");
					if(rel!=-1){
						chart1->Series["relief"]->Points->Clear();
					}else createReliefLine();
					for(int i=0;i<3;i++){
						rel=chart1->Series->IndexOf("detector "+i);
						if(rel==-1) {
							chart1->Series->Add("detector "+i);
							chart1->Series["detector "+i]->Color=Color::Gray;
							chart1->Series["detector "+i]->ChartType=DataVisualization::Charting::SeriesChartType::Line;
						}
						else chart1->Series["detector "+i]->Points->Clear();
					}
				}
				/*if(!chart1->Series[i])*/
				catch(ArgumentException^ e){
					chart1->Series->Add("Series "+1);
				}
			}else{
				for(int i=newCount;i<oldCount;i++){
					chart1->Series[i]->Points->Clear();
				}
			}
			raysCount=newCount;
		}
		void maxXY(double &maxX,double &minY){
			list<Node>::iterator point=sample->rays[0].points->begin();
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
		int minYRay(int &index,double& minY){
			if(!sample->rays) return 0;
			list<Node>::iterator point=sample->rays[0].points->begin();
			//list<double>::iterator itY=sample->rays[0].y->begin();
			index=0;
			minY=point->y;
			int n=raysCount;
			for(int i=0;i<n;i++){
				point=sample->rays[i].points->begin();
				//itY=sample->rays[i].y->begin();
				for(;point!=sample->rays[i].points->end();point++){
					if (minY>(point->y)){
						minY=point->y;
						index=i;
					}
				}
			}
			return index;
		}
		void correction(char str[]){
			char* begin=strchr(str,'e');
			while(begin[0]!='0')begin++;
			char* end=begin;
			while(end[0]=='0')end++;
			//if(s==NULL)return;
			for (;end[0]!=NULL;begin++,end++)
				begin[0]=end[0];
			begin[0]=NULL;
		}
		void visualize(){// визуализация
			double w,h;
			maxXY(w,h);	// глубина и ширина пучка
			width=2*w;
			height=h;
			double side=Math::Max(abs(height),width);
			//chart1->ChartAreas[0]->AxisX->Minimum=-w+*displaceX;
			//chart1->ChartAreas[0]->AxisX->Maximum=w+*displaceX;
			chart1->ChartAreas[0]->AxisX->Minimum=-side/2+*displaceX;
			chart1->ChartAreas[0]->AxisX->Maximum=side/2+*displaceX;
			chart1->ChartAreas[0]->AxisY->Maximum=sample->relief->getMaxY();
			chart1->ChartAreas[0]->AxisY->Minimum=-side/2;

			balance(raysCount,sample->getRaysCount());
			emmitedElectronsCount=0;
			for(int i=0;i<sample->getRaysCount();i++){
				chart1->Series[i]->Points->Clear();
				list<Node>::iterator point=sample->rays[i].points->begin();
				chart1->Series[i]->Points->AddXY(point->x,point->y);
				int x0,y0;
				y0=0;
				point++;
				int k=0;
				for(;point!=sample->rays[i].points->end();point++){
					try{
						chart1->Series[i]->Points->AddXY(point->x,point->y);
						// k++;
					}
					catch(OverflowException^ e){
						String^ mes = e->ToString();
					}
				}
				point--;
				if(!sample->relief->isInMaterial(point->x,point->y)){
					chart1->Series[i]->Color=Color::Red;
					emmitedElectronsCount++;
				}else chart1->Series[i]->Color=Color::Black;
			}
			if(sample->relief){// отрисовка рельефа
				chart1->Series["relief"]->Points->Clear();
				for(int i=0;i<sample->relief->getSize();i++){
					double x=sample->relief->getX(i);
					double y=sample->relief->getY(i);
					chart1->Series["relief"]->Points->AddXY(x,y);
				}
				chart1->Series["relief"]->Color=Color::Gray;
			}
			// отрисовка детекторов
			for(int i=0;i<3;i++) {
				chart1->Series["detector "+i]->Points->Clear();
			}
			for(int i=0;i<detectorsCount;i++){
				double w2cos=detectors[i].getSize()/2*Math::Cos(detectors[i].angle);// w/2*cos(alpha)
				double x0=detectors[i].x-w2cos;
				double x1=detectors[i].x+w2cos;
				double w2sin=detectors[i].getSize()/2*Math::Sin(detectors[i].angle);
				double y0=detectors[i].y+w2sin;
				double y1=detectors[i].y-w2sin;
				chart1->Series["detector "+i]->Points->AddXY(x0,y0);
				chart1->Series["detector "+i]->Points->AddXY(x1,y1);
			}
		}
		double sqr(double x){return x*x;}
		void visualize3D(){// визуализация
			double w,h;
			maxXY(w,h);	// глубина и ширина пучка
			width=2*w;
			height=h;
			double side=Math::Max(abs(height),width);
			//chart1->ChartAreas[0]->AxisX->Minimum=-w+*displaceX;
			//chart1->ChartAreas[0]->AxisX->Maximum=w+*displaceX;
			chart1->ChartAreas[0]->AxisX->Minimum=-side/2+*displaceX;
			chart1->ChartAreas[0]->AxisX->Maximum=side/2+*displaceX;
			chart1->ChartAreas[0]->AxisY->Maximum=0.0;
			chart1->ChartAreas[0]->AxisY->Minimum=-side;

			balance(raysCount,sample3D->getRaysCount());
			emmitedElectronsCount=0;
			for(int i=0;i<sample3D->getRaysCount();i++){
				chart1->Series[i]->Points->Clear();
				list<Node3D>::iterator point=sample3D->rays[i].points->begin();
				//chart1->Series[i]->Points->AddXY(point->x,point->y);
				int n=sample3D->rays[i].points->size();
				cli::array<Point3D^>^ p=gcnew cli::array<Point3D^>(n);
				point++;
				//int k=0;
				for(int k=0;k<n;k++){
					p[k]=gcnew Point3D(point->x,point->y,point->z);
					point++;
				}
				point--;
				//chart1->Series[i]->Points
				if(sample3D->relief->isInMaterial(point->x,point->y,point->z)){
					emmitedElectronsCount++;
				}
			}
			if(sample->relief){// отрисовка рельефа
				chart1->Series["relief"]->Points->Clear();
				for(int i=0;i<sample->relief->getSize();i++){
					double x=sample->relief->getX(i);
					double y=sample->relief->getY(i);
					chart1->Series["relief"]->Points->AddXY(x,y);
				}
				chart1->Series["relief"]->Color=Color::Red;
			}

			for(int i=0;i<3;i++) {
				chart1->Series["detector "+i]->Points->Clear();
			}
			for(int i=0;i<detectorsCount;i++){
				double w2cos=detectors[i].getSize()/2*Math::Cos(detectors[i].angle);// w/2*cos(alpha)
				double x0=detectors[i].x-w2cos;
				double x1=detectors[i].x+w2cos;
				double w2sin=detectors[i].getSize()/2*Math::Sin(detectors[i].angle);
				double y0=detectors[i].y+w2sin;
				double y1=detectors[i].y-w2sin;
				chart1->Series["detector "+i]->Points->AddXY(x0,y0);
				chart1->Series["detector "+i]->Points->AddXY(x1,y1);
			}
		}
		void singlescattering(){

			int Z=13; //atomic number Silicon
			double Ein=10; //Incoming energy E in keV
			double A=27;//Atomic weight g/mole
			double ro=2.7;//density in gr/cm3
			int traj_num=100;//number of trajectories or electrons
			double thick=0.0001;//Thickness of the sample in cm
			int dotf=0;//draw trayectories on the fly. 1=YES slow, 0=NO fast
			double Emin=1;
			//Calculate some constants
			double alpha_c=3.4e-3*pow(Z,0.67);//alpha or screening factor is 3.4e-3*Z^0.67/E;
			double Einr=((Ein+511.0)/(Ein+1024.0)); //Correction for relativistic energy	
			double lambda_c=(A/(ro*6.0e23));//lambda or MFP in cm is lambda=(A/(ro*6.0e23*scs)) *1.0e8 in angstrom
			double J=(9.76*Z+(58.5/pow(Z,0.19)))*0.001; //Mean ionisation potential

			chart1->ChartAreas[0]->AxisX->Minimum=-1*thick;
			chart1->ChartAreas[0]->AxisX->Maximum=1*thick;
			chart1->ChartAreas[0]->AxisY->Maximum=0;
			chart1->ChartAreas[0]->AxisY->Minimum=-1.5*thick;
			int bk_sct=0;
			int num=0;
			//LOOP for each electron
			while (num<traj_num){
				int rel= chart1->Series->IndexOf("trajectory "+num);
				if (rel==-1)
				{
					chart1->Series->Add("trajectory "+num);
					chart1->Series["trajectory "+num]->Color=Color::Black;
					chart1->Series["trajectory "+num]->ChartType=DataVisualization::Charting::SeriesChartType::Line;
				}else{
					chart1->Series["trajectory "+num]->Points->Clear();
				}
				
				// x, y, z are the initial coordinates of one step of the electron
				//reset coordinates at start of each trajectory x=xn, y=yn, z=zn and direction cosines cx=ca, cy=cb,
				double Esi=Ein; //Esi initial step energy
				double x=0;double y=0;double z=0;double cx=0;double cy=0;double cz=1;

				//Allow initial entrance of electron
				double alpha=alpha_c/Esi;
				double scs_v=5.21e-21*sqr(Z)*12.56*sqr(Einr);// scattering cross section is scs_c/(Esi^2*alpha(alpha+1));	
				double scs=scs_v/(sqr(Esi) *alpha*(alpha+1));
				double lambda=lambda_c/scs;
				double step=-lambda*Math::Log(random());
				double zn=step;

				if (zn >=thick){

				}else{
					z=zn;
					int bs=0;int tr=0; //Indices que indican si hay backscattering o tranmission
					while (Esi>Emin && bs==0 && tr==0){
						alpha=alpha_c/Esi;
						double scs_c=5.21e-21*sqr(Z)*12.56*sqr(Einr);
						scs=scs_c/(sqr(Esi)*alpha*(alpha+1));
						lambda=lambda_c/scs;
						step=-lambda*Math::Log(random());
						//Find scattering angles phi and gamma	
						double R1=random();
						double cos_phi=1-((2*alpha*R1)/(1+alpha-R1));
						double sin_phi=sqrt(1-sqr(cos_phi));
						double gamma=2*Math::PI*random();

						//Find finish coordinates of the step, xn, yn, zn
						if (cz==0){
							cz=0.000001;
						}
						double AM=-cx/cz;double AN=1/sqrt(1+sqr(AM));
						double V1=AN*sin_phi;double V2=AN*AM*sin_phi;double V3=cos(gamma);double V4=sin(gamma);
						double CA=(cx*cos_phi)+(V1*V3)+(cy*V2*V4);
						double CB=(cy*cos_phi)+V4*(cz*V1-cx*V2);
						double CC=(cz*cos_phi)+(V2*V3)-(cy*V1*V4);

						double xn=x+step*CA;
						double yn=y+step*CB;
						double zn=z+step*CC;

						if (zn<=0){
							//num=num+1;
							bk_sct=bk_sct+1;
							
							bs=1;
						}

						if (zn>thick){
							tr=1;

						}
						//Find final energy Ef=Ei-step*ro*SP being ro the density and SP the
						chart1->Series["trajectory "+num]->Points->AddXY(xn,-zn);
						DataVisualization::Charting::DataPointCollection^ P=chart1->Series["trajectory "+num]->Points;
						//chart1->Series["Series "+num]->Points->AddXY(0,-0.5);
						cx=CA; cy=CB; cz=CC;
						x=xn; y=yn; z=zn;
						//CAlculate Stopping power

						double dEdS=78500*(Z/(A*Esi))*log(1.166*(Esi+0.85*J)/J); //Stopping Power
						double dE=step*dEdS*ro;
						Esi=Esi-(dE);
					}
				}

				//DataVisualization::Charting::DataPointCollection^ P=chart1->Series["Series "+num]->Points;
				num++;
			}	
			
		}
	private: System::Void calculateButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 //singlescattering();
				 //return;
				 double E0=Convert::ToDouble(textBoxInitialEnergy->Text->Replace('.',','));// начальная энергия кэВ
				 double Ecr=Convert::ToDouble(textBoxCriticalEnergy->Text->Replace('.',','));
				 //Ecr=0.4*E0;
				 //return;
				 sample->citicalEnergy=Ecr;
				 // double R0=sample->depthOfPenetration(Ecr);// макс. длина пробега
				 switch(comboBox3->SelectedIndex){// смещение
				 case 0:
					 *displaceX=Convert::ToDouble(textBoxDisplace->Text->Replace('.',','));// см
					 break;
				 case 1:
					 *displaceX=Convert::ToDouble(textBoxDisplace->Text->Replace('.',','))/10;// мм 
					 break;
				 case 2:
					 *displaceX=Convert::ToDouble(textBoxDisplace->Text->Replace('.',','))/10000;  // mkm
					 break;
				 case 3:
					 *displaceX=Convert::ToDouble(textBoxDisplace->Text->Replace('.',','))/10000000;// nm
					 break;
				 }
				 if(*rayDistance < sample->relief->getY(*displaceX)){
					 labelError->Text="Ошибка! Недопустимое положение электронной пушки";
					 return;
				 }else labelError->Text="";
				 
				 int n=Convert::ToUInt64(numericRays->Value);
				 if(sample->isTraced()) 
					 sample->clear(); // очистка предыдущих лучей
				 sample->setRaysCount(n);
				 if(detectorsCount==0) sample->traceRays(n,E0,Ecr,*diameterRay,*rayDistance,*displaceX);// трассировка
				 else sample->traceRays(n,E0,Ecr,*diameterRay,*rayDistance,*displaceX,detectors,detectorsCount);
				 visualize();// визуализация
				 
				 char str[10];
				 sprintf(str,"%.3le",-height);
				 // labelDist->Text=gcnew String(str);
				 labelEmission->Text=Convert::ToString((double)emmitedElectronsCount/sample->getRaysCount());
				 labelElectronCount2->Text=Convert::ToString(sample->getRaysCount()-emmitedElectronsCount);
			 }
			 
	private: System::Void pictureBoxTrace_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 for(int i=0;i<1;i++){
					 list<Node>::iterator itp=sample->rays[0].points->begin();
					 //list<double>::iterator itY=sample->rays[0].y->begin();
					 //e->Graphics->DrawLine(System::Drawing::Pens::Green,pictureBoxTrace->Image , m_p[2], m_p[3], m_p[4]);
				 }
			 }
private: System::Void сохранитьИзображениеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (chart1->Images!=nullptr)
			 {
//				 pictureBoxTrace->Image=gcnew Bitmap(pictureBoxTrace->Width,pictureBoxTrace->Height,g);
				 saveFileImage->Filter="Image files | *.png ; *.jpeg ; *.bmp";
				 saveFileImage->FileName=Convert::ToString(sample->getRaysCount())+" "+textBoxInitialEnergy;
				 if (saveFileImage->ShowDialog()==Windows::Forms::DialogResult::OK)
				 {
					 chart1->SaveImage(saveFileImage->FileName,ChartImageFormat::Bmp); 
				 }
			 }
		 }
private: System::Void изменитьПараметрыToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 ParametersWindow^ pw=gcnew ParametersWindow(sample);
			 pw->ShowDialog();
		 }

private: System::Void buttonСut_Click(System::Object^  sender, System::EventArgs^  e) {
			 double screenWidth=chart1->ChartAreas[0]->AxisX->Maximum - chart1->ChartAreas[0]->AxisX->Minimum;
			 double screenHeight=chart1->ChartAreas[0]->AxisY->Maximum - chart1->ChartAreas[0]->AxisY->Minimum;

			 AnalyseWindow^ window=gcnew AnalyseWindow(sample,chart1->ChartAreas[0]->AxisX->Minimum,screenWidth,chart1->ChartAreas[0]->AxisY->Maximum,screenHeight);
			 //AnalyseWindow^ window=gcnew AnalyseWindow(sample,width,height,0);
			 window->ShowDialog();
		 }
private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 //sample->setRaysCount();
		 }
private: System::Void trackBarSection_Scroll(System::Object^  sender, System::EventArgs^  e) {
//			 if (height!=0)
//			 {
//				 int val=100-trackBarSection->Value;
//				 section=val*height/100;
//				 char str[10],* s;
//				 sprintf(str,"%.3le",-section);
//				 correction(str);
//				 String^ text=gcnew String(str);//
//				 labelSec->Text=text+"("+val+"%)";
//			 }else{
//				 int val=100-trackBarSection->Value; 
//			 labelSec->Text="0("+val+"%)";
//			 }
		 }
private: System::Void распределениеДозToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 AnalyseWindow^ window=gcnew AnalyseWindow(sample,chart1->ChartAreas[0]->AxisX->Minimum,chart1->ChartAreas[0]->AxisX->Maximum,chart1->ChartAreas[0]->AxisY->Minimum,chart1->ChartAreas[0]->AxisY->Maximum);
			 window->ShowDialog();
		 }
private: System::Void параметрыПучкаToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 RayParameterWindow^ wind=gcnew RayParameterWindow(diameterRay,rayDistance,displaceX,sample->relief);
			 wind->ShowDialog();
		 }

private: System::Void ReliefToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 //ReliefSelectWindow^ w=gcnew ReliefSelectWindow();
		 }

private: System::Void chart1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 this->chart1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::chart1_MouseMove);
			 xPrev=chart1->MousePosition.X;
			 yPrev=chart1->MousePosition.Y;
			
		 }
private: System::Void chart1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(chart1->MouseButtons==Forms::MouseButtons::Left){
				 double scaleX=(chart1->ChartAreas[0]->AxisX->Maximum-chart1->ChartAreas[0]->AxisX->Minimum)/(chart1->Width+115);
				 double scaleY=height/(chart1->Height+40);
				 double xNew=chart1->MousePosition.X;
				 double yNew=chart1->MousePosition.Y;
				 chart1->ChartAreas[0]->AxisX->Maximum-=scaleX*(xNew-xPrev);
				 chart1->ChartAreas[0]->AxisX->Minimum-=scaleX*(chart1->MousePosition.X-xPrev);
				 chart1->ChartAreas[0]->AxisY->Maximum+=scaleY*(yNew-yPrev);
				 chart1->ChartAreas[0]->AxisY->Minimum+=scaleY*(chart1->MousePosition.Y-yPrev);
			 }
		 }

private: System::Void chart1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e){
			 if(e->Delta<0){				 
				 //scaleX*=2;
				 //scaleY*=2;
				 chart1->ChartAreas[0]->AxisX->Maximum*=1.5;
				 chart1->ChartAreas[0]->AxisX->Minimum*=1.5;
				 chart1->ChartAreas[0]->AxisY->Minimum*=1.5;
				 chart1->ChartAreas[0]->AxisY->Maximum*=1.5;
			 }else{
				 //scaleX/=2;
				 //scaleY/=2;
				 chart1->ChartAreas[0]->AxisX->Maximum/=1.5;
				 chart1->ChartAreas[0]->AxisX->Minimum/=1.5;
				 chart1->ChartAreas[0]->AxisY->Minimum/=1.5;
				 chart1->ChartAreas[0]->AxisY->Maximum/=1.5;
			 }
			 //width=chart1->ChartAreas[0]->AxisX->Maximum-chart1->ChartAreas[0]->AxisX->Minimum;
			 //height=chart1->ChartAreas[0]->AxisY->Maximum-chart1->ChartAreas[0]->AxisY->Minimum;
			 //chart1->ChartAreas[0]->AxisX->ScaleView->Zoom(chart1->ChartAreas[0]->AxisX->Minimum*scaleX,chart1->ChartAreas[0]->AxisX->Maximum*scaleX);
			 //chart1->ChartAreas[0]->AxisY->ScaleView->Zoom(chart1->ChartAreas[0]->AxisY->Minimum*scaleY,chart1->ChartAreas[0]->AxisY->Maximum*scaleY);
		 };
private: System::Void chart1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 chart1->Focus();
		 }
private: System::Void chart1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			 double scaleX=(chart1->ChartAreas[0]->AxisX->Maximum-chart1->ChartAreas[0]->AxisX->Minimum)/(chart1->Width);
			 double scaleY=height/(chart1->Height);
			 double h=chart1->ChartAreas[0]->AxisY->Maximum-chart1->ChartAreas[0]->AxisY->Minimum;
			 double w=chart1->ChartAreas[0]->AxisX->Maximum-chart1->ChartAreas[0]->AxisX->Minimum;
			 switch(e->KeyChar){
			 case 'w':
				 
				 chart1->ChartAreas[0]->AxisY->Maximum-=scaleY*200;
				 //chart1->ChartAreas[0]->AxisY->Maximum=0.0001;
				 chart1->ChartAreas[0]->AxisY->Minimum-=scaleY*200;
				 break;
			 case 's':
				 h=chart1->ChartAreas[0]->AxisY->Maximum-chart1->ChartAreas[0]->AxisY->Minimum;
				 chart1->ChartAreas[0]->AxisY->Maximum+=scaleY*20;
				 chart1->ChartAreas[0]->AxisY->Minimum+=scaleY*20;
				 break;
			 case 'a':
				 
				 chart1->ChartAreas[0]->AxisX->Maximum-=scaleX*20;
				 chart1->ChartAreas[0]->AxisX->Minimum-=scaleX*20;
				 break;
			 case 'd':
				 w=0;
				 chart1->ChartAreas[0]->AxisX->Maximum+=scaleX*20;
				 chart1->ChartAreas[0]->AxisX->Minimum+=scaleX*20;
				 break;
			 }
		 }
private: System::Void chart1_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 chart1->ChartAreas[0]->AxisX->Maximum=width/2+displaceX[0];
			 chart1->ChartAreas[0]->AxisX->Minimum=-width/2+displaceX[0];
			 chart1->ChartAreas[0]->AxisY->Maximum=rayDistance[0];
			 chart1->ChartAreas[0]->AxisY->Minimum=height;
		 }
private: System::Void анализToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBoxInitialEnergy_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 try{
				 double E0=Convert::ToDouble(textBoxInitialEnergy->Text->Replace('.',','));// начальная энергия кэВ
				 double Ecr=Convert::ToDouble(textBoxCriticalEnergy->Text->Replace('.',','));
				 if(Ecr<E0) calculateButton->Enabled=true;
				 else throw gcnew System::ArgumentException("Ошибка: проверьте начальную и критическую энергию");
				 double val;
				 val=Ray::waveLength(E0);
				 char str[16];
				 //sprintf(str,"%0.6lf",val);
				 labelWaveLength->Text=Convert::ToString(val)+" мкм";
			 }
			 catch(System::FormatException^ e){
				 labelWaveLength->Text="NaN";
			 }catch(ArgumentException^ e){
				 labelError->Text=e->Message;
				 calculateButton->Enabled=false;
			 }
		 }
private: System::Void детекторыToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 pin_ptr<int> var=&detectorsCount;
			 DetectorWindow^ win=gcnew DetectorWindow(detectors,var);
			 win->ShowDialog();
		 }
private: System::Void textBoxCriticalEnergy_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 try{
				 double E0=Convert::ToDouble(textBoxInitialEnergy->Text->Replace('.',','));// начальная энергия кэВ
				 double Ecr=Convert::ToDouble(textBoxCriticalEnergy->Text->Replace('.',','));
				 if(Ecr>=E0){
					 labelError->Text="Ошибка: проверьте начальную и критическую энергию";
					 calculateButton->Enabled=false;
				 }else {
					 calculateButton->Enabled=true;
					 labelError->Text="";
				 }
			 }catch(FormatException^ e){
				 labelError->Text="Ошибка: некорректно введены данные";
			 }
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 double w,h;
			 maxXY(w,h);	// глубина и ширина пучка
			 width=2*w;
			 height=h;
			 double side=Math::Max(abs(height),width);
			 //chart1->ChartAreas[0]->AxisX->Minimum=-w+*displaceX;
			 //chart1->ChartAreas[0]->AxisX->Maximum=w+*displaceX;
			 chart1->ChartAreas[0]->AxisX->Minimum=-side/2+*displaceX;
			 chart1->ChartAreas[0]->AxisX->Maximum=side/2+*displaceX;
			 chart1->ChartAreas[0]->AxisY->Maximum=0.0;
			 chart1->ChartAreas[0]->AxisY->Minimum=-side;
			 int minI;
			 double minY;
			 minYRay(minI,minY);
			 balance(raysCount,sample->getRaysCount());
			 emmitedElectronsCount=0;
			 for(int i=0;i<sample->getRaysCount();i++){
				 chart1->Series[i]->Points->Clear();
				 list<Node>::iterator point=sample->rays[i].points->begin();
				 chart1->Series[i]->Points->AddXY(point->x,point->y);
				 point++;
				 int k=0;
				 for(;point!=sample->rays[i].points->end();point++){
					 try{
						 chart1->Series[i]->Points->AddXY(point->x,point->y);
						 // k++;
					 }
					 catch(OverflowException^ e){
						 String^ mes = e->ToString();
					 }
				 }
			 }
			 if(sample->relief){// отрисовка рельефа
				 chart1->Series["relief"]->Points->Clear();
				 for(int i=0;i<sample->relief->getSize();i++){
					 double x=sample->relief->getX(i);
					 double y=sample->relief->getY(i);
					 chart1->Series["relief"]->Points->AddXY(x,y);
				 }
				 chart1->Series["relief"]->Color=Color::Red;
			 }
		 }
private: System::Void сканированиеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 double E0=Convert::ToDouble(textBoxInitialEnergy->Text->Replace('.',','));
			 double Ecr=Convert::ToDouble(textBoxCriticalEnergy->Text->Replace('.',','));
			 switch(comboBox3->SelectedIndex){// смещение
			 case 0:
				 *displaceX=Convert::ToDouble(textBoxDisplace->Text->Replace('.',','));// см
				 break;
			 case 1:
				 *displaceX=Convert::ToDouble(textBoxDisplace->Text->Replace('.',','))/10;// мм 
				 break;
			 case 2:
				 *displaceX=Convert::ToDouble(textBoxDisplace->Text->Replace('.',','))/10000;  // mkm
				 break;
			 case 3:
				 *displaceX=Convert::ToDouble(textBoxDisplace->Text->Replace('.',','))/10000000;// nm
				 break;
			 }
			 if(*rayDistance < sample->relief->getY(*displaceX)){
				 labelError->Text="Ошибка! Недопустимое положение электронной пушки";
				 return;
			 }else labelError->Text="";
			 AnalyseWindow^ win=gcnew AnalyseWindow(sample,E0,Ecr,*diameterRay,*displaceX,*rayDistance,detectors);	 
			 win->Show();
		 }
private: System::Void dСканированиеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Scan3DWindow^ win=gcnew Scan3DWindow(sample,detectors,detectorsCount,*rayDistance,*diameterRay);
			 win->Show();
		 }
private: System::Void распределениеДозToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(sample->isTraced()){
				 double screenWidth=chart1->ChartAreas[0]->AxisX->Maximum - chart1->ChartAreas[0]->AxisX->Minimum;
				 double screenHeight=chart1->ChartAreas[0]->AxisY->Maximum - chart1->ChartAreas[0]->AxisY->Minimum;
				 AnalyseWindow^ window=gcnew AnalyseWindow(sample,chart1->ChartAreas[0]->AxisX->Minimum,screenWidth,chart1->ChartAreas[0]->AxisY->Maximum,screenHeight);
				 window->ShowDialog();
			 }
			 
		 }
private: System::Void сохранитьДанныеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 saveFileDialog1->Filter="MCSimulator files | *.mcstrace";
			 if(saveFileDialog1->ShowDialog()== Forms::DialogResult::OK){
				 char* fName=(char*)(void*)Marshal::StringToHGlobalAnsi("Z"+sample->getZNumber()+" "+sample->getRaysCount()+"rays "+sample->getRaysCount()+".mcstrace");
				 if(fName!="" ){
					 sample->output(fName,detectorsCount,detectors);
					 
				 }
			 }
			 
			 //sample->output("trace2.txt");
		 }
private: System::Void загрузитьДанныеToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 //if(sample->isTraced())sample->clear();
			 openFileDialog1->Filter="MCSimulator files | *.mcstrace";
			 if(openFileDialog1->ShowDialog()== Forms::DialogResult::OK){
				 try
				 {
					 char* name=(char*)(void*)Marshal::StringToHGlobalAnsi(openFileDialog1->FileName);
					 pin_ptr<int> c=&detectorsCount;
					 sample->input(name,*c,detectors);
					 detectorsCount=*c;
				 }
				 catch (exception& e)
				 {
					 labelError->Text=gcnew String(e.what());
					 //labelError->Text="ошибка чтения файла";
				 }
				 
				 catch(System::NullReferenceException^ e){

					 labelError->Text=e->Message;
				 }
				 visualize();
				 
			 }
		 }
private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 double E0=Convert::ToDouble(textBoxInitialEnergy->Text->Replace('.',','));// начальная энергия кэВ
			 double Ecr=Convert::ToDouble(textBoxCriticalEnergy->Text->Replace('.',','));
			 //Ecr=0.4*E0;
			 sample->citicalEnergy=Ecr;
			 // double R0=sample->depthOfPenetration(Ecr);// макс. длина пробега
			 
			 switch(comboBox3->SelectedIndex){// смещение
			 case 0:
				 *displaceX=Convert::ToDouble(textBoxDisplace->Text->Replace('.',','));// см
				 break;
			 case 1:
				 *displaceX=Convert::ToDouble(textBoxDisplace->Text->Replace('.',','))/10;// мм 
				 break;
			 case 2:
				 *displaceX=Convert::ToDouble(textBoxDisplace->Text->Replace('.',','))/10000;  // mkm
				 break;
			 case 3:
				 *displaceX=Convert::ToDouble(textBoxDisplace->Text->Replace('.',','))/10000000;// nm
				 break;
			 }
			 if(*rayDistance < sample->relief->getY(*displaceX)){
				 labelError->Text="Ошибка! Недопустимое положение электронной пушки";
				 return;
			 }else labelError->Text="";
			 int n=Convert::ToUInt64(numericRays->Value);
			 labelMessage->Text="очистка";
			 
			 sample3D->setRaysCount(n);
			 labelMessage->Text="трассировка";
			 if(sample3D->isTraced())sample3D->clear();
			 if(detectorsCount==0) sample3D->traceRays(n,E0,Ecr,*diameterRay,*rayDistance,*displaceX);// трассировка
			 else sample3D->traceRays(n,E0,Ecr,*diameterRay,*rayDistance,*displaceX,detectors,detectorsCount);
			 //visualize3D();// визуализация
			 labelMessage->Text="запись завершена";
			 sample3D->output("sample3D.txt");
			 //labelMessage->Text="запись завершена";
			 //sample3D->output("sample3D.txt");
			 //delete sample3D;
		 }
private: System::Void пробеговToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 //if (sample.isTraced()){
				 AnalyseWindow^ window=gcnew AnalyseWindow(2);
				 window->ShowDialog();
			 //}
		 }
private: System::Void дополнительноToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			 //if (sample.isTraced()){
				 AnalyseWindow^ window=gcnew AnalyseWindow(3);
				 window->ShowDialog();
			 //}
		 }
};
}