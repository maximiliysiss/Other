#pragma once
#include <msclr\marshal_cppstd.h>
#include <ctime>

namespace FileJoiner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;


	/// <summary>
	/// Summary for DivideFile
	/// </summary>
	public ref class DivideFile : public System::Windows::Forms::Form
	{
	public:
		DivideFile(void)
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
		~DivideFile()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;

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
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(45, 27);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Divide";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &DivideFile::button1_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// DivideFile
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(164, 62);
			this->Controls->Add(this->button1);
			this->Name = L"DivideFile";
			this->Text = L"Divide";
			this->ResumeLayout(false);

		}
#pragma endregion
		String^ getName(int i)
		{
			srand((unsigned int)time(0));
			String^ s = "";
			for (int i = 0; i < 20; i++)
				s += rand() % 24 + 97;
			return s + i.ToString();
		}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ path;
		String^ fExe;
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && openFileDialog1->FileName != ""
			&& openFileDialog1->FileName != " ")
			path = openFileDialog1->FileName;
		else
		{
			this->DestroyHandle();
			this->Close();
			return;
		}
		FileStream^ FIn = File::OpenRead(path);
		String^ m_main = path;
		BinaryReader ^ file = gcnew BinaryReader(FIn);
		array<Byte>^ block = gcnew array<Byte>(1);
		int count = file->ReadInt32();
		array<String^>^ list1 = gcnew array<String^>(count) {""};
		for (int i = 0; i < count; i++)
		{
			wchar_t c = file->ReadChar();
			while (c!='/')
			{
				list1[i] += c;
				c = file->ReadChar();
			}
		}
		wchar_t c = file->ReadChar();
		wchar_t add = file->ReadChar();
		for (int i = 0; i < count; i++)
		{
			if (add == '0')
			{
				saveFileDialog1->Filter = "File " + list1[i] + "|*." + list1[i];
				if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && saveFileDialog1->FileName != "")
				{
					path = saveFileDialog1->FileName;
					if (i == 0)
						fExe = path;
				}
				else
					continue;
			}
			else
			{
				path = System::IO::Path::GetFullPath(m_main) + getName(i) + "." + list1[i];
				if (i == 0)
					fExe = path;
			}
			unsigned int size = file->ReadInt32();
			FileStream^ fileOut = File::OpenWrite(path);
			while (size != 0)
			{
				FIn->Read(block, 0, 1);
				fileOut->Write(block, 0, 1);
				size--;
			}
			fileOut->Close();
		}
		if (add != '0')System::Diagnostics::Process::Start(fExe);
		FIn->Close();
		file->Close();
		this->DestroyHandle();
		this->Close();
	}
	};
}
