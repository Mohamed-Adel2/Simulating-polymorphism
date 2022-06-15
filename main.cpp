#include <iostream>

using namespace std;

//table that will store functions addresses
struct shapeVtable;

//act as base class
struct Shape
{
    //table that will store the addresses of the functions
    shapeVtable* table;
};

struct shapeVtable
{
    //pointer to the function that will calculate area of the shape and return the result
    double (*Area) (Shape*);
    //pointer to the function that will print info of the shape
    void (*Info) (Shape*);
};

//function that will return the value of shape`s area
double GetArea(Shape* s)
{
    //go to the pointer that points to the function that calculates the area and call that function
    return s->table->Area(s);
}

//function that will print the shape`s info
void PrintInfo(Shape* s)
{
    //go to the pointer that point to the function that print the shape`s info and call that function
    s->table->Info(s);
}

//derived type of shape
struct Circle
{
    Shape parent;//act as parent
    double* radius;
};

//function that has the logic of calculating circle`s area
double CircleArea(Circle* c)
{
    return 3.14*(c->(*radius))*(c->(*radius));
}

//function that has the logic of printing circle`s info
void CircleInfo(Circle* c)
{
    cout<<"Circle Radius = "<<c->*radius<<endl;
}

//the table that will store the circle functions` addresses
shapeVtable CircleTable
{
    //cast the pointers of circle`s functions to be compatible with shapeVtable pointers
    (double(*) (Shape*)) CircleArea,
    (void(*) (Shape*)) CircleInfo
};

//function that will initialize the circle object
void CircleInitialize(Circle* c,double r)
{
    //make the parent`s table points to CircleTable that has the addresses of Circle functions
    c->parent.table=&CircleTable;
    c->*radius=new double(r);
}

//derived type of shape
struct Rectangle
{
    Shape parent;//act as parent of the Rectangle
    double length,width;
};

//function that has the logic of calculating Rectangle`s area
double RectangleArea(Rectangle* r)
{
    return r->length*r->width;
}

//function that has the logic of printing Rectangle`s info
void RectangleInfo(Rectangle* r)
{
    cout<<"Rectangle Length = "<<r->length<<", Rectangle Width ="<<r->width<<endl;
}

//the table that will store the rectangle functions` addresses
shapeVtable RectangleTable
{
    //cast the pointers of Rectangle`s functions to be compatible with shapeVtable pointers
    (double(*) (Shape*)) RectangleArea,
    (void(*) (Shape*)) RectangleInfo
};

//function that will initialize the Rectangle object
void RectangleInitialize(Rectangle* r,double l,double w)
{
    //make the parent`s table points to RectangleTable that has the addresses of Rectangle functions
    r->parent.table=&RectangleTable;
    r->length=l;
    r->width=w;
}

//derived type of shape
struct Ellipse
{
    Shape parent;//act as parent of ellipse
    double radius1,radius2;
};

//function that has the logic of calculating Ellipse`s area
double EllipseArea(Ellipse* e)
{
    return 3.14*e->radius1*e->radius2;
}

//function that has the logic of printing Ellipse`s info
void EllipseInfo(Ellipse* e)
{
    cout<<"Ellipse first Radius = "<<e->radius1<<", Ellipse second Radius ="<<e->radius2<<endl;
}

//the table that will store the Ellipse functions` addresses
shapeVtable EllipseTable
{
    //cast the pointers of Ellipse`s functions to be compatible with shapeVtable pointers
    (double(*) (Shape*)) EllipseArea,
    (void(*) (Shape*)) EllipseInfo
};

//function that will initialize the Ellipse object
void EllipseInitialize(Ellipse* e,double r1,double r2)
{
    //make the ellipse parent`s table points to EllipseTable that has the addresses of Ellipse functions
    e->parent.table=&EllipseTable;
    e->radius1=r1;
    e->radius2=r2;
}

int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10
    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5
    Ellipse ellipse;
    EllipseInitialize(&ellipse, 10, 12); // ellipse with radius 10, 12
    Shape* shapes[3];
    shapes[0]=(Shape*)&circle ;//make shapes[0] points to circle`s parent
    shapes[1]=(Shape*)&rectangle ;//make shapes[1] points to rectangle`s parent
    shapes[2]=(Shape*)&ellipse ;//make shapes[2] points to ellipse`s parent
    double total_area=0;//will store the sum of areas of the 3 shapes
    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);//get the area of the shape and store it in var d
        total_area+=d;
        PrintInfo(shapes[i]); // prints the radius if circle, width and height if rectangle, ... etc
    }

    cout<<total_area<<endl; // check if the value is correct
    return 0;
}
