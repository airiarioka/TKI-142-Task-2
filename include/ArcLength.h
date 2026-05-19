#pragma once

#include "Point.h"

/**
* @brief Класс "Длина дуги".
* Класс хранит две географические точки и рассчитывает
* расстояние между ними по дуге большого круга.
*/
class ArcLength
{
private:
    /**
    * @brief Первая географическая точка дуги.
    */
    Point firstPoint;

    /**
    * @brief Вторая географическая точка дуги.
    */
    Point secondPoint;

public:
    /**
    * @brief Конструктор из двух точек.
    * @param firstPoint Первая точка дуги.
    * @param secondPoint Вторая точка дуги.
    */
    ArcLength(const Point firstPoint = Point(), const Point secondPoint = Point());

    /**
    * @brief Конструктор из четырёх координат.
    * @param latitude1 Широта первой точки в десятичных градусах.
    * @param longitude1 Долгота первой точки в десятичных градусах.
    * @param latitude2 Широта второй точки в десятичных градусах.
    * @param longitude2 Долгота второй точки в десятичных градусах.
    * @throw out_of_range если координаты выходят за допустимые диапазоны.
    */
    ArcLength(const double latitude1, const double longitude1,
              const double latitude2, const double longitude2);

    /**
    * @brief Конструктор из четырёх углов.
    * @param latitude1 Широта первой точки.
    * @param longitude1 Долгота первой точки.
    * @param latitude2 Широта второй точки.
    * @param longitude2 Долгота второй точки.
    * @throw out_of_range если координаты выходят за допустимые диапазоны.
    */
    ArcLength(const Angle latitude1, const Angle longitude1,
              const Angle latitude2, const Angle longitude2);

    /**
    * @brief Возвращает первую точку дуги.
    * @return Первая точка дуги.
    */
    Point getFirstPoint(void) const;

    /**
    * @brief Возвращает вторую точку дуги.
    * @return Вторая точка дуги.
    */
    Point getSecondPoint(void) const;

    /**
    * @brief Рассчитывает длину дуги большого круга.
    * @param radius Радиус сферы в метрах. По умолчанию используется радиус Земли 6371000 м.
    * @return Длина дуги в метрах.
    * @throw invalid_argument если радиус отрицательный.
    */
    double getLength(const double radius = 6371000.0) const;

    /**
    * @brief Выводит информацию об объекте в поток.
    * @param output Поток вывода.
    */
    void ToString(ostream& output) const;

    /**
    * @brief Считывает дугу из потока ввода.
    * Формат ввода: широта1 долгота1 широта2 долгота2.
    * @param input Поток ввода.
    */
    void Read(istream& input);

    /**
    * @brief Оператор вывода дуги в поток.
    * @param output Поток вывода.
    * @param arc Выводимая дуга.
    * @return Ссылка на поток вывода.
    */
    friend ostream& operator << (ostream& output, const ArcLength& arc);

    /**
    * @brief Оператор ввода дуги из потока.
    * @param input Поток ввода.
    * @param arc Дуга, в которую записываются считанные данные.
    * @return Ссылка на поток ввода.
    */
    friend istream& operator >> (istream& input, ArcLength& arc);
};
