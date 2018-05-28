#include "DataBase.h"

// Открыть документ 
void DataBase::OpenForFileStream(std::string path, unsigned int Mode) 
{
	this->FileStream.open(path, Mode); // Открыть с модом
	if (!this->FileStream.is_open()) // Если не открыт, то создать
		this->FileStream.open(path, Mode | std::ios_base::out);
}

// Считать данные в ОЗУ
std::vector<Student> DataBase::ReadAllRecords()
{
	std::vector<Student> vec_result; // Результат
	this->OpenForFileStream(FileName, std::ios_base::binary | std::ios_base::in); // Открытие
	Student st;
	while (true)
	{
		this->FileStream.read((char*)&st, sizeof(Student)); // Считывание
		if (FileStream.eof()) // Если файл закончился
			break;
		vec_result.push_back(st); // Добавление в вектор
	}
	this->FileStream.close(); // Закрытие файлового потока
	return vec_result;
}

void DataBase::LoadToListViewFromRAM(HWND hListView) // Загрузить  в лист
{
	if (SaveRAM.size() > 0) // Если данные в ОЗУ, то оттуда
		this->LoadFromRAM(hListView);
	else
		if (!inScreen) // Если не вФоне, то из файла
			this->EasyForRamReadToList(hListView);
}

void DataBase::LoadFromRAM(HWND hListView) // Загрузить из памяти
{
	for (UINT i = 0; i < SaveRAM.size(); i++)
		this->AddToHWNDLIST(SaveRAM[i], hListView, i);
}

void DataBase::EasyForRamReadToList(HWND hListView) // Загрузить из файла
{
	int row = 0; // индекс
	this->OpenForFileStream(FileName, std::ios_base::binary | std::ios_base::in);
	Student st;
	while (true)
	{
		this->FileStream.read((char*)&st, sizeof(Student));
		if (this->FileStream.eof())
			break;
		row++;
		this->AddToHWNDLIST(st, hListView, row);
	}
	this->FileStream.close();
}

std::vector<Student> DataBase::FindInRAM(const std::string key) // Поиск в памяти
{
	std::vector<Student> result; // Результат
	for (UINT i = 0; i < SaveRAM.size(); i++)
		if (SaveRAM[i] == key) // Сравнение с ключом
			result.push_back(SaveRAM[i]);
	return result;
}

std::vector<Student> DataBase::FindInFile(const std::string key) // Поиск в файле
{
	std::vector<Student> result; // Результат
	this->OpenForFileStream(FileName, std::ios_base::binary | std::ios_base::in);
	Student st;
	while (true)
	{
		this->FileStream.read((char*)&st, sizeof(Student));
		if (this->FileStream.eof())
			break;
		if (st == key) // Сранвние с ключом
			result.push_back(st);
	}
	this->FileStream.close();
	return result;
}

std::vector<Student> DataBase::FindEl(std::string key) // Поиск элемента
{
	std::vector<Student> result; // Результат
	if (SaveRAM.size() > 0 || inScreen) // Если ОЗУ не пуста или работа в ФОне
	{
		result = this->FindInRAM(key);
		if (result.size() > 0 || inScreen) // Поиск был успешным или работа в фоне
			return result;
	}
	result = this->FindInFile(key);
	return result;
}

void DataBase::AddRecord(Student s) // Добавление студента
{
	if (inScreen || bSaveRAM) // Если работа в фоне или загрузка в рам
	{
		SaveRAM.push_back(s);
		if (inScreen) // Если в фоне, то на этом все
			return;
	}
	this->OpenForFileStream(FileName, std::ios_base::binary | std::ios_base::app); // Запись в файл
	this->FileStream.write((char*)&s, sizeof(Student));
	this->FileStream.close();
}

void DataBase::SavingDB(std::string path) // Сохранение бд
{
	path += ".fileDB";
	if (path == FileName) // Если пути совпали, то ничего не делаем
		return;
	std::fstream file_to(path, std::ios_base::binary | std::ios_base::out); // Файл записи
	if (inScreen) // Если в фоне
	{
		for (UINT i = 0; i < SaveRAM.size(); i++) // Считывание из ОЗУ
			file_to.write((char*)&SaveRAM[i], sizeof(Student));
		inScreen = false; // Теперь работа не в фоне
	}
	else
	{
		this->OpenForFileStream(FileName, std::ios_base::binary | std::ios_base::in); // Начинается запись в файл
		Student st;
		while (true)
		{
			FileStream.read((char*)&st, sizeof(Student));
			if (FileStream.eof())
				break;
			file_to.write((char*)&st, sizeof(Student));
		}
		this->FileStream.close();
	}
	file_to.close();
	FileName = path; // Новый путь есть
}

void DataBase::DeleteRecord(Student st_d) // Удаление элемента
{
	if (SaveRAM.size() > 0) // Память не пуста, то ищем элементы и удаляем их из памяти
		while (std::find(SaveRAM.begin(), SaveRAM.end(), st_d) != SaveRAM.end())
			SaveRAM.erase(std::find(SaveRAM.begin(), SaveRAM.end(), st_d));
	if (inScreen) // Если в фоне, то на это все
		return;
	std::rename(FileName.c_str(), "temp.fileDB"); // Переименновываем текущий файл
	std::fstream t_file("temp.fileDB", std::ios_base::binary | std::ios_base::in); // Создаем привязку в нему
	this->OpenForFileStream(FileName, std::ios_base::binary | std::ios_base::out); // Создаем новый файл со старым именем
	Student st;
	while (true) // Перекатываем из одного в другой с пропуском элемента на удаление
	{
		t_file.read((char*)&st, sizeof(Student));
		if (t_file.eof())
			break;
		if (st == st_d)
			continue;
		this->FileStream.write((char*)&st, sizeof(Student));
	}
	t_file.close();
	this->FileStream.close();
	std::remove("temp.fileDB"); // Удаление временного файла
}

void DataBase::AddToHWNDLIST(Student a_st, HWND hListView, int index) // Добалвние в таблицу
{
	if (index == -1) // Если индекс не опредлен, то добавляем на последнее место
		index = ListView_GetItemCount(hListView);
	LVITEM lvi; // Определение ITEM 
	memset(&lvi, 0, sizeof(LVITEM));
	lvi.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
	lvi.state = 0;
	lvi.stateMask = 0;
	lvi.iItem = index;
	lvi.iSubItem = 0;
	int res = ListView_InsertItem(hListView, &lvi);
	ListView_SetItemText(hListView, res, 0, a_st.GetIDChar());
	ListView_SetItemText(hListView, res, 1, a_st.GetFIOChar());
	ListView_SetItemText(hListView, res, 2, a_st.GetAgeChar());
	ListView_SetItemText(hListView, res, 3, (LPSTR)a_st.GetAverBallChar());
	ListView_SetItemText(hListView, res, 4, a_st.GetUniversityChar());
}