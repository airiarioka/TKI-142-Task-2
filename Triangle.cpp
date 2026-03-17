#include "Point.h"
#include "Triangle.h"
#include <iostream> 
#include <cmath>

using namespace std;

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3)
{
    a=Point(p1.getX(),p1.getY());
    b=Point(p2.getX(),p2.getY());
    c=Point(p3.getX(),p3.getY());

    AB=getSide(a,b);
    BC=getSide(b,c);
    AC=getSide(a,c);
    if ( (( (p3.getX()-p1.getX())/(p2.getX()-p1.getX()) ) == ( (p3.getY()-p1.getY())/(p2.getY()-p1.getY()) ) || same(p1,p2)||same(p1,p3) || same(p2,p3) ) || (AB<=0||BC<=0||AC<=0||AB>=BC+AC||BC>=AB+AC||AC>=AB+BC))
    {
        cout<<"Error 2\n";
        exit(1);
    }
}

double Triangle::getSide(const Point p1, const Point p2)
{
    return sqrt(pow(p1.getX()-p2.getX(),2)+pow(p1.getY()-p2.getY(),2));
}

double Triangle::getR_inTriangle()
{
    double p=(AB+BC+AC)/2;
    double s=sqrt(p*(p-AB)*(p-BC)*(p-AC));
    return s/p;
}

double Triangle::getR_aroundTriangle()
{
    double p=(AB+BC+AC)/2;
    double s=sqrt(p*(p-AB)*(p-BC)*(p-AC));
    return (AB*BC*AC)/(4*s);
}
