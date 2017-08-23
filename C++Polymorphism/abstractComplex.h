#pragma once

#include<iostream>

using namespace std;

class AbstractComplex
{
protected:

public:
	virtual double modulus() = 0;//возвращает модуль комплексного числа
	virtual double argument() = 0;//возвращает аргумент комплексного числа
	virtual double getReal() = 0;//возвращает действительную часть комплексного числа
	virtual double getImag() = 0;//возвращает мнимую часть комплексного числа
	virtual void changeReal(double newReal) = 0;//изменяет реальную часть числа
	virtual void changeImag(double newImag) = 0;//изменяет мнимую часть числа

	virtual ~AbstractComplex() {};//деструктор по умолчанию
};