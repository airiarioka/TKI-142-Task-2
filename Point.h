#pragma once 

/**
*@brief Класс точка.
*/
class Point
{
    private:
        /**
        *@brief Координата точки по x.
        */
        double x;
        /**
        *@brief Координата точки по y.
        */
        double y;

    public:
        /**
        *@brief Конструктор.
        *@param x Координата точки по x.
        *@param y Координата точки по y.
        */
        Point(const double x = 0, const double y = 0);
        /**
        *@brief Выбирает координату точки по x.
        *@return Возвращает координату точки по x.
        */
        double getX() const;
        /**
        *@brief Выбирает координату точки по y.
        *@return Возвращает координату точки по y.
        */
        double getY() const;
        /**
        *@brief Проверяет две точки на совпадение.
        *@param p_1 Первая точка.
        *@param p_2 Вторая точка.
        *@return True если равны, иначе false.
        */
        bool same(Point p_1,Point p_2);
};
