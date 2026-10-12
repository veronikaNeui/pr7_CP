// pr7_File.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Ticket 
{
    int id;
    string username;
    string title;
    string description;
    string priority;
    string status;

};

int main()
{
    setlocale(NULL, "Russian");

    Ticket tickets[100];
    int count = 0;
    string filename = "helpdesk.txt";


    try 
    {
        ifstream file(filename);

        if (!file.is_open())
        {
            cout << "Не удалось откртыть файл" << endl;
            return 1;

        }

        string id_str;
        while (getline(file, id_str, ';'))
        {
            if (count >= 100) break;

            if (id_str.empty() || id_str == "\n" || id_str == "\r\n") {
                continue;
            }

            if (!getline(file, tickets[count].username, ';')|| !getline(file,tickets[count].title,';') ||
                !getline(file, tickets[count].description, ';') || !getline(file, tickets[count].priority, ';') ||
                !getline(file, tickets[count].status, '\n'))

            {
                throw "Строка файла содержит недостаточное количество данных";
            }

            try 
            {
                tickets[count].id = stoi(id_str);
            }
            catch (...) 
            {
                throw "Числовое значение имеет некорректный формат";
            }

            if (tickets[count].id <= 0) 
            {
                throw "Числовое значение выходит за допустимые пределы";
            }


            count++;

        }
        file.close();

        cout << "Загружено записей: " << count << "\n";

    }
    catch (const char* error)
    {
        cout << "Критическая ошибка: " << error << endl;
        return 1;

    }

    int choice = 0;
    while (choice != 6) {
        cout << "\n1 - Поиск обращения по номеру\n2 - Поиск обращений пользователя\n3 - Фильтрация по приоритету\n4 - Вывод открытых обращений\n5 - Изменение статуса\n6 - Сохранение данных и выход\nВаш выбор: ";
        cin >> choice;
        cin.ignore();

        try
        {
            if (choice == 1) 
            {
                int searchId;
                cout << "Номер: ";
                cin >> searchId;

                bool found = false;
                for (int i = 0; i < count; i++) 
                {
                    if (tickets[i].id == searchId) 
                    {
                        cout << tickets[i].id << ";" << tickets[i].username << ";" << tickets[i].title << ";" << tickets[i].description << ";" << tickets[i].priority << ";" << tickets[i].status << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Не найдено\n";
            }
            else if (choice == 2)
            {
                string searchUser;
                cout << "Имя: ";
                getline(cin, searchUser);

                for (int i = 0; i < count; i++) 
                {
                    if (tickets[i].username == searchUser) 
                    {
                        cout << tickets[i].id << ";" << tickets[i].title << endl;
                    }
                }
            }
            else if (choice == 3)
            {
                string searchPriority;
                cout << "Приоритет: ";
                getline(cin, searchPriority);

                for (int i = 0; i < count; i++)
                {
                    if (tickets[i].priority == searchPriority) 
                    {
                        cout << tickets[i].id << ";" << tickets[i].username << ";" << tickets[i].title << endl;
                    }
                }
            }
            else if (choice == 4) 
            {
                for (int i = 0; i < count; i++) 
                {
                    if (tickets[i].status == "Open") 
                    {
                        cout << tickets[i].id << ";" << tickets[i].username << ";" << tickets[i].title << endl;
                    }
                }
            }
            else if (choice == 5) 
            {
                int editId;
                cout << "Номер обращения: ";
                cin >> editId;
                cin.ignore();

                bool found = false;
                for (int i = 0; i < count; i++) 
                {
                    if (tickets[i].id == editId) 
                    {
                        found = true;
                        if (tickets[i].status == "Closed") 
                        {
                            throw "Выполняемая операция невозможна по состоянию объекта";
                        }
                        cout << "Новый статус: ";
                        getline(cin, tickets[i].status);
                        break;
                    }
                }
                if (!found) cout << "Не найдено\n";
            }
            else if (choice == 6) 
            {
                ofstream out(filename);
                if (!out.is_open()) 
                {
                    throw "Файл не существует или не открывается";
                }

                for (int i = 0; i < count; i++) 
                {
                    out << tickets[i].id << ";" << tickets[i].username << ";" << tickets[i].title << ";" << tickets[i].description << ";" << tickets[i].priority << ";" << tickets[i].status << "\n";
                }
                out.close();
            }
        }
        catch (const char* error)
        {
            cout << "Ошибка: " << error << endl;
        }


    }




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
