#include "Point.h"

Point::Point(const double x, const double y): x(x),y(y)
{
}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}