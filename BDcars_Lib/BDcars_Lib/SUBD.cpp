#include <iostream>
#include <fstream>
#include <string>
#include "SUBD.h"
using namespace std;

void PrintAuto(ListAuto* item)
{
    setlocale(LC_ALL, "rus");
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



void Replace(char* str, char what, char value)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
        if (str[i] == what)
            str[i] = value;
}

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

bool SaveListToTextFile(ListAuto* firstItem, const std::string& filename)
{
    if (firstItem == nullptr) return false;
    std::ofstream f(filename);
    if (!f) return false;
    auto temp = firstItem;
    char itemCopy[30];
    while (temp != nullptr)
    {
        strcpy_s(itemCopy, temp->brand);
        Replace(itemCopy, ' ', '_');
        f << temp->vin << " " << itemCopy << " " << temp->model
            << " " << temp->carcase << "\n";
        temp = temp->next;
    }
    bool result = f.good();
    f.close();
    return result;
}

ListAuto* LoadListFromTextFile(const std::string& filename)
{
    std::ifstream f(filename);
    if (!f) return nullptr;
    ListAuto item;
    ListAuto* first = nullptr;
    while (f >> item.vin >> item.brand >> item.model >> item.carcase >> item.drive)
    {
        Replace(item.brand, '_', ' ');
        AddLast(first, item.vin, item.brand, item.model, item.carcase, item.drive);
    }
    f.close();
    return first;
}