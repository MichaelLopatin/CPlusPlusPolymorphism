
#include "complexNumber.h"
#include "abstractComplex.h"

enum Menu
{
	exitMenu = 48,
	showAllNumbers,
	enterNewComplexNumber,
	changeParametersOfComplexNumber,
	deleteComplexNumber,
	deleteAllComplexNumberFromArray,
	showQuantityOfArrayElements
};

int random(int i);//псевдорандом
void showMenu(); //показывает пункты меню
void clearBufAndErr(); //чистит поток
void showAllComplexNumber();//отображает все комплексные числа
int enterIndex();//ввод индекса с клавиатуры
void enterQuantityOfComplexNumber(int &quantityOfComplexNumber);//вводит начальное кол-во комплексных чисел
void createStartingArrayOfComplexNumbers();//создание начального массива с комплексными числами
void menu();//работа в меню


void main()
{
	setlocale(LC_ALL, "Russian");
	Complex a(5.55, 7.77); //проверка: статические числа в массив не добавляет, что и требовалось
	createStartingArrayOfComplexNumbers();
	menu();
}


int random(int i)
{
	srand(i);
	return(rand());
}

void showMenu()
{
	cout << "_______________________________" << endl;
	cout << "  1 - Отобразить список комплексных чисел" << endl;
	cout << "  2 - Добавить число" << endl;
	cout << "  3 - Изменить реальную и мнимую часть числа" << endl;
	cout << "  4 - Удалить число" << endl;
	cout << "  5 - Удалить все числа из массива" << endl;
	cout << "  6 - Отобразить количество элементов массива" << endl;
	cout << "  0 - Выход из программы" << endl;
	cout << "_______________________________" << endl;
}

void clearBufAndErr()
{
	cin.clear();
	cin.sync();
	cin.ignore(10000, '\n');
}

void showAllComplexNumber()
{
	if (Complex::getCount() == 0)
	{
		cout << "Массив пустой." << endl;
	}
	else
	{
		cout << setw(5) << "Index" << setw(20) << "Комплексное число" << endl;
		for (int i = 0; i < Complex::getCount(); i++)
		{
			cout << setw(3) << i;
			cout << setw(11) << Complex::getRealFromArray(i) << " + ";
			cout << setw(5) << Complex::getImagFromArray(i) << "i" << endl;
		}
	}
}

int enterIndex()
{
	int index = -1;
	try
	{
		cin >> index;
		if (!cin.good() || (index < 0) || (index >= Complex::getCount()))
		{
			throw exception("Введено не верное значение (необходимо целое неотрицательное)");
		}
	}
	catch (exception str)
	{
		cout << str.what() << endl;
		clearBufAndErr();
		index = -1;
	}
	return index;
}

void enterQuantityOfComplexNumber(int &quantityOfComplexNumber)
{
	bool endCycle = true;
	while (endCycle)
	{
		cout << "Введите начальное количество комплексных чисел:" << endl;
		try
		{
			cin >> quantityOfComplexNumber;
			if (!cin.good() || (quantityOfComplexNumber <= 0))
			{
				throw exception("Введено не верное значение (необходимо натуральное число).");
			}
			else
			{
				clearBufAndErr();
				endCycle = false;
			}
		}
		catch (exception str)
		{
			cout << str.what() << endl;
			clearBufAndErr();
		}
	}
}

void createStartingArrayOfComplexNumbers()
{
	int quantityOfComplexNumber = 0;//начальное количество комплексных чисел
	enterQuantityOfComplexNumber(quantityOfComplexNumber);
	for (int i = 0; i < quantityOfComplexNumber; i++)
	{
		double realRartTemp, imagRartTemp;
		realRartTemp = double(random(i + 1) % 100) + double(((random(i + 1) / 10 + random(i + 1) % 10) % 100)) / 100;
		imagRartTemp = double(random(i*i) % 100) + double(((random(i*i) / 10 + random(i*i) % 10) % 100)) / 100;
		Complex::createNewNumber(realRartTemp, imagRartTemp);
	}
}


void menu()
{
	char key;//код нажатой клавиши
	bool quit = true;//завершение работы в меню
	showMenu();
	do
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
			case exitMenu:
			{
				quit = false;
				Complex::deleteAllNumbersInArray();
				return;
				break;
			}
			case showAllNumbers:
			{
				//отображается двумя способами
				showAllComplexNumber();
		//		cout << "------------------------------------" << endl;
		//		Complex::showArrayAsClassMethod();
				break;
			}
			case enterNewComplexNumber:
			{
				double realRartTemp = 0.0;
				double imagRartTemp = 0.0;

				cout << "Введите значения реальной и мнимой части комплексного числа" << endl;
				cin >> realRartTemp;
				cin >> imagRartTemp;
				Complex::createNewNumber(realRartTemp, imagRartTemp);
				break;
			}
			case changeParametersOfComplexNumber:
			{
				cout << "Введите индекс изменяемого числа." << endl;
				int indexTemp = enterIndex();
				if (indexTemp == -1)
				{
					break;
				}
				double realRartTemp = 0.0;
				double imagRartTemp = 0.0;

				cout << "Введите значения реальной и мнимой части комплексного числа" << endl;
				cin >> realRartTemp;
				cin >> imagRartTemp;
				Complex::changeRealAndImagParts(indexTemp, realRartTemp, imagRartTemp);
				break;
			}
			case deleteComplexNumber:
			{
				cout << "Введите индекс удаляемого числа." << endl;
				int indexTemp = enterIndex();
				if (indexTemp == -1)
				{
					break;
				}
				Complex::deleteNumber(indexTemp);
				break;
			}
			case deleteAllComplexNumberFromArray:
			{
				Complex::deleteAllNumbersInArray();
				break;
			}
			case showQuantityOfArrayElements:
			{
				cout << "Количество элементов массива:  " << Complex::getCount() << endl;
				break;
			}
			default:cout << "Выбран некорректный пункт меню, будьте внимательны" << endl;
				break;
			}
			showMenu();
		}
	} while (quit);
}
