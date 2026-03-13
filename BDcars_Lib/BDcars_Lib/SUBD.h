#pragma once
struct ListAuto
{
    char vin[17]; // уникальный номер
    char brand[7];  // название
    char model[10];
    char carcase[15]; // кузов
    char drive[10]; // привод
    ListAuto* next; // указатель на следующий элемент
};

struct ListUser
{
    char login[20];
    char password[20];
    ListUser* next;
};

// печатает элемент списка в консоли O(1)
void PrintAuto(ListAuto* item);

// печатает весь список в консоль O(n)
void PrintListAuto(ListAuto* firstItem);

// удаление списка O(n)
// указатель на первый элемент передаем по ссылке
void DeleteListAuto(ListAuto*& firstItem);

// Функция получения указателя на последний элемент O(n)
// Если функция не изменяет указатель на первый элемент, то передаем его по значению
ListAuto* GetLast(ListAuto* firstItem);

// добавление элемента в конец списка O(n)
ListAuto* AddLast(
    ListAuto*& firstItem,
    char vin[17],
    char brand[7],
    char model[10],
    char carcase[15],
    char drive[10]
);



// поиск элемента по названию продукта O(n)
ListAuto* FindAuto(ListAuto* firstItem, const char* productName);

// авторизация пользователя
bool FindUser(ListUser* firstItem, const char* productName);

bool SaveListToBinaryFile(ListAuto* firstItem, const std::string& filename);

ListAuto* LoadListFromBinaryFile(const std::string& filename);

bool SaveListToTextFile(ListAuto* firstItem, const std::string& filename);

ListAuto* LoadListFromTextFile(const std::string& filename);