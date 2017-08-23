#pragma once

#include "abstractComplex.h"

#include <iostream>
#include <locale.h>
#include <iomanip>
#include <conio.h>
#include <exception>
#include <cstdlib>



using namespace std;


class Complex :public AbstractComplex
{
	double realPart;//реальная часть комплексного числа
	double imagPart;//мнимая часть комплексного числа
	static int quantityArrayElements;//количество чисел в массиве
	static AbstractComplex ** arrayOfAbstractPointers;//массив чисел
	static bool heap;//статический или динамический объект

public:

	static const double M_PI; // Пи 3.14159265358979323846
	Complex();//конструктор по умолчанию
	Complex(double real, double imaginary);//конструктор с параметрами
	Complex(Complex &obj);//конструктор копирования
	~Complex();//деструктор

	static void saveNumberToArray(AbstractComplex *thisNumber);//добавление числа (часть контрукторов)
	static void deleteNumber(int index);//удаление числа по индексу
	static void deleteAllNumbersInArray();//удаление всех чисел из массива
	static void createNewNumber(double newReal, double newImag);//создние нового числа с заданными параметрами
	static void changeRealAndImagParts(int index, double newReal, double newImag);//изменяет реальную и мнимую части числа (число определяется по индексу массива)
	static int getCount();//возвращает кол-во комплексных чисел
//	static void showArrayAsClassMethod();//выводит на экран содержимое массива
	static double getRealFromArray(int index);//возвращает реальную часть числа из массива 
	static double getImagFromArray(int index);//возвращает мнимую часть числа из массива

	static void * operator new(size_t bites);//перегрузка оператора new

	virtual double modulus();//возвращает модуль комплексного числа
	virtual double argument();//возвращает аргумент комплексного числа
	virtual double getReal();//возвращает действительную часть комплексного числа
	virtual double getImag();//возвращает мнимую часть комплексного числа
	virtual void changeReal(double newReal);//изменяет реальную часть числа
	virtual void changeImag(double newImag);//изменяет мнимую часть числа
};
