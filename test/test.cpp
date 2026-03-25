// test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
using namespace std;

const string userFileName = "ListUser.bin";

struct ListUser
{
    char login[20];
    char password[20];
    ListUser* next;
};


ListUser* GetLast(ListUser* firstItem)
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
    ListUser*& firstItem,
    char productVin[20],
    char productBrand[20])
{
    ListUser* temp = new ListUser; // создаем в памяти новый элемент списка
    strcpy_s(temp->login, productVin);   // присваиваем полям элемента нужные значения
    strcpy_s(temp->password, productBrand); // имя продукта - это стока C-Style, поэтому копируем ее с помощью специальной функции копирования строк

    temp->next = firstItem; // нам нужно встроить элемент в начало списка, поэтому
    // указатель next настраиваем таким образом, чтобы он указывал на элемент
    // который ранее был первым (на него указывает first)
    firstItem = temp;       // а теперь делаем, чтобы first указывал на наш созданный элемент
}


ListUser* AddLast(
    ListUser*& firstItem,
    char productVin[18],
    char productBrand[7])
{
    if (firstItem == nullptr) // если список пуст, вызовем функцию добавления в начало списка
    {
        AddFirst(firstItem, productVin, productBrand);
        return firstItem;
    }
    ListUser* temp = new ListUser; // создаем в памяти новый элемент списка
    strcpy_s(temp->login, productVin);   // присваиваем полям элемента нужные значения
    strcpy_s(temp->password, productBrand); // имя продукта - это стока C-Style, поэтому копируем ее с помощью специальной функции копирования строк

    temp->next = nullptr; // нам нужно встроить элемент в конец списка, поэтому
    // указатель next настраиваем таким образом, чтобы он был пустым
    // который ранее был первым (на него указывает first)
    GetLast(firstItem)->next = temp;    // а теперь делаем, чтобы элемент, который до этого был последним
    // (а его мы получаем с помощью уже созданной GetLast)
    // ссылался на наш новый элемент
    return temp; // возвращаем указатель на последний элемент
}

bool SaveListToBinaryFile(ListUser* firstItem, const std::string& filename)
{
    if (firstItem == nullptr) return false;
    std::ofstream f(filename, std::ios::binary);
    if (!f) return false;
    auto temp = firstItem;
    while (temp != nullptr)
    {
        f.write((char*)temp, sizeof(ListUser));
        temp = temp->next;
    }
    bool result = f.good();
    f.close();
    return result;
}




void PrintUser(ListUser* item)
{
    setlocale(LC_ALL, "");
    if (item == nullptr) return; // проверяем корректность указателя
    cout << "Универсальный номер: " << item->login << endl; // далее выводим данные в консоль
    cout << "Название: " << item->password << endl;
    cout << endl;
}

void PrintListUser(ListUser* firstItem)
{
    std::cout << std::endl;
    auto temp = firstItem; // начинаем с первого элемента
    while (temp != nullptr) // перебираем весь список
    {
        PrintUser(temp); // печатаем очередной элемент ранее созданной функцией
        temp = temp->next; // перемещаемся к следующему элементу
    }
}

int main()
{
    ListUser* firstItemUser = nullptr;
    char login[20], password[20];
    cin >> login >> password;
    AddLast(firstItemUser, login, password);
    cin >> login >> password;
    AddLast(firstItemUser, login, password);
    SaveListToBinaryFile(firstItemUser, userFileName);
    cout << endl << endl << endl;
    PrintListUser(firstItemUser);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
