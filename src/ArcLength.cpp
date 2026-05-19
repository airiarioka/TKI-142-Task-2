#include "../include/ArcLength.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <stdexcept>
#include <exception>

ArcLength::ArcLength(const Point firstPoint, const Point secondPoint)
{
    this->firstPoint = firstPoint;
    this->secondPoint = secondPoint;
}

ArcLength::ArcLength(const double latitude1, const double longitude1,
                     const double latitude2, const double longitude2)
{
    firstPoint = Point(latitude1, longitude1);
    secondPoint = Point(latitude2, longitude2);
}

ArcLength::ArcLength(const Angle latitude1, const Angle longitude1,
                     const Angle latitude2, const Angle longitude2)
{
    firstPoint = Point(latitude1, longitude1);
    secondPoint = Point(latitude2, longitude2);
}

Point ArcLength::getFirstPoint(void) const
{
    return firstPoint;
}

Point ArcLength::getSecondPoint(void) const
{
    return secondPoint;
}

double ArcLength::getLength(const double radius) const
{
    if (radius < 0)
    {
        throw invalid_argument("Радиус не должен быть отрицательным.");
    }

    /**
    * @brief Широта первой точки в радианах.
    */
    double lat1 = firstPoint.getLatitude().ToRadians();

    /**
    * @brief Долгота первой точки в радианах.
    */
    double lon1 = firstPoint.getLongitude().ToRadians();

    /**
    * @brief Широта второй точки в радианах.
    */
    double lat2 = secondPoint.getLatitude().ToRadians();

    /**
    * @brief Долгота второй точки в радианах.
    */
    double lon2 = secondPoint.getLongitude().ToRadians();

    /**
    * @brief Разность широт в радианах.
    */
    double dLat = lat2 - lat1;

    /**
    * @brief Разность долгот в радианах.
    */
    double dLon = lon2 - lon1;

    /**
    * @brief Промежуточное значение формулы гаверсинуса.
    */
    double a = pow(sin(dLat / 2.0), 2)
             + cos(lat1) * cos(lat2) * pow(sin(dLon / 2.0), 2);

    /**
    * @brief Ограничение значения в диапазоне [0; 1].
    */
    a = clamp(a, 0.0, 1.0);

    /**
    * @brief Центральный угол между точками в радианах.
    */
    double centralAngle = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));

    return radius * centralAngle;
}

void ArcLength::ToString(ostream& output) const
{
    output << "Информация о дуге:" << endl;
    output << "Первая точка: " << firstPoint << endl;
    output << "Вторая точка: " << secondPoint << endl;
    output << "Длина дуги: " << fixed << setprecision(3) << getLength() << " м" << endl;
}

void ArcLength::Read(istream& input)
{
    /**
    * @brief Считанная широта первой точки.
    */
    double latitude1;

    /**
    * @brief Считанная долгота первой точки.
    */
    double longitude1;

    /**
    * @brief Считанная широта второй точки.
    */
    double latitude2;

    /**
    * @brief Считанная долгота второй точки.
    */
    double longitude2;

    input >> latitude1 >> longitude1 >> latitude2 >> longitude2;
    if (input.fail())
    {
        return;
    }

    try
    {
        *this = ArcLength(latitude1, longitude1, latitude2, longitude2);
    }
    catch (const exception& error)
    {
        cerr << "Ошибка: " << error.what() << endl;
        input.setstate(ios::failbit);
    }
}

ostream& operator << (ostream& output, const ArcLength& arc)
{
    arc.ToString(output);

    return output;
}

istream& operator >> (istream& input, ArcLength& arc)
{
    arc.Read(input);
    return input;
}
