#pragma once

#include "Angle.h"

/**
* @brief Класс географическая точка.
* Класс хранит широту и долготу в виде объектов класса Angle.
*/
class Point
{
private:
    /**
    * @brief Географическая широта точки.
    */
    Angle latitude;

    /**
    * @brief Географическая долгота точки.
    */
    Angle longitude;

    /**
    * @brief Проверяет корректность широты и долготы.
    * @throw out_of_range если широта или долгота выходят за допустимый диапазон.
    */
    void CheckPoint(void) const;

public:
    /**
    * @brief Конструктор из двух углов.
    * @param latitude Широта точки.
    * @param longitude Долгота точки.
    * @throw out_of_range если координаты выходят за допустимый диапазон.
    */
    Point(const Angle latitude = Angle(), const Angle longitude = Angle());

    /**
    * @brief Конструктор из двух вещественных чисел.
    * @param latitude Широта в десятичных градусах.
    * @param longitude Долгота в десятичных градусах.
    * @throw out_of_range если координаты выходят за допустимый диапазон.
    */
    Point(const double latitude, const double longitude);

    /**
    * @brief Возвращает широту точки.
    * @return Объект Angle, содержащий широту.
    */
    Angle getLatitude(void) const;

    /**
    * @brief Возвращает долготу точки.
    * @return Объект Angle, содержащий долготу.
    */
    Angle getLongitude(void) const;

    /**
    * @brief Сравнивает две точки.
    * @param other Точка для сравнения.
    * @return true, если широты и долготы точек равны, иначе false.
    */
    bool operator == (const Point& other) const;

    /**
    * @brief Сравнивает две точки на неравенство.
    * @param other Точка для сравнения.
    * @return true, если точки не равны, иначе false.
    */
    bool operator != (const Point& other) const;

    /**
    * @brief Оператор вывода точки в поток.
    * Формат вывода: широта долгота.
    * @param output Поток вывода.
    * @param point Выводимая точка.
    * @return Ссылка на поток вывода.
    */
    friend ostream& operator << (ostream& output, const Point& point);

    /**
    * @brief Оператор ввода точки из потока.
    * Формат ввода: широта долгота.
    * @param input Поток ввода.
    * @param point Точка, в которую записываются считанные данные.
    * @return Ссылка на поток ввода.
    */
    friend istream& operator >> (istream& input, Point& point);
};
