#pragma once
#include "Point.h"

/**
*@brief Класс треугольник.
*/
class Triangle
{
    private:
        /**
        *@brief Первая точка.
        */
        Point a;
        /**
        *@brief Первая точка.
        */
        Point b;
        /**
        *@brief Первая точка.
        */
        Point c;
        /**
        *@brief Первая сторона треугольника.
        */
        double AB;
        /**
        *@brief Вторая сторона треугольника.
        */
        double BC;
        /**
        *@brief Третья сторона треугольника.
        */
        double AC;
        /**
        *@brief Вычисляет сторону треугольника по двум точкам.
        *@param p1 Первая точка.
        *@param p2 Вторая точка.
        *@return Рассчитанное значение длины.
        */
        double getSide(const Point p1, const Point p2);

    public:
        /**
        *@brief Конструктор.
        *@param side1 Первая сторона треугольника.
        *@param side2 Вторая сторона треугольника.
        *@param side3 Третья сторона треугольника.
        */
        Triangle(const Point& p1, const Point& p2, const Point& p3);
        /**
        *@brief Вычисляет радиус вписанной окружности.
        */
        double getR_inTriangle();
        /**
        *@brief Вычисляет радиус описанной окружности.
        */
        double getR_aroundTriangle();
};
