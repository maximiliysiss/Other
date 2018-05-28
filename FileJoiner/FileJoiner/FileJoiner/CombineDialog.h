#pragma once
#include <ctime>
#include <string>
#include <Windows.h>

namespace FileJoiner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for CombineDialog
	/// </summary>
	public ref class CombineDialog : public System::Windows::Forms::Form
	{
	public:
		CombineDialog(System::Windows::Forms::ListBox^ listBox):listBox1(listBox)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~CombineDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::ListBox^  listBox1;

	private: System::Windows::Forms::ProgressBar^  progressBar1;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	protected:

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(58, 39);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Merge";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &CombineDialog::button1_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->progressBar1->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->progressBar1->Location = System::Drawing::Point(0, 68);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(180, 23);
			this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->progressBar1->TabIndex = 2;
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Asked about filepath", L"Execute first file in list" });
			this->comboBox2->Location = System::Drawing::Point(12, 12);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(121, 21);
			this->comboBox2->TabIndex = 3;
			this->comboBox2->Text = L"Asked about filepath";
			// 
			// CombineDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(180, 91);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->button1);
			this->Name = L"CombineDialog";
			this->Text = L"Merge settings";
			this->ResumeLayout(false);

		}
#pragma endregion

		void encode_ceaser(array<Byte>^temp, int k)
		{
			for (int i = 0; i < temp->Length; i++)
				temp[i] + k > 255 ? temp[i] = temp[i] - 255 + k : temp[i] += k;
		}

		array<Byte>^ getRash(String ^ s)
		{
			String^ ra = "";
			String^ dot = ".";
			for (int i = s->Length-1; s[i]!=dot[0]; i--)
				ra += s[i];
			array<Byte>^ r = gcnew array<Byte>(ra->Length);
			for (int i = 0; i < ra->Length; i++)
				r[i] = (char)ra[ra->Length - i - 1];
			return r;
		}

		unsigned int ghash(String^ path)
		{
			FileStream^ f = File::OpenRead(path);
			unsigned int hash = 0;
			array<Byte>^ block = gcnew array<Byte>(1);
			while (f->Read(block, 0, block->Length) > 0)
				hash++;
			f->Close();
			return hash;
		}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		if (listBox1->Items->Count == 0)
		{
			MessageBox::Show("Not found files","Error");
			this->Close();
			return;
		}
		String^ path;
		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && saveFileDialog1->FileName != "")
			path = saveFileDialog1->FileName;
		else 
		{
			this->Close();
			this->DestroyHandle();
			return;
		}
		FileStream^ FOut = File::OpenWrite(path);
		BinaryWriter^ file = gcnew BinaryWriter(FOut);
		array<Byte>^ block = gcnew array<Byte>(1);
		char* buffer=new char[MAX_PATH];
		path = "";
		ZeroMemory(buffer, MAX_PATH);
		GetModuleFileName(NULL, (LPWSTR)buffer, 256);
		for (int i = 0; i < 256; i++)
			if (buffer[i])path += (wchar_t)buffer[i];
		delete buffer;
		FileStream^ FIn1 = File::OpenRead(path);
		int j = 0;
		while (j != 185344)
		{
			FIn1->Read(block, 0, 1);
			j++;
		}
		while (FIn1->Read(block, 0, 1))
			FOut->Write(block, 0, 1);
		FIn1->Close();
		int min = 0;
		int dm = 100 % listBox1->Items->Count;
		file->Write(listBox1->Items->Count);
		for (int i = 0; i < listBox1->Items->Count;i++)
		{
			array<Byte>^ t = getRash((String^)listBox1->Items[i]);
			FOut->Write(t, 0, t->Length);
			file->Write((Byte)'/');
		}
			file->Write((Byte)'0');
			if (comboBox2->SelectedIndex == 0 || comboBox2->SelectedIndex == -1)
				file->Write((Byte)'0');
			else
				file->Write((Byte)'1');
			for (int i = 0; i < listBox1->Items->Count; i++)
			{
				unsigned int hash = ghash((String^)listBox1->Items[i]);
				FileStream^ FIn = File::OpenRead((String^)listBox1->Items[i]);
				file->Write(hash);
				while (FIn->Read(block, 0, 1))
					FOut->Write(block, 0, 1);
				FIn->Close();
				progressBar1->Value += dm;
			}
		FOut->Close();
		file->Close();
		MessageBox::Show("Success", "Success");
		this->DestroyHandle();
		this->Close();
	}
	};
}
