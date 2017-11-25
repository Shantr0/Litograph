#pragma once
#include "SampleParameters.h"
#include "Relief2D.h"
namespace Litography {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for RayParameterWindow
	/// </summary>
	public ref class RayParameterWindow : public System::Windows::Forms::Form
	{
	public:
		double* width;
		double* height;
		double* displace;
		Relief2D* relief;
	private: System::Windows::Forms::Button^  OKbutton;
	public: 
	private: System::Windows::Forms::Button^  button2;


	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::RadioButton^  radioButtonSteps;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::TextBox^  textBoxPeriod;

	private: System::Windows::Forms::TextBox^  textBoxWidth;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBoxHeight1;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::RadioButton^  radioButtonRandom;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::TextBox^  textBoxDepths;

	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  textBoxHeight2;

	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBoxWidth2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDownStepsCount;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TextBox^  textBoxLowWidth;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;

	private: System::Windows::Forms::Label^  label9;

			 

	public: RayParameterWindow(double *width,double *height,double* displace, Relief2D* relief)
		{
			InitializeComponent();
			this->width=width;
			this->height=height;
			this->displace=displace;
			this->relief=relief;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RayParameterWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxDiameterBundle;
	private: System::Windows::Forms::TextBox^  textBoxDistance;



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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBoxDiameterBundle = (gcnew System::Windows::Forms::TextBox());
			this->textBoxDistance = (gcnew System::Windows::Forms::TextBox());
			this->OKbutton = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->radioButtonSteps = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->textBoxLowWidth = (gcnew System::Windows::Forms::TextBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->numericUpDownStepsCount = (gcnew System::Windows::Forms::NumericUpDown());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->textBoxPeriod = (gcnew System::Windows::Forms::TextBox());
			this->textBoxWidth = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBoxHeight1 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->radioButtonRandom = (gcnew System::Windows::Forms::RadioButton());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->textBoxWidth2 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBoxDepths = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBoxHeight2 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownStepsCount))->BeginInit();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(84, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Диаметр пучка";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 82);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(127, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Расстояние до образца";
			// 
			// textBoxDiameterBundle
			// 
			this->textBoxDiameterBundle->Location = System::Drawing::Point(191, 21);
			this->textBoxDiameterBundle->Name = L"textBoxDiameterBundle";
			this->textBoxDiameterBundle->Size = System::Drawing::Size(100, 20);
			this->textBoxDiameterBundle->TabIndex = 2;
			// 
			// textBoxDistance
			// 
			this->textBoxDistance->Location = System::Drawing::Point(191, 82);
			this->textBoxDistance->Name = L"textBoxDistance";
			this->textBoxDistance->Size = System::Drawing::Size(100, 20);
			this->textBoxDistance->TabIndex = 3;
			// 
			// OKbutton
			// 
			this->OKbutton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->OKbutton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->OKbutton->Location = System::Drawing::Point(12, 222);
			this->OKbutton->Name = L"OKbutton";
			this->OKbutton->Size = System::Drawing::Size(75, 23);
			this->OKbutton->TabIndex = 4;
			this->OKbutton->Text = L"OK";
			this->OKbutton->UseVisualStyleBackColor = true;
			this->OKbutton->Click += gcnew System::EventHandler(this, &RayParameterWindow::OKbutton_Click);
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button2->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button2->Location = System::Drawing::Point(836, 222);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(76, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Отмена";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"см", L"мм", L"мкм", L"нм"});
			this->comboBox1->Location = System::Drawing::Point(297, 21);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(43, 21);
			this->comboBox1->TabIndex = 8;
			this->comboBox1->Text = L"см";
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"см", L"мм", L"мкм", L"нм"});
			this->comboBox2->Location = System::Drawing::Point(297, 82);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(43, 21);
			this->comboBox2->TabIndex = 9;
			this->comboBox2->Text = L"см";
			// 
			// radioButtonSteps
			// 
			this->radioButtonSteps->AutoSize = true;
			this->radioButtonSteps->Checked = true;
			this->radioButtonSteps->Location = System::Drawing::Point(389, 21);
			this->radioButtonSteps->Name = L"radioButtonSteps";
			this->radioButtonSteps->Size = System::Drawing::Size(90, 17);
			this->radioButtonSteps->TabIndex = 11;
			this->radioButtonSteps->TabStop = true;
			this->radioButtonSteps->Tag = L"1";
			this->radioButtonSteps->Text = L"Ступенчатый";
			this->radioButtonSteps->UseVisualStyleBackColor = true;
			this->radioButtonSteps->CheckedChanged += gcnew System::EventHandler(this, &RayParameterWindow::radioButtonSteps_CheckedChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(537, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(46, 13);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Рельеф";
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->textBoxLowWidth);
			this->panel1->Controls->Add(this->checkBox1);
			this->panel1->Controls->Add(this->label11);
			this->panel1->Controls->Add(this->numericUpDownStepsCount);
			this->panel1->Controls->Add(this->label10);
			this->panel1->Controls->Add(this->textBoxPeriod);
			this->panel1->Controls->Add(this->textBoxWidth);
			this->panel1->Controls->Add(this->label6);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->textBoxHeight1);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Location = System::Drawing::Point(389, 52);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(250, 167);
			this->panel1->TabIndex = 13;
			// 
			// textBoxLowWidth
			// 
			this->textBoxLowWidth->Enabled = false;
			this->textBoxLowWidth->Location = System::Drawing::Point(3, 63);
			this->textBoxLowWidth->Name = L"textBoxLowWidth";
			this->textBoxLowWidth->Size = System::Drawing::Size(100, 20);
			this->textBoxLowWidth->TabIndex = 28;
			this->textBoxLowWidth->Text = L"0.1";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(231, 68);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(15, 14);
			this->checkBox1->TabIndex = 27;
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &RayParameterWindow::checkBox1_CheckedChanged);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(109, 66);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(116, 13);
			this->label11->TabIndex = 26;
			this->label11->Text = L"Ширина ступени (низ)";
			// 
			// numericUpDownStepsCount
			// 
			this->numericUpDownStepsCount->Location = System::Drawing::Point(6, 136);
			this->numericUpDownStepsCount->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->numericUpDownStepsCount->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDownStepsCount->Name = L"numericUpDownStepsCount";
			this->numericUpDownStepsCount->Size = System::Drawing::Size(97, 20);
			this->numericUpDownStepsCount->TabIndex = 24;
			this->numericUpDownStepsCount->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(117, 138);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(85, 13);
			this->label10->TabIndex = 25;
			this->label10->Text = L"число ступеней";
			// 
			// textBoxPeriod
			// 
			this->textBoxPeriod->Location = System::Drawing::Point(3, 110);
			this->textBoxPeriod->Name = L"textBoxPeriod";
			this->textBoxPeriod->Size = System::Drawing::Size(191, 20);
			this->textBoxPeriod->TabIndex = 5;
			this->textBoxPeriod->Text = L"0";
			// 
			// textBoxWidth
			// 
			this->textBoxWidth->Location = System::Drawing::Point(3, 31);
			this->textBoxWidth->Name = L"textBoxWidth";
			this->textBoxWidth->Size = System::Drawing::Size(100, 20);
			this->textBoxWidth->TabIndex = 4;
			this->textBoxWidth->Text = L"0.001";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(3, 94);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(172, 13);
			this->label6->TabIndex = 3;
			this->label6->Text = L"Расстояние между ступеньками";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(109, 34);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(121, 13);
			this->label5->TabIndex = 2;
			this->label5->Text = L"Ширина ступени (верх)";
			// 
			// textBoxHeight1
			// 
			this->textBoxHeight1->Location = System::Drawing::Point(3, 5);
			this->textBoxHeight1->Name = L"textBoxHeight1";
			this->textBoxHeight1->Size = System::Drawing::Size(100, 20);
			this->textBoxHeight1->TabIndex = 1;
			this->textBoxHeight1->Text = L"0";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(109, 8);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(88, 13);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Высота ступени";
			// 
			// radioButtonRandom
			// 
			this->radioButtonRandom->AutoSize = true;
			this->radioButtonRandom->Location = System::Drawing::Point(716, 25);
			this->radioButtonRandom->Name = L"radioButtonRandom";
			this->radioButtonRandom->Size = System::Drawing::Size(159, 17);
			this->radioButtonRandom->TabIndex = 14;
			this->radioButtonRandom->Tag = L"1";
			this->radioButtonRandom->Text = L"Шероховатая поверхность";
			this->radioButtonRandom->UseVisualStyleBackColor = true;
			this->radioButtonRandom->CheckedChanged += gcnew System::EventHandler(this, &RayParameterWindow::radioButtonRandom_CheckedChanged);
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->label12);
			this->panel2->Controls->Add(this->numericUpDown1);
			this->panel2->Controls->Add(this->textBoxWidth2);
			this->panel2->Controls->Add(this->label9);
			this->panel2->Controls->Add(this->textBoxDepths);
			this->panel2->Controls->Add(this->label8);
			this->panel2->Controls->Add(this->textBoxHeight2);
			this->panel2->Controls->Add(this->label7);
			this->panel2->Enabled = false;
			this->panel2->Location = System::Drawing::Point(696, 52);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(220, 138);
			this->panel2->TabIndex = 15;
			// 
			// textBoxWidth2
			// 
			this->textBoxWidth2->Location = System::Drawing::Point(3, 35);
			this->textBoxWidth2->Name = L"textBoxWidth2";
			this->textBoxWidth2->Size = System::Drawing::Size(100, 20);
			this->textBoxWidth2->TabIndex = 5;
			this->textBoxWidth2->Text = L"0.1";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(121, 42);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(46, 13);
			this->label9->TabIndex = 4;
			this->label9->Text = L"Ширина";
			// 
			// textBoxDepths
			// 
			this->textBoxDepths->Location = System::Drawing::Point(3, 70);
			this->textBoxDepths->Name = L"textBoxDepths";
			this->textBoxDepths->Size = System::Drawing::Size(100, 20);
			this->textBoxDepths->TabIndex = 3;
			this->textBoxDepths->Text = L"0";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(116, 73);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(80, 13);
			this->label8->TabIndex = 2;
			this->label8->Text = L"Макс. глубина";
			// 
			// textBoxHeight2
			// 
			this->textBoxHeight2->Location = System::Drawing::Point(3, 8);
			this->textBoxHeight2->Name = L"textBoxHeight2";
			this->textBoxHeight2->Size = System::Drawing::Size(100, 20);
			this->textBoxHeight2->TabIndex = 1;
			this->textBoxHeight2->Text = L"0";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(120, 12);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(77, 13);
			this->label7->TabIndex = 0;
			this->label7->Text = L"Макс. высота";
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(15, 52);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(86, 17);
			this->checkBox2->TabIndex = 16;
			this->checkBox2->Text = L"узкий пучок";
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &RayParameterWindow::checkBox2_CheckedChanged);
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(3, 110);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {100000, 0, 0, 0});
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(100, 20);
			this->numericUpDown1->TabIndex = 6;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(116, 113);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(98, 13);
			this->label12->TabIndex = 7;
			this->label12->Text = L"число интервалов";
			// 
			// RayParameterWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(924, 257);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->radioButtonRandom);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->radioButtonSteps);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->OKbutton);
			this->Controls->Add(this->textBoxDistance);
			this->Controls->Add(this->textBoxDiameterBundle);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"RayParameterWindow";
			this->Text = L"Параметры пучка";
			this->Load += gcnew System::EventHandler(this, &RayParameterWindow::RayParameterWindow_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDownStepsCount))->EndInit();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void RayParameterWindow_Load(System::Object^  sender, System::EventArgs^  e) {
				 textBoxDiameterBundle->Text=Convert::ToString(width[0]);
				 textBoxDistance->Text=Convert::ToString(height[0]);
				 //textBoxDisplace->Text=Convert::ToString(displace[0]);
				 //textBoxDisplace->Text=Convert::ToString(height[0]);
			 }

	private: System::Void OKbutton_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(checkBox2->Checked==false){
					 switch(comboBox1->SelectedIndex){// выбор размерности
					 case 0:
						 *width=Convert::ToDouble(textBoxDiameterBundle->Text->Replace('.',','));// см
						 break;
					 case 1:
						 *width=Convert::ToDouble(textBoxDiameterBundle->Text->Replace('.',','))/10;// мм 
						 break;
					 case 2:
						 *width=Convert::ToDouble(textBoxDiameterBundle->Text->Replace('.',','))/10000;  // mkm
						 break;
					 case 3:
						 *width=Convert::ToDouble(textBoxDiameterBundle->Text->Replace('.',','))/1.0e+8;// nm
						 break;
					 }
				 }else *width=0.0;
				 switch(comboBox2->SelectedIndex){// выбор размерности
				 case 0:
					 *height=Convert::ToDouble(textBoxDistance->Text->Replace('.',','));// см
					 break;
				 case 1:
					 *height=Convert::ToDouble(textBoxDistance->Text->Replace('.',','))/10;// мм 
					 break;
				 case 2:
					 *height=Convert::ToDouble(textBoxDistance->Text->Replace('.',','))/10000;  // mkm
					 break;
				 case 3:
					 *height=Convert::ToDouble(textBoxDistance->Text->Replace('.',','))/1.0e+8;// nm
					 break;
				 }
				 
				 //delete relief;
				 if(radioButtonSteps->Checked){
					 double h=Convert::ToDouble(textBoxHeight1->Text->Replace('.',','));
					 double w=Convert::ToDouble(textBoxWidth->Text->Replace('.',','));
					 double d=Convert::ToDouble(textBoxPeriod->Text->Replace('.',','));
					 double w2;
					 if(checkBox1->Checked) w2=Convert::ToDouble(textBoxLowWidth->Text->Replace('.',','));
					 else w2=w;
					 Relief2D* r;
					 if(checkBox1->Checked) r=Relief2D::generationSteps(h,w,w2,d,(int)numericUpDownStepsCount->Value);
					 else r=Relief2D::generationSteps(h,w,d,(int)numericUpDownStepsCount->Value);
					 relief->setXY(r->getX(),r->getY(),r->getSize());
				 }else{
					 double h=Convert::ToDouble(textBoxHeight2->Text->Replace('.',','));
					 double w=Convert::ToDouble(textBoxWidth2->Text->Replace('.',','));
					 double d=Convert::ToDouble(textBoxDepths->Text->Replace('.',','));
					 int count=(int)numericUpDown1->Value;
					 relief=Relief2D::generateRandom(d,h,w,count);
				 }
			 }
private: System::Void radioButtonSteps_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 panel1->Enabled=radioButtonSteps->Checked;
		 }
private: System::Void radioButtonRandom_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 panel2->Enabled=radioButtonRandom->Checked;
		 }
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 textBoxLowWidth->Enabled=checkBox1->Checked;
			 label11->Enabled=checkBox1->Checked;
		 }
private: System::Void checkBox2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 textBoxDiameterBundle->Enabled=checkBox2->Checked;
		 }
};
}
