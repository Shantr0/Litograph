#pragma once
#include "Detector.h"

namespace Litography {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

	/// <summary>
	/// Summary for DetectorWindow
	/// </summary>
	public ref class DetectorWindow : public System::Windows::Forms::Form
	{
		Detector* detectors;
		static const double pi180=Math::PI/180;
		int* detectorsCount;
	private: System::Windows::Forms::CheckBox^  checkBoxDetector1;
	private: System::Windows::Forms::CheckBox^  checkBoxDetector2;
	private: System::Windows::Forms::CheckBox^  checkBoxDetector3;
			 
	public:
		DetectorWindow(Detector* detectors,int* n)
		{
			InitializeComponent();
			this->detectors=detectors;
			detectorsCount=n;
			cli::array<CheckBox^>^ cb={checkBoxDetector1,checkBoxDetector2,checkBoxDetector3};
			cli::array<TextBox^>^ tbX={textBoxX1,textBoxX2,textBoxX3};
			cli::array<TextBox^>^ tbY={textBoxY1,textBoxY2,textBoxY3};
			cli::array<TextBox^>^ tbAngle={textBoxAngle1,textBoxAngle2,textBoxAngle3};
			cli::array<TextBox^>^ tbSize={textBoxWidth1,textBoxWidth2,textBoxWidth3};
			for(int i=0;i<(*n);i++){
				tbX[i]->Text=Convert::ToString(detectors[i].x);
				tbY[i]->Text=Convert::ToString(detectors[i].y);
				tbAngle[i]->Text=Convert::ToString(detectors[i].angle/pi180);
				tbSize[i]->Text=Convert::ToString(detectors[i].getSize());
				cb[i]->Checked=detectors[i].isActive();
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DetectorWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 


	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBoxX1;
	private: System::Windows::Forms::TextBox^  textBoxY1;
	private: System::Windows::Forms::TextBox^  textBoxWidth1;


	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBoxAngle1;

	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBoxAngle2;


	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  textBoxWidth2;

	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  textBoxY2;

	private: System::Windows::Forms::TextBox^  textBoxX2;

	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;

	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::TextBox^  textBoxAngle3;


	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::TextBox^  textBoxX3;
	private: System::Windows::Forms::TextBox^  textBoxY3;


	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  textBoxWidth3;

	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Button^  buttonOK;
	private: System::Windows::Forms::Button^  buttonCancel;

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
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBoxX1 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxY1 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxWidth1 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBoxAngle1 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBoxAngle2 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBoxWidth2 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBoxY2 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxX2 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->checkBoxDetector1 = (gcnew System::Windows::Forms::CheckBox());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->checkBoxDetector2 = (gcnew System::Windows::Forms::CheckBox());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->textBoxAngle3 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->textBoxX3 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxY3 = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->textBoxWidth3 = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->checkBoxDetector3 = (gcnew System::Windows::Forms::CheckBox());
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 54);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(74, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"координата у";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(9, 8);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(74, 13);
			this->label4->TabIndex = 4;
			this->label4->Text = L"координата х";
			// 
			// textBoxX1
			// 
			this->textBoxX1->Location = System::Drawing::Point(9, 24);
			this->textBoxX1->Name = L"textBoxX1";
			this->textBoxX1->Size = System::Drawing::Size(87, 20);
			this->textBoxX1->TabIndex = 5;
			this->textBoxX1->Text = L"0.0";
			// 
			// textBoxY1
			// 
			this->textBoxY1->Location = System::Drawing::Point(12, 70);
			this->textBoxY1->Name = L"textBoxY1";
			this->textBoxY1->Size = System::Drawing::Size(87, 20);
			this->textBoxY1->TabIndex = 6;
			this->textBoxY1->Text = L"1";
			// 
			// textBoxWidth1
			// 
			this->textBoxWidth1->Location = System::Drawing::Point(12, 116);
			this->textBoxWidth1->Name = L"textBoxWidth1";
			this->textBoxWidth1->Size = System::Drawing::Size(87, 20);
			this->textBoxWidth1->TabIndex = 8;
			this->textBoxWidth1->Text = L"0.5";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(9, 100);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(69, 13);
			this->label5->TabIndex = 7;
			this->label5->Text = L"–азмер (см)";
			// 
			// textBoxAngle1
			// 
			this->textBoxAngle1->Location = System::Drawing::Point(12, 161);
			this->textBoxAngle1->Name = L"textBoxAngle1";
			this->textBoxAngle1->Size = System::Drawing::Size(87, 20);
			this->textBoxAngle1->TabIndex = 10;
			this->textBoxAngle1->Text = L"0";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(9, 145);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(83, 13);
			this->label6->TabIndex = 9;
			this->label6->Text = L"поворот (град.)";
			// 
			// textBoxAngle2
			// 
			this->textBoxAngle2->Location = System::Drawing::Point(21, 161);
			this->textBoxAngle2->Name = L"textBoxAngle2";
			this->textBoxAngle2->Size = System::Drawing::Size(87, 20);
			this->textBoxAngle2->TabIndex = 19;
			this->textBoxAngle2->Text = L"45";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(18, 145);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(83, 13);
			this->label7->TabIndex = 18;
			this->label7->Text = L"поворот (град.)";
			// 
			// textBoxWidth2
			// 
			this->textBoxWidth2->Location = System::Drawing::Point(21, 116);
			this->textBoxWidth2->Name = L"textBoxWidth2";
			this->textBoxWidth2->Size = System::Drawing::Size(87, 20);
			this->textBoxWidth2->TabIndex = 17;
			this->textBoxWidth2->Text = L"0.5";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(18, 100);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(69, 13);
			this->label8->TabIndex = 16;
			this->label8->Text = L"–азмер (см)";
			// 
			// textBoxY2
			// 
			this->textBoxY2->Location = System::Drawing::Point(21, 70);
			this->textBoxY2->Name = L"textBoxY2";
			this->textBoxY2->Size = System::Drawing::Size(87, 20);
			this->textBoxY2->TabIndex = 15;
			this->textBoxY2->Text = L"1";
			// 
			// textBoxX2
			// 
			this->textBoxX2->Location = System::Drawing::Point(18, 24);
			this->textBoxX2->Name = L"textBoxX2";
			this->textBoxX2->Size = System::Drawing::Size(87, 20);
			this->textBoxX2->TabIndex = 14;
			this->textBoxX2->Text = L"-0.1";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(18, 8);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(74, 13);
			this->label9->TabIndex = 13;
			this->label9->Text = L"координата х";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(18, 54);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(74, 13);
			this->label10->TabIndex = 12;
			this->label10->Text = L"координата у";
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->textBoxAngle1);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->textBoxX1);
			this->panel1->Controls->Add(this->textBoxY1);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->textBoxWidth1);
			this->panel1->Controls->Add(this->label6);
			this->panel1->Enabled = false;
			this->panel1->Location = System::Drawing::Point(12, 48);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(114, 190);
			this->panel1->TabIndex = 29;
			// 
			// checkBoxDetector1
			// 
			this->checkBoxDetector1->AutoSize = true;
			this->checkBoxDetector1->Location = System::Drawing::Point(24, 20);
			this->checkBoxDetector1->Name = L"checkBoxDetector1";
			this->checkBoxDetector1->Size = System::Drawing::Size(81, 17);
			this->checkBoxDetector1->TabIndex = 34;
			this->checkBoxDetector1->Text = L"детектор 1";
			this->checkBoxDetector1->UseVisualStyleBackColor = true;
			this->checkBoxDetector1->CheckedChanged += gcnew System::EventHandler(this, &DetectorWindow::checkBoxDetector1_CheckedChanged);
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->textBoxAngle2);
			this->panel2->Controls->Add(this->label10);
			this->panel2->Controls->Add(this->label9);
			this->panel2->Controls->Add(this->textBoxX2);
			this->panel2->Controls->Add(this->textBoxY2);
			this->panel2->Controls->Add(this->label8);
			this->panel2->Controls->Add(this->textBoxWidth2);
			this->panel2->Controls->Add(this->label7);
			this->panel2->Enabled = false;
			this->panel2->Location = System::Drawing::Point(141, 48);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(131, 190);
			this->panel2->TabIndex = 30;
			// 
			// checkBoxDetector2
			// 
			this->checkBoxDetector2->AutoSize = true;
			this->checkBoxDetector2->Location = System::Drawing::Point(151, 20);
			this->checkBoxDetector2->Name = L"checkBoxDetector2";
			this->checkBoxDetector2->Size = System::Drawing::Size(81, 17);
			this->checkBoxDetector2->TabIndex = 34;
			this->checkBoxDetector2->Text = L"детектор 2";
			this->checkBoxDetector2->UseVisualStyleBackColor = true;
			this->checkBoxDetector2->CheckedChanged += gcnew System::EventHandler(this, &DetectorWindow::checkBoxDetector2_CheckedChanged);
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->textBoxAngle3);
			this->panel3->Controls->Add(this->label13);
			this->panel3->Controls->Add(this->label14);
			this->panel3->Controls->Add(this->textBoxX3);
			this->panel3->Controls->Add(this->textBoxY3);
			this->panel3->Controls->Add(this->label15);
			this->panel3->Controls->Add(this->textBoxWidth3);
			this->panel3->Controls->Add(this->label16);
			this->panel3->Enabled = false;
			this->panel3->Location = System::Drawing::Point(283, 48);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(121, 190);
			this->panel3->TabIndex = 31;
			// 
			// textBoxAngle3
			// 
			this->textBoxAngle3->Location = System::Drawing::Point(21, 161);
			this->textBoxAngle3->Name = L"textBoxAngle3";
			this->textBoxAngle3->Size = System::Drawing::Size(87, 20);
			this->textBoxAngle3->TabIndex = 19;
			this->textBoxAngle3->Text = L"-45";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(18, 54);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(74, 13);
			this->label13->TabIndex = 12;
			this->label13->Text = L"координата у";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(18, 8);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(74, 13);
			this->label14->TabIndex = 13;
			this->label14->Text = L"координата х";
			// 
			// textBoxX3
			// 
			this->textBoxX3->Location = System::Drawing::Point(18, 24);
			this->textBoxX3->Name = L"textBoxX3";
			this->textBoxX3->Size = System::Drawing::Size(87, 20);
			this->textBoxX3->TabIndex = 14;
			this->textBoxX3->Text = L"0.1";
			// 
			// textBoxY3
			// 
			this->textBoxY3->Location = System::Drawing::Point(21, 70);
			this->textBoxY3->Name = L"textBoxY3";
			this->textBoxY3->Size = System::Drawing::Size(87, 20);
			this->textBoxY3->TabIndex = 15;
			this->textBoxY3->Text = L"1";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(18, 100);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(69, 13);
			this->label15->TabIndex = 16;
			this->label15->Text = L"–азмер (см)";
			// 
			// textBoxWidth3
			// 
			this->textBoxWidth3->Location = System::Drawing::Point(21, 116);
			this->textBoxWidth3->Name = L"textBoxWidth3";
			this->textBoxWidth3->Size = System::Drawing::Size(87, 20);
			this->textBoxWidth3->TabIndex = 17;
			this->textBoxWidth3->Text = L"0.5";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(18, 145);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(83, 13);
			this->label16->TabIndex = 18;
			this->label16->Text = L"поворот (град.)";
			// 
			// checkBoxDetector3
			// 
			this->checkBoxDetector3->AutoSize = true;
			this->checkBoxDetector3->Location = System::Drawing::Point(306, 20);
			this->checkBoxDetector3->Name = L"checkBoxDetector3";
			this->checkBoxDetector3->Size = System::Drawing::Size(81, 17);
			this->checkBoxDetector3->TabIndex = 35;
			this->checkBoxDetector3->Text = L"детектор 3";
			this->checkBoxDetector3->UseVisualStyleBackColor = true;
			this->checkBoxDetector3->CheckedChanged += gcnew System::EventHandler(this, &DetectorWindow::checkBoxDetector3_CheckedChanged);
			// 
			// buttonOK
			// 
			this->buttonOK->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->buttonOK->Location = System::Drawing::Point(409, 186);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(94, 23);
			this->buttonOK->TabIndex = 32;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &DetectorWindow::buttonOK_Click);
			// 
			// buttonCancel
			// 
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->Location = System::Drawing::Point(409, 215);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(94, 23);
			this->buttonCancel->TabIndex = 33;
			this->buttonCancel->Text = L"ќтмена";
			this->buttonCancel->UseVisualStyleBackColor = true;
			// 
			// DetectorWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(515, 249);
			this->Controls->Add(this->checkBoxDetector3);
			this->Controls->Add(this->checkBoxDetector1);
			this->Controls->Add(this->checkBoxDetector2);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->buttonOK);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Name = L"DetectorWindow";
			this->Text = L"DetectorWindow";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonOK_Click(System::Object^  sender, System::EventArgs^  e) {
				 
				 if(panel1->Enabled){
					 detectors[0].x=Convert::ToDouble(textBoxX1->Text->Replace('.',','));
					 detectors[0].y=Convert::ToDouble(textBoxY1->Text->Replace('.',','));
					 detectors[0].angle=pi180*Convert::ToDouble(textBoxAngle1->Text->Replace('.',','));
					 detectors[0].setSize(Convert::ToDouble(textBoxWidth1->Text->Replace('.',',')));
				 };
				 detectors[0].setActive(panel1->Enabled);
				 if(panel2->Enabled){
					 detectors[1].x=Convert::ToDouble(textBoxX2->Text->Replace('.',','));
					 detectors[1].y=Convert::ToDouble(textBoxY2->Text->Replace('.',','));
					 detectors[1].angle=pi180*Convert::ToDouble(textBoxAngle2->Text->Replace('.',','));
					 detectors[1].setSize(Convert::ToDouble(textBoxWidth2->Text->Replace('.',',')));
				 }
				 detectors[1].setActive(panel2->Enabled);
				 if(panel3->Enabled){
					 detectors[2].x=Convert::ToDouble(textBoxX3->Text->Replace('.',','));
					 detectors[2].y=Convert::ToDouble(textBoxY3->Text->Replace('.',','));
					 detectors[2].angle=pi180*Convert::ToDouble(textBoxAngle3->Text->Replace('.',','));
					 detectors[2].setSize(Convert::ToDouble(textBoxWidth3->Text->Replace('.',',')));
				 }
				 detectors[2].setActive(panel3->Enabled);
			 }
