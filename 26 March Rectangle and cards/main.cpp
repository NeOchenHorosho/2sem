#include <iostream>
#include <math.h>
using namespace std;

class MyRectangle
{
protected:
    int x1,x2,y1,y2;
public:
    MyRectangle(int _x1, int _x2, int _y1, int _y2): x1(_x1), x2(_x2), y1(_y1), y2(_y2) {}  
    virtual double area()
    {
        return abs((x1-x2)*(y1-y2));
    }
    virtual double perimeter()
    {
        return 2*(abs(x1-x2)+abs(y1-y2));
    }
};
class MyTriangle: public MyRectangle
{
public:
    MyTriangle(int _x1, int _x2, int _y1, int _y2) : MyRectangle(_x1, _x2, _y1, _y2) {}
    double area()
    {
        return MyRectangle::area()*0.5;
    }
    double perimeter()
    {
        return abs(x1-x2)+2*(sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)/4));
    }
};

class MyRhombus: public MyRectangle
{
public:
    MyRhombus(int _x1, int _x2, int _y1, int _y2) : MyRectangle(_x1, _x2, _y1, _y2) {}
    double area()
    {
        return MyRectangle::area()*0.5;
    }
    double perimeter()
    {
        return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)*2)*2;
    }
};

int main()
{
    MyRectangle a(0,2,0,3);
    cout << "\nrectangle area: " << a.area() << "\nrectangle perimeter: " << a.perimeter();
    MyTriangle b(0,2,0,3);
    cout << "\n\ntriangle area: " << b.area() << "\ntriangle perimeter: " << b.perimeter();
    MyRhombus c(0,2,0,3);
    cout << "\n\nRhombus area: " << c.area() << "\nRhombus perimeter: " << c.perimeter();
    MyRectangle& rb = b;
    cout << "\n\ntriangle of rectangle area: " << rb.area() << "\ntriangle of rectangle perimeter: " << rb.perimeter();
    MyRectangle* pc = &c;
    cout << "\n\nRhombus of rectangle area: " << pc->area() << "\nRhombus of rectangle perimeter: " << pc->perimeter();
    cout << "\n\nrectangle of rhombus area: " << c.MyRectangle::area() << "\nrectangle of rhombus perimeter: " << c.MyRectangle::perimeter();
}