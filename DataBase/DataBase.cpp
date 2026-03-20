#include <iostream>
#include <conio.h>
#include <fstream>
// #include "students.h"// подключаем свою библиотеку работы со связным списком
						// список должен хранить данные о вашей предметной области
						// и реализовывать функции, согласно вашему заданию
using namespace std;

const string autoFileName = "ListAutos.bin";
const string userFileName = "ListUser.bin";

struct ListUser
{
	char login[20];
	char password[20];
	ListUser* next;
};

struct ListAuto
{
	char vin[17];
	char brand[7];
	char model[10];
	char carcase[15];
	char drive[10];
	ListAuto* next;
};































void PrintAuto(ListAuto* item)
{
    setlocale(LC_ALL, "");
    if (item == nullptr) return; // проверяем корректность указателя
    cout << "Универсальный номер: " << item->vin << endl; // далее выводим данные в консоль
    cout << "Название: " << item->brand << endl;
    cout << "Модель: " << item->model << endl;
    cout << "Кузов: " << item->carcase << endl;
    cout << "Привод: " << item->drive << endl;
    cout << endl;
}

void PrintListAuto(ListAuto* firstItem)
{
    std::cout << std::endl;
    auto temp = firstItem; // начинаем с первого элемента
    while (temp != nullptr) // перебираем весь список
    {
        PrintAuto(temp); // печатаем очередной элемент ранее созданной функцией
        temp = temp->next; // перемещаемся к следующему элементу
    }
}

// очистка всего списка автомобилей
void DeleteListAuto(ListAuto*& firstItem)
{
    auto temp = firstItem; // вспомогательный указатель, который будет указывать на удаляемый элемент
    // в то время, как firstItem мы будем продвигать вперед на следующие элемент
    while (firstItem != nullptr) // пока не достигли конца списка
    {
        firstItem = firstItem->next; // передвигаем "курсор" на следующий элемент
        delete temp;    // удаляем текущий
        temp = firstItem; // обновляем temp, так чтобы он указывал на следующий
    } // в конце цикла firstItem будет равен nullptr
}

// удаление автомобиля по фильтру
bool DeleteAuto(
    ListAuto*& firstItem,
    char find[17])
{
    if (firstItem == nullptr) return false;
    auto temp = firstItem;
    if (temp->vin == find)  // если указатель на начало списка и на удаляемый элемент совпадают, то
    {                       // частный случай - удаляем первый в списке элемент
        firstItem = firstItem->next; // правим указатель на первый элемент таким образом, чтобы он указывал на следующий в списке
        delete temp; // удаляем первый элемент
        return true; // его нет, возвращаем false
    }
    // если удаляемый элемент не первый в списке
    while (temp->vin != find && temp->next != nullptr) // ищем элемент, предшествующий удаляемому
    {
        temp = temp->next; // передвижение к следующему
    }
    if (temp->next == nullptr) return false;
    auto removableItem = temp->next; // иначе обозначили удаляемый элемент, он следующий по списку
    temp->next = removableItem->next;
    delete removableItem;   // удаляем элемент
    return true;
}



//void Replace(char* str, char what, char value)
//{
//    int len = strlen(str);
//    for (int i = 0; i < len; i++)
//        if (str[i] == what)
//            str[i] = value;
//}

ListAuto* GetLast(ListAuto* firstItem)
{
    if (firstItem == nullptr) return nullptr; // если список пуст, то вернем пустой указатель
    auto temp = firstItem; // временной переменной присваиваем указатель на первый элемент
    while (temp->next != nullptr) // пока ее поле next не пустой указатель (если пустой, то мы достигли последнего элемента!)
    {
        // запомните это присваивание - это переход к следующему в списке элементу
        temp = temp->next;  // перемещаемся к следующему элементу списка
    }
    return temp; // возвращаем указатель на последний элемент
}

