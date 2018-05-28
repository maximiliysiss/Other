#pragma once
#include "Objects.h"

class DataBase
{
private:
	std::vector<Student> SaveRAM; // RAM сохранение студентов
	std::string FileName; // Имя подключенного файла
	bool inScreen; // Работа в фоне (RAM)
	bool bSaveRAM; // Сохранять ли в RAM
	std::fstream FileStream; // Файловый поток
	// Открыть файл для работы + не забыть закрыть
	void OpenForFileStream(std::string path, unsigned int Mode); 
	// Считать все записи в ОЗУ
	std::vector<Student> ReadAllRecords();
	// Считать в таблицу из ОЗУ
	void LoadFromRAM(HWND hListView);
	// Считать из файла
	void EasyForRamReadToList(HWND hListView);
	// Поиск в памяти
	std::vector<Student> FindInRAM(const std::string key);
	// Поиск в файле
	std::vector<Student> FindInFile(const std::string key);
public:
	// Получить путь файла с именем
	inline std::string GetFilePath()
	{
		return FileName;
	}
	// Поиск элемента
	std::vector<Student> FindEl(std::string key);
	// Загрузить в лист из ОЗУ 
	void LoadToListViewFromRAM(HWND hListView);
	// Добавить студента в лист по индексу
	void AddToHWNDLIST(Student a_st, HWND hListView, int index = -1);
	//Загрузить из файла
	void LoadFromFile(HWND hListView)
	{
		this->EasyForRamReadToList(hListView);
	}
	// Констурктор от пути и требования загрузки в ОЗУ
	DataBase(std::string path, bool RAM) :FileName(path)
	{
		bSaveRAM = RAM;
		inScreen = false;
		this->OpenForFileStream(FileName, std::ios_base::in | std::ios_base::binary);
		this->FileStream.close();
		if (bSaveRAM)
			SaveRAM = this->ReadAllRecords();
	}
	// Конструктор заивисимости от хранения в ОЗУ
	DataBase(bool RAM)
	{
		inScreen = false;
		bSaveRAM = RAM;
		FileName = "DB.fileDB"; this->OpenForFileStream(FileName, std::ios_base::in | std::ios_base::binary);
		this->FileStream.close();
		if (bSaveRAM)
			SaveRAM = this->ReadAllRecords();
	}
	DataBase() // Дефолт конструктор
	{
		inScreen = false;
		bSaveRAM = false;
		FileName = "DB.fileDB";
		this->OpenForFileStream(FileName, std::ios_base::in | std::ios_base::binary);
		this->FileStream.close();
	}
	DataBase(std::string path) :FileName(path) // Конструктор зависимости от пути
	{
		inScreen = false;
		bSaveRAM = false;
		this->OpenForFileStream(FileName, std::ios_base::in | std::ios_base::binary);
		this->FileStream.close();
	}
	DataBase(DataBase & DB) // Конструктор копирования
	{
		inScreen = false;
		bSaveRAM = DB.bSaveRAM;
		this->FileName = DB.FileName;
		this->OpenForFileStream(FileName, std::ios_base::in | std::ios_base::binary);
		this->FileStream.close();
	}
	DataBase(std::string path, bool RAM, bool Screen) // Конструктор зависимости от пути, хранение и работы в фоне
	{
		inScreen = Screen;
		if (!inScreen)
		{
			this->OpenForFileStream(FileName, std::ios_base::in | std::ios_base::binary);
			this->FileStream.close();
			if (RAM)
				SaveRAM = this->ReadAllRecords();
		}
	}
	// Добавить запись
	void AddRecord(Student s);
	// Вернуть работает ли в inScreen
	inline bool SavingQ()
	{
		return inScreen;
	}
	// Сохранить
	void SavingDB(std::string path);
	// Удалить запись
	void DeleteRecord(Student st_d);
};