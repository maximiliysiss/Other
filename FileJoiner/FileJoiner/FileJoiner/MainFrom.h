#pragma once
#include "CombineDialog.h"
#include "DivideFile.h"

namespace FileJoiner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;


	/// <summary>
	/// Summary for MainFrom
	/// </summary>
	public ref class MainFrom : public System::Windows::Forms::Form
	{
	public:
		MainFrom(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainFrom()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  addFileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteFileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  combineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  divideToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutProgramToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  abourtProgramToolStripMenuItem;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;

	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::Button^  button7;




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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainFrom::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->addFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->combineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->divideToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutProgramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->abourtProgramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->ForeColor = System::Drawing::Color::Gray;
			this->button1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.Image")));
			this->button1->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->button1->Location = System::Drawing::Point(15, 235);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(55, 55);
			this->button1->TabIndex = 0;
			this->button1->TextAlign = System::Drawing::ContentAlignment::TopLeft;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainFrom::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->Multiselect = true;
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(12, 28);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(237, 199);
			this->listBox1->TabIndex = 1;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolToolStripMenuItem,
					this->aboutProgramToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(326, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// toolToolStripMenuItem
			// 
			this->toolToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->addFileToolStripMenuItem,
					this->deleteFileToolStripMenuItem, this->combineToolStripMenuItem, this->divideToolStripMenuItem
			});
			this->toolToolStripMenuItem->Name = L"toolToolStripMenuItem";
			this->toolToolStripMenuItem->Size = System::Drawing::Size(42, 20);
			this->toolToolStripMenuItem->Text = L"Tool";
			// 
			// addFileToolStripMenuItem
			// 
			this->addFileToolStripMenuItem->Name = L"addFileToolStripMenuItem";
			this->addFileToolStripMenuItem->Size = System::Drawing::Size(126, 22);
			this->addFileToolStripMenuItem->Text = L"Add file";
			this->addFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainFrom::addFileToolStripMenuItem_Click);
			// 
			// deleteFileToolStripMenuItem
			// 
			this->deleteFileToolStripMenuItem->Name = L"deleteFileToolStripMenuItem";
			this->deleteFileToolStripMenuItem->Size = System::Drawing::Size(126, 22);
			this->deleteFileToolStripMenuItem->Text = L"Delete file";
			this->deleteFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainFrom::deleteFileToolStripMenuItem_Click);
			// 
			// combineToolStripMenuItem
			// 
			this->combineToolStripMenuItem->Name = L"combineToolStripMenuItem";
			this->combineToolStripMenuItem->Size = System::Drawing::Size(126, 22);
			this->combineToolStripMenuItem->Text = L"Combine";
			this->combineToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainFrom::combineToolStripMenuItem_Click);
			// 
			// divideToolStripMenuItem
			// 
			this->divideToolStripMenuItem->Name = L"divideToolStripMenuItem";
			this->divideToolStripMenuItem->Size = System::Drawing::Size(126, 22);
			this->divideToolStripMenuItem->Text = L"Divide";
			this->divideToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainFrom::divideToolStripMenuItem_Click);
			// 
			// aboutProgramToolStripMenuItem
			// 
			this->aboutProgramToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->abourtProgramToolStripMenuItem });
			this->aboutProgramToolStripMenuItem->Name = L"aboutProgramToolStripMenuItem";
			this->aboutProgramToolStripMenuItem->Size = System::Drawing::Size(52, 20);
			this->aboutProgramToolStripMenuItem->Text = L"About";
			// 
			// abourtProgramToolStripMenuItem
			// 
			this->abourtProgramToolStripMenuItem->Name = L"abourtProgramToolStripMenuItem";
			this->abourtProgramToolStripMenuItem->Size = System::Drawing::Size(160, 22);
			this->abourtProgramToolStripMenuItem->Text = L"Abourt program";
			this->abourtProgramToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainFrom::abourtProgramToolStripMenuItem_Click);
			// 
			// button2
			// 
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->ForeColor = System::Drawing::Color::Gray;
			this->button2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.Image")));
			this->button2->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->button2->Location = System::Drawing::Point(78, 235);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(55, 55);
			this->button2->TabIndex = 3;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainFrom::button2_Click);
			// 
			// button3
			// 
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->ForeColor = System::Drawing::Color::Gray;
			this->button3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.Image")));
			this->button3->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->button3->Location = System::Drawing::Point(141, 235);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(70, 55);
			this->button3->TabIndex = 4;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainFrom::button3_Click);
			// 
			// button4
			// 
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->ForeColor = System::Drawing::Color::Gray;
			this->button4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button4.Image")));
			this->button4->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->button4->Location = System::Drawing::Point(219, 235);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(70, 55);
			this->button4->TabIndex = 5;
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainFrom::button4_Click);
			// 
			// button6
			// 
			this->button6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->ForeColor = System::Drawing::Color::Gray;
			this->button6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button6.Image")));
			this->button6->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->button6->Location = System::Drawing::Point(255, 70);
			this->button6->Name = L"button6";
			this->button6->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->button6->Size = System::Drawing::Size(55, 55);
			this->button6->TabIndex = 7;
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MainFrom::button6_Click);
			// 
			// button7
			// 
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->ForeColor = System::Drawing::Color::Gray;
			this->button7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button7.Image")));
			this->button7->ImageAlign = System::Drawing::ContentAlignment::TopLeft;
			this->button7->Location = System::Drawing::Point(255, 128);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(55, 55);
			this->button7->TabIndex = 8;
			this->button7->TextAlign = System::Drawing::ContentAlignment::TopLeft;
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MainFrom::button7_Click);
			// 
			// MainFrom
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(326, 302);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"MainFrom";
			this->Text = L"File Joiner";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		addFileToolStripMenuItem_Click(sender, e);
	}
	private: System::Void addFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			for each(String^ file in openFileDialog1->FileNames)
				listBox1->Items->Add(file);
	}
	private: System::Void deleteFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if (listBox1->SelectedIndex != -1)listBox1->Items->RemoveAt(listBox1->SelectedIndex);
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		deleteFileToolStripMenuItem_Click(sender, e);
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		CombineDialog one(listBox1);
		one.ShowDialog();
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		DivideFile one;
		one.ShowDialog();
	}
private: System::Void combineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	button3_Click(sender, e);
}
private: System::Void divideToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	button4_Click(sender, e);
}
private: System::Void abourtProgramToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show("Creator & Programmer - ZiMA\nDesigner - Kate\n","About authors");
}
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
	if (listBox1->SelectedIndex != -1 && listBox1->SelectedIndex != 0)
	{
		Object^ temp = listBox1->Items[listBox1->SelectedIndex];
		listBox1->Items[listBox1->SelectedIndex] = listBox1->Items[listBox1->SelectedIndex - 1];
		listBox1->Items[listBox1->SelectedIndex - 1] = temp;
		listBox1->SelectedIndex = listBox1->SelectedIndex - 1;
	}
}
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
	if (listBox1->SelectedIndex != -1 && listBox1->SelectedIndex != listBox1->Items->Count - 1)
	{
		Object^ temp = listBox1->Items[listBox1->SelectedIndex];
		listBox1->Items[listBox1->SelectedIndex] = listBox1->Items[listBox1->SelectedIndex + 1];
		listBox1->Items[listBox1->SelectedIndex + 1] = temp;
		listBox1->SelectedIndex = listBox1->SelectedIndex + 1;
	}
}
};
};
