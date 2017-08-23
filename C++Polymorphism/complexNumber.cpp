#include "complexNumber.h"

int Complex::quantityArrayElements = 0;
AbstractComplex ** Complex::arrayOfAbstractPointers = NULL;
bool Complex::heap = false;
const double Complex::M_PI = 3.14159265358979323846;

Complex::Complex() : realPart(1.1), imagPart(1.1)
{
	if (heap == true)
	{
		saveNumberToArray(this);
	}
	//	cout << "Конструктор по умолчанию " << endl;
	//	cout << "Объект " << realPart << "+" << imagPart << "i" << endl;
}

Complex::Complex(double real, double imaginary) :realPart(real), imagPart(imaginary)//конструктор с параметрами
{
	if (heap == true)
	{
		saveNumberToArray(this);
	}
	//	cout << "Конструктор со списком инициализации " << endl;
	//	cout << "Объект " << realPart << "+" << imagPart << "i" << endl;
}

Complex::Complex(Complex & obj)//конструктор копирования
{
	this->realPart = obj.realPart;
	this->imagPart = obj.imagPart;
	if (heap == true)
	{
		saveNumberToArray(this);
	}
	//	cout << "Конструктор КОПИРОВАНИЯ " << endl;
}

Complex::~Complex()// деструктор
{
	if (quantityArrayElements == 1)
	{
		//		cout << "Деструктор quantityArrayElements == 1" << endl;
		delete[]arrayOfAbstractPointers;
		arrayOfAbstractPointers = NULL;
		quantityArrayElements--;
	}
	if (quantityArrayElements > 1)
	{
		//		cout << "Деструктор quantityArrayElements > 1" << endl;
		AbstractComplex ** arrayOfAbstractPointersTemp = NULL;
		arrayOfAbstractPointersTemp = new AbstractComplex*[quantityArrayElements - 1];
		for (int i = 0, j = 0; i < quantityArrayElements; i++)
		{
			if (*(arrayOfAbstractPointers + i) == this)
			{
				continue;
			}
			*(arrayOfAbstractPointersTemp + j) = *(arrayOfAbstractPointers + i);
			j++;
		}
		delete[]arrayOfAbstractPointers;
		arrayOfAbstractPointers = arrayOfAbstractPointersTemp;
		arrayOfAbstractPointersTemp = NULL;
		delete arrayOfAbstractPointersTemp;

		quantityArrayElements--;
		//		cout << "quantityArrayElements = " << quantityArrayElements << endl;
	}
	//	cout << "Деструктор" << endl;
	//cout << "Удаляется объект " << realPart << "+" << imagPart << "i" << endl;
}

void Complex::saveNumberToArray(AbstractComplex *thisNumber)//добавляет число в массив
{
	quantityArrayElements++;
	AbstractComplex ** arrayOfAbstractPointersTemp = NULL;
	arrayOfAbstractPointersTemp = new AbstractComplex*[quantityArrayElements];
	if (arrayOfAbstractPointers != NULL)
	{
		for (int i = 0; i < quantityArrayElements - 1; i++)
		{
			*(arrayOfAbstractPointersTemp + i) = *(arrayOfAbstractPointers + i);
		}
	}
	*(arrayOfAbstractPointersTemp + (quantityArrayElements - 1)) = thisNumber;

	delete[]arrayOfAbstractPointers;
	arrayOfAbstractPointers = arrayOfAbstractPointersTemp;
	arrayOfAbstractPointersTemp = NULL;
	delete arrayOfAbstractPointersTemp;
	Complex::heap = false;
}

void Complex::deleteNumber(int index)//удаляет число из массива по индексу
{
	try
	{
		if (index < 0 || index >= quantityArrayElements)
		{
			throw exception("Введен не верный индекс.");
		}
	}
	catch (exception str)
	{
		cout << str.what() << endl;
		cin.clear();
		cin.sync();
		cin.ignore(10000, '\n');
		return;
	}
	delete arrayOfAbstractPointers[index];
}

void Complex::deleteAllNumbersInArray()//удаление всех чисел из массива
{
	if (quantityArrayElements > 0)
	{
		delete[]arrayOfAbstractPointers;
		arrayOfAbstractPointers = NULL;
		quantityArrayElements = 0;
	}
}

void Complex::createNewNumber(double newReal, double newImag)
{
	try
	{
		if (!cin.good())
		{
			throw exception("Введено не верное значение (не действительное число)");
		}
	}
	catch (exception str)
	{
		cout << str.what() << endl;
		cin.clear();
		cin.sync();
		cin.ignore(10000, '\n');
		return;
	}
	new Complex(newReal, newImag);
}

void Complex::changeRealAndImagParts(int index, double newReal, double newImag)
{
	try
	{
		if (!cin.good())
		{
			throw exception("Введено не верное значение (не действительное число)");
		}
	}
	catch (exception str)
	{
		cout << str.what() << endl;
		cin.clear();
		cin.sync();
		cin.ignore(10000, '\n');
		return;
	}
	arrayOfAbstractPointers[index]->changeReal(newReal);
	arrayOfAbstractPointers[index]->changeImag(newImag);
}

int Complex::getCount()//возвращает количество комплексных чисел в массиве
{
	return quantityArrayElements;
}

/*
void Complex::showArrayAsClassMethod()//выводит на экран содержимое массива
{
	if (arrayOfAbstractPointers != NULL)
	{
		cout << setw(5) << "Index" << setw(20) << "Комплексное число" << endl;
		for (int i = 0; i < quantityArrayElements; i++)
		{
			cout << setw(3) << i;
			cout << setw(11) << arrayOfAbstractPointers[i]->getReal() << " + ";
			cout << setw(5) << arrayOfAbstractPointers[i]->getImag() << "i" << endl;
		}
	}
	else
	{
		cout << "Массив пустой." << endl;
	}

}
*/
double Complex::getRealFromArray(int index)//возвращает реальную часть числа из массива 
{
	return arrayOfAbstractPointers[index]->getReal();
}

double Complex::getImagFromArray(int index)//возвращает мнимую часть числа из массива
{
	return arrayOfAbstractPointers[index]->getImag();
}

void * Complex::operator new(size_t bites)
{
	//	cout << "перегрузка new" << endl;
	Complex::heap = true;
	Complex *p = (Complex *)malloc(sizeof(Complex));
	return p;
}

double Complex::modulus()//возвращает модуль комплексного числа
{
	return sqrt((realPart*realPart) + (imagPart*imagPart));
}

double Complex::argument()//возвращает аргумент комплексного числа
{
	double arg = 0.0;
	if (realPart > 0)
	{
		arg = atan(imagPart / realPart);
	}
	if (realPart < 0 && imagPart >= 0)
	{
		arg = atan(imagPart / realPart) + M_PI;
	}
	if (realPart < 0 && imagPart < 0)
	{
		arg = atan(imagPart / realPart) - M_PI;
	}
	if (realPart == 0 && imagPart > 0)
	{
		arg = M_PI / 2;
	}
	if (realPart == 0 && imagPart < 0)
	{
		arg = -(M_PI / 2);
	}
	if (realPart == 0 && imagPart == 0)
	{
		throw exception("Для комплексного числа 0.0+0.0i аргумент не определен.");
	}
	return arg;
}

double Complex::getReal()//возвращает действительную часть комплексного числа
{
	return realPart;
}

double Complex::getImag() //возвращает мнимую часть комплексного числа
{
	return imagPart;
}

void Complex::changeReal(double newReal)
{
	realPart = newReal;
}

void Complex::changeImag(double newImag)
{
	imagPart = newImag;
}
