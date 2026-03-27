#pragma once
struct ListUser
{
    char login[20];
    char password[20];
    ListUser* next;
};

struct ListAuto
{
    ListAuto* first;
    char vin[18]; // уникальный номер
    char brand[7];  // название
    char model[10];
    char carcase[15]; // кузов
    char drive[10]; // привод
    ListAuto* next; // указатель на следующий элемент
};

// печатает элемент списка в консоли O(1)
void PrintAuto(ListAuto* item);

// печатает весь список в консоль O(n)
void PrintListAuto(ListAuto* firstItem);

// удаление списка O(n)
// указатель на первый элемент передаем по ссылке
void DeleteListAuto(ListAuto*& firstItem);
bool DeleteAuto(ListAuto*& firstItem, char find[18]);

// Функция получения указателя на последний элемент O(n)
// Если функция не изменяет указатель на первый элемент, то передаем его по значению
ListAuto* GetLast(ListAuto* firstItem);

void AddFirst(
    ListAuto*& firstItem,
    char Vin[18],
    char Brand[7],
    char Model[10],
    char Carcase[15],
    char Drive[10]
);

// добавление элемента в конец списка O(n)
ListAuto* AddLast(
    ListAuto*& firstItem,
    char vin[18],
    char brand[7],
    char model[10],
    char carcase[15],
    char drive[10]
);

// поиск элемента по названию продукта O(n)
bool FindAuto(ListAuto* firstItem, int filter, char find[18]);

// авторизация пользователя
bool FindUser(ListUser* firstItem, char userName[20], char password[20]);

bool SaveListToBinaryFile(ListAuto* firstItem, const string& filename);

ListAuto* LoadListFromBinaryFile(const string& filename);

void AddFirstUser(ListUser*& firstItem, char login[20], char password[20]);

ListUser* GetLastUser(ListUser* firstItem);

ListUser* AddLastUser(ListUser*& firstItem, char login[20], char password[20]);

ListUser* LoadListUserFromBinaryFile(const string& filename);