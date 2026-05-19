#include "../include/ArcLength.h"

#include <iostream>
#include <cstdlib>

using namespace std;

/**
* @brief Считывает дугу с проверкой ввода.
* @return Считанное значение.
*/
ArcLength getArc()
{
    ArcLength arc;
    cin >> arc;

    if (cin.fail())
    {
        cerr << "Ошибка ввода дуги." << endl;
        exit(1);
    }

    return arc;
}

/**
* @brief Основной код программы.
* @return 0, если программа завершилась успешно, иначе 1
*/
int main()
{
    system("chcp 65001");

    cout << "Задайте дугу: ";
    ArcLength arc = getArc();
    arc.ToString(cout);

    return 0;
}