void AddFirst(
    ListAuto*& firstItem,
    char productVin[17],
    char productBrand[7],
    char productModel[10],
    char productCarcase[15],
    char productDrive[10])
{
    ListAuto* temp = new ListAuto; // создаем в памяти новый элемент списка
    strcpy_s(temp->vin, productVin);   // присваиваем полям элемента нужные значения
    strcpy_s(temp->brand, productBrand); // имя продукта - это стока C-Style, поэтому копируем ее с помощью специальной функции копирования строк
    strcpy_s(temp->model, productModel); // присваиваем полям элемента нужные значения
    strcpy_s(temp->carcase, productCarcase);
    strcpy_s(temp->drive, productDrive);// присваиваем полям элемента нужные значения
    temp->next = firstItem; // нам нужно встроить элемент в начало списка, поэтому
    // указатель next настраиваем таким образом, чтобы он указывал на элемент
    // который ранее был первым (на него указывает first)
    firstItem = temp;       // а теперь делаем, чтобы first указывал на наш созданный элемент
}


ListAuto* AddLast(
    ListAuto*& firstItem,
    char productVin[17],
    char productBrand[7],
    char productModel[10],
    char productCarcase[15],
    char productDrive[10])
{
    if (firstItem == nullptr) // если список пуст, вызовем функцию добавления в начало списка
    {
        AddFirst(firstItem, productVin, productBrand, productModel, productCarcase, productDrive);
        return firstItem;
    }
    ListAuto* temp = new ListAuto; // создаем в памяти новый элемент списка
    strcpy_s(temp->vin, productVin);   // присваиваем полям элемента нужные значения
    strcpy_s(temp->brand, productBrand); // имя продукта - это стока C-Style, поэтому копируем ее с помощью специальной функции копирования строк
    strcpy_s(temp->model, productModel); // присваиваем полям элемента нужные значения
    strcpy_s(temp->carcase, productCarcase);
    strcpy_s(temp->drive, productDrive); // присваиваем полям элемента нужные значения
    temp->next = nullptr; // нам нужно встроить элемент в конец списка, поэтому
    // указатель next настраиваем таким образом, чтобы он был пустым
    // который ранее был первым (на него указывает first)
    GetLast(firstItem)->next = temp;    // а теперь делаем, чтобы элемент, который до этого был последним
    // (а его мы получаем с помощью уже созданной GetLast)
    // ссылался на наш новый элемент
    return temp; // возвращаем указатель на последний элемент
}

// поиск автомобиля по фильтру
ListAuto* FindAuto(ListAuto* firstItem, char* filter)
{
    auto temp = firstItem;
    while (temp != nullptr)
    {
        if ((strcmp(temp->brand, filter) == 0) || (strcmp(temp->model, filter) == 0) || (strcmp(temp->vin, filter) == 0)) return temp; // возвращаем указатель на найденный элемент
        temp = temp->next; // переходим к следующему элементу
    }
    return nullptr; // если ничего не нашли - возвращаем nullptr
}

// поиск пользователя
bool FindUser(ListUser* firstItem, char* userName, char* password)
{
    auto temp = firstItem;
    while (temp != nullptr)
    {
        if (temp->login == userName && temp->password == password) return true; // возвращаем указатель на найденный элемент
        temp = temp->next; // переходим к следующему элементу
    }
    return false; // если ничего не нашли - возвращаем nullptr
}

bool SaveListToBinaryFile(ListAuto* firstItem, const std::string& filename)
{
    if (firstItem == nullptr) return false;
    std::ofstream f(filename, std::ios::binary);
    if (!f) return false;
    auto temp = firstItem;
    while (temp != nullptr)
    {
        f.write((char*)temp, sizeof(ListAuto));
        temp = temp->next;
    }
    bool result = f.good();
    f.close();
    return result;
}

ListAuto* LoadListFromBinaryFile(const string& filename)
{
    ifstream f(filename, ios::binary);
    if (!f) return nullptr;
    ListAuto item;
    ListAuto* first = nullptr;
    while (f.read((char*)&item, sizeof(ListAuto)))
    {
        AddLast(first, item.vin, item.brand, item.model, item.carcase, item.drive);
    }
    f.close();
    return first;
}






















