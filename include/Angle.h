#pragma once

#include <iostream>

using namespace std;

/**
* @brief Класс "Угловая мера".
* Класс хранит угол в виде градусов, минут и секунд.
* Знак угла хранится отдельно.
*/
class Angle
{
private:
    /**
    * @brief Признак отрицательного угла.
    * true означает, что угол меньше нуля.
    * false означает, что угол больше или равен нулю.
    */
    bool negative;

    /**
    * @brief Целое количество градусов.
    */
    int degrees;

    /**
    * @brief Целое количество минут.
    */
    int minutes;

    /**
    * @brief Количество секунд.
    */
    double seconds;

    /**
    * @brief Проверяет корректность минут и секунд.
    * @throw invalid_argument если минуты или секунды заданы неверно.
    */
    void CheckAngle(void) const;

public:
    /**
    * @brief Конструктор из полного количества угловых секунд.
    * @param totalSeconds Полная величина угла в угловых секундах.
    * @throw invalid_argument если значение не является конечным числом.
    */
    Angle(const double totalSeconds = 0.0);

    /**
    * @brief Конструктор из градусов, минут и секунд.
    * @param degrees Количество градусов.
    * @param minutes Количество минут. Должно быть от 0 до 59.
    * @param seconds Количество секунд. Должно быть от 0 до значения меньше 60.
    * @throw invalid_argument если минуты или секунды заданы неверно.
    */
    Angle(const int degrees, const int minutes, const double seconds);

    /**
    * @brief Создаёт угол из десятичных градусов.
    * @param decimalDegrees Величина угла в десятичных градусах.
    * @return Объект класса Angle.
    */
    static Angle FromDegrees(const double decimalDegrees);

    /**
    * @brief Возвращает градусы с учётом знака.
    * @return Количество градусов.
    */
    int getDegrees(void) const;

    /**
    * @brief Возвращает минуты.
    * @return Количество минут.
    */
    int getMinutes(void) const;

    /**
    * @brief Возвращает секунды.
    * @return Количество секунд.
    */
    double getSeconds(void) const;

    /**
    * @brief Переводит угол в десятичные градусы.
    * @return Значение угла в десятичных градусах.
    */
    double ToDegrees(void) const;

    /**
    * @brief Переводит угол в радианы.
    * @return Значение угла в радианах.
    */
    double ToRadians(void) const;

    /**
    * @brief Сравнивает два угла на равенство.
    * @param other Угол для сравнения.
    * @return true, если углы равны с учётом погрешности, иначе false.
    */
    bool operator == (const Angle& other) const;

    /**
    * @brief Сравнивает два угла на неравенство.
    * @param other Угол для сравнения.
    * @return true, если углы не равны, иначе false.
    */
    bool operator != (const Angle& other) const;

    /**
    * @brief Оператор вывода угла.
    * @param output Поток вывода.
    * @param angle Выводимый угол.
    * @return Ссылка на поток вывода.
    */
    friend ostream& operator << (ostream& output, const Angle& angle);

    /**
    * @brief Оператор ввода угла.
    * @param input Поток ввода.
    * @param angle Угол, в который записываются считанные данные.
    * @return Ссылка на поток ввода.
    */
    friend istream& operator >> (istream& input, Angle& angle);
};
