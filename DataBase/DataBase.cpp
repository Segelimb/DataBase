#include <iostream>
#include <conio.h>
#include <fstream>
#include "../SUBD/SUBD.h" // билиотека SUBD для работы с базой данных

using namespace std;

const string autoFileName = "ListAutos.bin";
const string userFileName = "ListUser.bin";


char* ImputValue(string print, int MaxSize)
{
	char* str = new char[MaxSize];

	while (1)
	{
		cout << print << " (Не более " << MaxSize - 1 << " символов): ";
		cin.getline(str, MaxSize);
		if (cin.fail())
		{
			cout << "Ошибка: введено слишком много символов!" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else break;
	}
	return str;
}
// функция добавления данных
void AddData(ListAuto*& firstItemAuto)
{
	system("cls");
	cout << "Добавление данных о автомобиле:\n \n";
	char* vin = ImputValue("Введите уникальный номер автомобиля", 18);
	char* brand = ImputValue("Введите марку автомобиля", 10);
	char* model = ImputValue("Введите модель автомобиля", 10);
	char* carcase = ImputValue("Введите тип кузова автомобиля", 15);
	char* drive = ImputValue("Введите тип привода автомобиля", 10);
	AddLast(firstItemAuto, vin, brand, model, carcase, drive);
	cout << "\nУспешно добавлены данные об автомобиле!";
	_getch();
}

// функция печати данных
void PrintDataListAuto(ListAuto*& firstItemAuto)
{
	system("cls");
	cout << "Список автомобилей в продаже:\n\n";
	PrintListAuto(firstItemAuto);
	_getch();
}

// функция удаления данных
void DeleteData(ListAuto*& firstItemAuto)
{
	system("cls");
	char* vin = ImputValue("Введите уникальный номер автомобиля для удаления", 18);
	if (DeleteAuto(firstItemAuto, vin)) cout << "Удаление произведено успешно!";
	else cout << "Автомобиль с данным номером не найден";
	_getch();
}

// функция печати данных по критерию отбора
char MenuPrintFilteredData(ListAuto*& firstItemAuto)
{
	system("cls");
	cout << "Поиск автомобиля по фильтру:\n\n"; // например выводим только отличников
	cout << "[1] Поиск автомобиля по уникальному номеру" << endl;
	cout << "[2] Поиск автомобиля по марке" << endl;
	cout << "[3] Поиск автомобиля по модели" << endl;
	cout << "[4] Выход в главное меню" << endl << endl;
	cout << "Для выбора пункта меню нажмите клавишу с номером нужного действия > ";
	char choice = _getch(); // считываем нажатую пользователем клавишу
	if (choice < '1' || choice > '5') // проверяем, соответствует ли клавиша пунктам менюд
	{	// если нет, то требуем повторить ввод
		cout << "\nТакого варианта не существует! Нажмите любую клавишу...";
		_getch();
	}
	else
	{	// если соответствует, то возвращаем в вызываемую программу символ
		// соответствующий нажатой клавише
		return choice;
	}
}

void PrintFilteredData(ListAuto*& firstItemAuto)
{
	char choice = 0;
	choice = MenuPrintFilteredData(firstItemAuto); // определяем, какой пункт меню выбрал пользователь
	if (choice == '4') return;
	system("cls");
	bool AutoFind;

	char* find = ImputValue("Введите значение фильтра", 18);
	// переменная choice будет хранить символ, соответствующий 
	// выбранному пункту меню
	switch (choice) // проверяем какую клавишу нажал пользователь
	{
	case '1': // если 1 то вызываем функцию добавления данных
		AutoFind = FindAuto(firstItemAuto, 1, find);
		break;
	case '2': // если 2 то вызываем функцию вывода данных
		AutoFind = FindAuto(firstItemAuto, 2, find);
		break;
	case '3': // если 5 то вызываем функцию вывода данных по фильтру
		AutoFind = FindAuto(firstItemAuto, 3, find);
		break;
	default:
		AutoFind = false;
		break;
	}
	cout << endl;
	if (AutoFind == false) cout << endl << "Данный авто не найден";
	_getch();
}

// функция загрузки данных
bool LoadData(ListAuto*& firstItemAuto, ListUser*& firstItemUser)
{
	firstItemAuto = LoadListFromBinaryFile(autoFileName);
	firstItemUser = LoadListUserFromBinaryFile(userFileName);
	if (firstItemAuto == nullptr || firstItemUser == nullptr) return false;
	return true;
}

bool Authorization(ListUser* firstItemUser)
{
	while (1)
	{
		system("cls");
		char* login = ImputValue("Введите логин пользователя", 20);
		char* password = ImputValue("Введите пароль", 20);
		//return true;
		if (FindUser(firstItemUser, login, password))
		{
			cout << "\nАвторизация выполнена успешно!";
			_getch();
			return true;
		}
		else
		{
			cout << "\nНеверный логин или пароль" << endl << endl;
			cout << "[1] Повторить попытку" << endl;
			cout << "[2] Закрыть программу" << endl << endl;
			cout << "Для выбора пункта меню нажмите клавишу с номером нужного действия > ";
			char choice = _getch(); // считываем нажатую пользователем клавишу
			while (choice < '1' || choice > '2') // проверяем, соответствует ли клавиша пунктам менюд
			{	// если нет, то требуем повторить ввод
				cout << "\nТакого варианта не существует! Нажмите любую клавишу...";
				choice = _getch();
			}
			if (choice == '2') break;
		}
	}
	return false;
}

// вывод в консоль меню программы
char MainMenu()
{
	while (true) // бесконечный цикл
	{
		system("cls"); // чистим экран
		cout << "УЧЕТ ПОДЕРЖАННЫХ АВТОМОБИЛЕЙ АВТОСАЛОНА Г. ВОТКИНСК\n\n"; // выводим название программы, оно у каждого буде свое
		// выводим строки меню, цивра в скобках - клавиша, которую нужно нажать для выбора соответствующего действия
		cout << "[1] Добавить автомобиль" << endl;
		cout << "[2] Вывести список автомобилей" << endl;
		cout << "[3] Поиск по фильтру" << endl;
		cout << "[4] Удалить данные об автомобиле" << endl;
		cout << "[5] Завершить работу" << endl;

		cout << "Для выбора пункта меню нажмите клавишу с номером нужного действия > ";
		char choice = _getch(); // считываем нажатую пользователем клавишу
		if (choice < '1' || choice > '5') // проверяем, соответствует ли клавиша пунктам менюд
		{	// если нет, то требуем повторить ввод
			cout << "\nТакого варианта не существует! Нажмите любую клавишу...";
			_getch();
		}
		else
		{	// если соответствует, то возвращаем в вызываемую программу символ
			// соответствующий нажатой клавише
			return choice;
		}
	}
}

// обработка действий пользователя
void HandleEvents(ListAuto*& firstItemAuto)
{
	char choice = 0;
	while (choice != '5') // цикл пока пользователь не нажал ВЫХОД
	{
		choice = MainMenu(); // определяем, какой пункт меню выбрал пользователь
		// переменная choice будет хранить символ, соответствующий 
		// выбранному пункту меню
		switch (choice) // проверяем какую клавишу нажал пользователь
		{
		case '1': // если 1 то вызываем функцию добавления данных
			AddData(firstItemAuto);
			break;
		case '2': // если 2 то вызываем функцию вывода данных
			PrintDataListAuto(firstItemAuto);
			break;
		case '3': // если 5 то вызываем функцию вывода данных по фильтру
			PrintFilteredData(firstItemAuto);
			break;
		case '4': // если 4 то вызываем функцию удаления данных 
			DeleteData(firstItemAuto);
			break;
		case '5': // // если 1 то выходим
			SaveListToBinaryFile(firstItemAuto, autoFileName);
			return;
		}
	}
}

int main()
{
	ListAuto* firstItemAuto = nullptr;
	ListUser* firstItemUser = nullptr;
	setlocale(LC_ALL, "");
	if (!LoadData(firstItemAuto, firstItemUser)) // если чтение базы данных неудачно, то продолжение выполнения программы невозможно
	{	// выводим сообщение об ошибке и выходим с кодом 1
		cout << "Ошибка чтения базы данных\n";
		return 1;
		// как вариант, если базу прочитать невозможно, вы можете создать новую базу данных и продолжить работу
		// с программой
	}
	if (Authorization(firstItemUser))
		HandleEvents(firstItemAuto); // вызываем функцию обработки нажатий клавиш пользователем
}
