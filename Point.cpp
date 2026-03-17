#include "Point.h"
#include <limits>
#include <cmath>

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

bool same(Point p_1,Point p_2)
{
    return fabs(p_1.getX()-p_2.getX()) < std::numeric_limits<double>::epsilon() & fabs(p_1.getY()-p_2.getY()) < std::numeric_limits<double>::epsilon();
}
