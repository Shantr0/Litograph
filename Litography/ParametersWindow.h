#pragma once
#include "SampleParameters.h"
namespace Litography {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ParametersWindow
	/// </summary>
	public ref class ParametersWindow : public System::Windows::Forms::Form
	{
		SampleParameters* param;
	public:
		ParametersWindow(SampleParameters* param)
		{
			InitializeComponent();
			initialize(param);
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ParametersWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
	protected: 
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridView^  dataGridViewParameters;
	private: System::Windows::Forms::Button^  buttonCancel;
	private: System::Windows::Forms::Button^  buttonAccept;

	protected: 
		void initialize(SampleParameters* param){
			this->param=param;
			dataGridViewParameters->Rows->Add("порядковый номер",param->getZNumber());
			//dataGridViewParameters->Rows->Add("число лучей",param->getRaysCount());
			dataGridViewParameters->Rows->Add("атомная масса, а.е.м.",param->getMass());
			dataGridViewParameters->Rows->Add("плотность, г/см^3",param->getDensity());
		}


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
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewParameters = (gcnew System::Windows::Forms::DataGridView());
			this->buttonCancel = (gcnew System::Windows::Forms::Button());
			this->buttonAccept = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridViewParameters))->BeginInit();
			this->SuspendLayout();
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"значение";
			this->Column2->Name = L"Column2";
			this->Column2->Width = 200;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Параметр";
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->Width = 200;
			// 
			// dataGridViewParameters
			// 
			this->dataGridViewParameters->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridViewParameters->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->Column1, 
				this->Column2});
			this->dataGridViewParameters->Location = System::Drawing::Point(12, 12);
			this->dataGridViewParameters->Name = L"dataGridViewParameters";
			this->dataGridViewParameters->Size = System::Drawing::Size(445, 212);
			this->dataGridViewParameters->TabIndex = 1;
			// 
			// buttonCancel
			// 
			this->buttonCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->buttonCancel->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->buttonCancel->Location = System::Drawing::Point(385, 230);
			this->buttonCancel->Name = L"buttonCancel";
			this->buttonCancel->Size = System::Drawing::Size(72, 24);
			this->buttonCancel->TabIndex = 15;
			this->buttonCancel->Text = L"Отмена";
			this->buttonCancel->UseVisualStyleBackColor = true;
			// 
			// buttonAccept
			// 
			this->buttonAccept->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->buttonAccept->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->buttonAccept->Location = System::Drawing::Point(12, 230);
			this->buttonAccept->Name = L"buttonAccept";
			this->buttonAccept->Size = System::Drawing::Size(72, 24);
			this->buttonAccept->TabIndex = 16;
			this->buttonAccept->Text = L"ОК";
			this->buttonAccept->UseVisualStyleBackColor = true;
			this->buttonAccept->Click += gcnew System::EventHandler(this, &ParametersWindow::buttonAccept_Click);
			// 
			// ParametersWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(462, 262);
			this->Controls->Add(this->buttonAccept);
			this->Controls->Add(this->buttonCancel);
			this->Controls->Add(this->dataGridViewParameters);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"ParametersWindow";
			this->Text = L"ParametersWindow";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridViewParameters))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void buttonAccept_Click(System::Object^  sender, System::EventArgs^  e) {
				 param->setZNumber(Convert::ToInt32(dataGridViewParameters->Rows[0]->Cells[1]->Value));
				 //param->setRaysCount(Convert::ToInt64(dataGridViewParameters->Rows[1]->Cells[1]->Value));
				 param->setMass(Convert::ToDouble(dataGridViewParameters->Rows[1]->Cells[1]->Value));
				 param->setDensity(Convert::ToDouble(dataGridViewParameters->Rows[2]->Cells[1]->Value));
			 }
};
}
