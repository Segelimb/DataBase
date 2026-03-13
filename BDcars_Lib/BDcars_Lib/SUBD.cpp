#include <iostream>
#include <fstream>
#include "SUBD.h"
using namespace std;

void PrintAuto(ListAuto* item)
{
    if (item == nullptr) return; // провер€ем корректность указател€
    cout << "”ниверсальный номер: " << item->vin << endl; // далее выводим данные в консоль
    cout << "Ќазвание: " << item->brand << endl;
    cout << "ћодель: " << item->model << endl;
    cout << " узов: " << item->carcase << endl;
    cout << "ѕривод: " << item->drive << endl;
    cout << endl;
}

void PrintListAuto(ListAuto* firstItem)
{
    std::cout << std::endl;
    auto temp = firstItem; // начинаем с первого элемента
    while (temp != nullptr) // перебираем весь список
    {
        PrintAuto(temp); // печатаем очередной элемент ранее созданной функцией
        temp = temp->next; // перемещаемс€ к следующему элементу
    }
}

void DeleteAuto(ListAuto*& firstItem)
{
    auto temp = firstItem; // вспомогательный указатель, который будет указывать на удал€емый элемент
    // в то врем€, как firstItem мы будем продвигать вперед на следующие элемент
    while (firstItem != nullptr) // пока не достигли конца списка
    {
        firstItem = firstItem->next; // передвигаем "курсор" на следующий элемент
        delete temp;    // удал€ем текущий
        temp = firstItem; // обновл€ем temp, так чтобы он указывал на следующий
    } // в конце цикла firstItem будет равен nullptr
}

// поиск элемента по названию продукта O(n)
ListAuto* Find(ListAuto* firstItem, const char* brandName)
{
    auto temp = firstItem; // начинаем с указанного элемента
    while (temp != nullptr) // перебираем весь список
    {
        if (strcmp(temp->brand, brandName) == 0) // если название продукта подходит
        {
            return temp; // возвращаем указатель на найденный элемент
        }
        temp = temp->next; // переходим к следующему элементу
    }
    return nullptr; // если ничего не нашли - возвращаем nullptr
}


bool SaveListToBinaryFile(ListAuto* firstItem, const std::string& filename)
{
    if (firstItem == nullptr) return false;
    std::ofstream f(filename, std::ios::binary);
    if (!f) return false;
    auto temp = firstItem;
    while (temp != nullptr)
    {
        f.write((char*)temp, sizeof(ListItem));
        temp = temp->next;
    }
    bool result = f.good();
    f.close();
    return result;
}

ListItem* LoadListFromBinaryFile(const std::string& filename)
{
    std::ifstream f(filename, std::ios::binary);
    if (!f) return nullptr;
    ListItem item;
    ListItem* first = nullptr;
    while (f.read((char*)&item, sizeof(ListItem)))
    {
        AddLast(first, item.id, item.name, item.price, item.count);
    }
    f.close();
    return first;
}

bool SaveListToTextFile(ListItem* firstItem, const std::string& filename)
{
    if (firstItem == nullptr) return false;
    std::ofstream f(filename);
    if (!f) return false;
    auto temp = firstItem;
    char itemCopy[30];
    while (temp != nullptr)
    {
        strcpy_s(itemCopy, temp->name);
        Replace(itemCopy, ' ', '_');
        f << temp->id << " " << itemCopy << " " << temp->price
            << " " << temp->count << "\n";
        temp = temp->next;
    }
    bool result = f.good();
    f.close();
    return result;
}

ListItem* LoadListFromTextFile(const std::string& filename)
{
    std::ifstream f(filename);
    if (!f) return nullptr;
    ListItem item;
    ListItem* first = nullptr;
    while (f >> item.id >> item.name >> item.price >> item.count)
    {
        Replace(item.name, '_', ' ');
        AddLast(first, item.id, item.name, item.price, item.count);
    }
    f.close();
    return first;
}