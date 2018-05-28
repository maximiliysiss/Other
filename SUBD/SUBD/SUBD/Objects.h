#pragma once
#include <Windows.h>
#include <string>
#include <fstream>
#include <numeric>
#include <commctrl.h>
#include <ctime>
#include <vector>
#include <cstdlib>
#include "Defines.h"

#pragma comment(lib, "ComCtl32.Lib")

class Human // Класс человека
{
private:
	char value[4]; // Для хранения результатов возврата указателей на char для возврата int переменной
protected:
	int age; // Возраст
	char name[50]; // Имя
public:
	Human() { age = 0; strcpy_s(name, "A A A"); } // Default конструктор
	Human(int _age, std::string _name) :age(_age) { strcpy_s(name, _name.c_str()); } // Обычный конструктор		
	Human(const Human& h) = default; // Деофлт конструктор копирования
	inline friend bool operator==(Human & h1, Human h2) // Опреатор сравнения
	{
		return h1.age == h2.age && strcmp(h1.name, h2.name) == 0;
	}
	inline char* GetFIOChar() // Получить ФИО
	{
		return name;
	}
	inline std::string GetFIO() // Получить ФИО, как строку
	{
		return std::string(name);
	}
	inline int GetAge() // Получить возраст как int
	{
		return age;
	}
	inline char* GetAgeChar() // Получить возраст как указатель на char
	{
		_itoa_s(age, value, 10);
		return value;
	}
	inline std::string GetName() // Получить имя
	{
		return this->GetFIO().substr(0, this->GetFIO().find(' '));
	}
	inline std::string GetSurName() // Получить фамилию
	{
		return this->GetFIO().substr(this->GetFIO().find(' ') + 1, this->GetFIO().substr(this->GetFIO().find(' ') + 1).find(' '));
	}
	inline std::string GetThirdName() // Получить отчество
	{
		return this->GetFIO().substr(this->GetFIO().find(' ') + 1 + this->GetFIO().substr(this->GetFIO().find(' ') + 1).find(' ') + 1);
	}
	Human& operator=(Human & h) = default; // Дофолт оператор копирования
};

class Learned // Класс обучающийся
{
private:
	char res[10]; // Хранение промежуточных числовых результатов
protected:
	int Marks[COUNT_MARKS]; // Оценки
	char university[50]; // Универ
	int cMarks; // Количество оценок
	void CreateMarks() // Сгенерировать оценки
	{
		for (int i = 0; i < cMarks; i++)
			Marks[i] = rand() % MAX_BALL;
	}
public:
	inline std::string GetUniversity() // Получить универ в виде строки
	{
		return std::string(university);
	}
	inline char* GetUniversityChar() // Получить универ - указатель
	{
		return university;
	}
	float GetAverBall() // Получить средний балл
	{
		return cMarks != 0 ? ((float)std::accumulate(Marks, Marks + cMarks, 0) / cMarks) : 0;
	}
	char* GetAverBallChar(); // Получить средний балл в виде указателя
	Learned() { cMarks = 0; strcpy_s(university, "NoName"); } // Дефолт конструктор
	Learned(int _cMarks, std::string _university); // Классический конструктор
	Learned(const Learned& l) = default; // Дефолт конструктор копирования
	inline friend bool operator==(Learned &l1, Learned &l2) // Оператор сравнения
	{
		return l1.cMarks == l2.cMarks && strcmp(l1.university, l2.university) == 0 && l1.GetAverBall() == l2.GetAverBall();
	}
	Learned& operator=(const Learned &l) = default; // Дефолт оператор копирования
};

class Student : public Learned, public Human // Класс студента
{
private:
	int id; // ИД
	char value[10]; // Храниение промежуточных результатов
public:
	Student() :Learned(), Human() // Дефолт констурктор
	{
		id = -1;
	}
	inline int GetID() // Получить айди
	{
		return id;
	}
	inline char* GetIDChar() // Получить айди в виде указателя
	{
		_itoa_s(id, value, 10);
		return value;
	}
	Student(int _id, int age, std::string name, int cMarks, std::string university) :Learned(cMarks, university), Human(age, name), id(_id) {} // Классический конструктор
	Student(const Student & s) = default; // Дефолт контструктор копирования
	friend bool operator==(Student & s1, const std::string & key) // Оператор сравнения с ключом
	{
		if (s1.GetName() == key || s1.GetSurName() == key || s1.GetThirdName() == key || s1.GetFIO() == key
			|| std::to_string(s1.GetID()) == key)
			return true;
		return false;
	}
	Student& operator=(Student& s) = default; // Оператор копирования
	friend bool operator==(Student & s1, Student & s2) // Оператор сравнения
	{
		return (Human)s1 == (Human)s2 && s1.id == s2.id;
	}
	bool CheckSession() // Проверка сдачи сессии
	{
		return this->GetAverBall() > CHECK_SESSION;
	}
	std::string to_String(); // Перевод с строку
};