//private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
//			 *count=1;
//			 switch(*count){
//			 case 0:
//				 panel1->Enabled=false;
//				 panel2->Enabled=false;
//				 panel3->Enabled=false;
//				 break;
//			 case 1:
//				 panel1->Enabled=true;
//				 panel2->Enabled=false;
//				 panel3->Enabled=false;
//				 break;
//			 case 2:
//				 panel1->Enabled=true;
//				 panel2->Enabled=true;
//				 panel3->Enabled=false;
//				 break;
//			 case 3:
//				 panel1->Enabled=true;
//				 panel2->Enabled=true;
//				 panel3->Enabled=true;
//				 break;
//			 }
//			 
//		 }
private: System::Void checkBoxDetector1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 panel1->Enabled=checkBoxDetector1->Checked;
			 detectors[0].setActive(checkBoxDetector1->Checked);
			 //if(checkBoxDetector1->Checked) detectorsCount++;
			 //else detectorsCount--;
		 }
private: System::Void checkBoxDetector2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 panel2->Enabled=checkBoxDetector2->Checked;
			 detectors[1].setActive(checkBoxDetector2->Checked);
			 //if(checkBoxDetector2->Checked) detectorsCount++;
			 //else detectorsCount--;
		 }
private: System::Void checkBoxDetector3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 panel3->Enabled=checkBoxDetector3->Checked;
			 detectors[2].setActive(checkBoxDetector3->Checked);
			 //if(checkBoxDetector3->Checked) detectorsCount++;
			 //else detectorsCount--;
		 }
};
}
