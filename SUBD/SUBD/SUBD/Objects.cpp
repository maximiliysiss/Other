#include "Objects.h"

char* Learned::GetAverBallChar()
{
	_itoa_s((int)this->GetAverBall(), res, 10); // Перевод числа в указатель char в 10тичной системе
	return res;
}

Learned::Learned(int _cMarks, std::string _university) : cMarks(_cMarks)
{
	if (cMarks > COUNT_MARKS) // Если больше, чем выделенно, то максимум оценок
		cMarks = COUNT_MARKS;
	strcpy_s(university, _university.c_str());
	this->CreateMarks();
}

std::string Student::to_String()
{
	std::string result = std::string(name) + ' ' + std::string(university) + ' ' + std::to_string(age) + ' ' + std::to_string(cMarks) + ' ' + std::to_string(id);
	for (int i = 0; i < cMarks; i++)
		result += ' ' + std::to_string(Marks[i]);
	return result;
}