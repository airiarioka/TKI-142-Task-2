#include "../include/Point.h"

#include <stdexcept>
#include <limits>
#include <exception>
#include <iostream>

void Point::CheckPoint(void) const
{
    /**
    * @brief Широта в десятичных градусах.
    */
    double lat = latitude.ToDegrees();

    /**
    * @brief Долгота в десятичных градусах.
    */
    double lon = longitude.ToDegrees();

    if (lat < -90.0 - numeric_limits<double>::epsilon() || lat > 90.0 + numeric_limits<double>::epsilon())
    {
        throw out_of_range("Широта должна быть от -90 до 90 градусов.");
    }

    if (lon < -180.0 - numeric_limits<double>::epsilon() || lon > 180.0 + numeric_limits<double>::epsilon())
    {
        throw out_of_range("Долгота должна быть от -180 до 180 градусов.");
    }
}

Point::Point(const Angle latitude, const Angle longitude)
{
    this->latitude = latitude;
    this->longitude = longitude;
    CheckPoint();
}

Point::Point(const double latitude, const double longitude)
{
    this->latitude = Angle::FromDegrees(latitude);
    this->longitude = Angle::FromDegrees(longitude);
    CheckPoint();
}

Angle Point::getLatitude(void) const
{
    return latitude;
}

Angle Point::getLongitude(void) const
{
    return longitude;
}

bool Point::operator == (const Point& other) const
{
    return latitude == other.latitude && longitude == other.longitude;
}

bool Point::operator != (const Point& other) const
{
    return !(*this == other);
}

ostream& operator << (ostream& output, const Point& point)
{
    output << point.latitude.ToDegrees() << ' ' << point.longitude.ToDegrees();
    return output;
}

istream& operator >> (istream& input, Point& point)
{
    double latitude;
    double longitude;
    input >> latitude >> longitude;

    if (input.fail())
    {
        return input;
    }

    try
    {
        point = Point(latitude, longitude);
    }
    catch (const exception& error)
    {
        cerr << "Ошибка: " << error.what() << endl;
        input.setstate(ios::failbit);
    }

    return input;
}