// функция добавления данных
void AddData(ListAuto*& firstItemAuto)
{
	system("cls");
	char vin[17], brand[7], model[10], carcase[15], drive[10];
	cout << "Добавление данных о автомобиле:\n \n";
	cout << "Введите уникальный номер автомобиля: ";
	cin >> vin;
	cout << "Введите марку автомобиля: ";
	cin >> brand;
	cout << "Введите модель автомобиля: ";
	cin >> model;
	cout << "Введите тип кузова автомобиля: ";
	cin >> carcase;
	cout << "Введите тип привода автомобиля: ";
	cin >> drive;
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
void DeleteData()
{
	system("cls");
	cout << "Введите уникальный номер автомобиля для удаления:\n";
	// здесь реализуете свой алгоритм
	_getch();
}

// функция печати данных по критерию отбора
void PrintFilteredData()
{
	system("cls");
	cout << "Поиск автомобиля по фильтру:\n"; // например выводим только отличников

	_getch();
}

// функция загрузки данных
bool LoadData(ListAuto*& firstItemAuto, ListAuto*& firstItemUser)
{
    //firstItemAuto = LoadListFromBinaryFile(autoFileName);
	//firstItemUser = LoadListFromBinaryFile(userFileName);
	if(firstItemAuto /* || firstItemUser */ == nullptr) return false;
	return true;
}

bool Authorization(ListAuto* firstItemUser)
{
	char login[20], password[20];
	cout << "Введите логин пользователя: ";
	cin >> login;
	cout << "Введите пароль: ";
	cin >> password;
	return true;
	//if (FindUser(firstItemUser, *login, *password)) cout << "/nАвторизация выполнена успешно!";
}

// вывод в консоль меню программы
char MainMenu()
{
	while (true) // бесконечный цикл
	{
		system("cls"); // чистим экран
		cout << "БАЗА ДАННЫХ ПОДДЕРЖАНЫХ АВТОМОБИЛЕЙ АВТОСАЛОНА\n\n"; // выводим название программы, оно у каждого буде свое
		// выводим строки меню, цивра в скобках - клавиша, которую нужно нажать для выбора соответствующего действия
		cout << "[1] Добавить автомобиль" << endl;
		cout << "[2] Вывести список автомобилей" << endl;
		cout << "[3] Поиск по фильтрам" << endl;
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
		case '3': // если 4 то вызываем функцию удаления данных
			DeleteData();
			break;
		case '4': // если 5 то вызываем функцию вывода данных по фильтру
			PrintFilteredData();
			break;
		case '5': // // если 1 то выходим
            SaveListToBinaryFile(firstItemAuto, userFileName);
			return;
		}
	}
}

int main()
{
	ListAuto* firstItemAuto = nullptr;
	ListAuto* firstItemUser = nullptr;
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





















//bool SaveListToTextFile(ListAuto* firstItem, const std::string& filename)
//{
//    if (firstItem == nullptr) return false;
//    std::ofstream f(filename);
//    if (!f) return false;
//    auto temp = firstItem;
//    char itemCopy[30];
//    while (temp != nullptr)
//    {
//        strcpy_s(itemCopy, temp->brand);
//        Replace(itemCopy, ' ', '_');
//        f << temp->vin << " " << itemCopy << " " << temp->model
//            << " " << temp->carcase << "\n";
//        temp = temp->next;
//    }
//    bool result = f.good();
//    f.close();
//    return result;
//}
//
//ListAuto* LoadListFromTextFile(const std::string& filename)
//{
//    std::ifstream f(filename);
//    if (!f) return nullptr;
//    ListAuto item;
//    ListAuto* first = nullptr;
//    while (f >> item.vin >> item.brand >> item.model >> item.carcase >> item.drive)
//    {
//        Replace(item.brand, '_', ' ');
//        AddLast(first, item.vin, item.brand, item.model, item.carcase, item.drive);
//    }
//    f.close();
//    return first;
//}