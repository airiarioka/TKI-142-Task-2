#include <iostream>
#include "Triangle.h"
#include <string>

using namespace std;

/**
*@brief Считывает точку треугольника с клавиатуры с проверкой ввода.
*@param report строка информации.
*@return Считанное значение.
*/
Point getPoint(string report="");


/**
*@brief Точка входа в программу.
*@return 0, если программа выполнена корректно.
*/
int main()
{
    Point a=getPoint("First point: ");
    Point b=getPoint("Second point: ");
    Point c=getPoint("Third point: ");
    Triangle ABC(a,b,c);
    cout<<"R = "<<ABC.getR_aroundTriangle()<<endl;
    cout<<"r = "<<ABC.getR_inTriangle();

    return 0;
}

Point getPoint(string report)
{
    cout<<report<<endl;
    double p_x = 0;
    double p_y = 0;
    cin>>p_x;
    cin>>p_y;
    if(cin.fail())
    {
        cout<<"Error 1\n";
        exit(1);
    }
    return (p_x,p_y);
}
