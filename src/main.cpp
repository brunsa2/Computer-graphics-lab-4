#include "x11context.h"
#include "shape.h"
#include "point.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include "polygon.h"
#include "image.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>

using namespace std;
 
int main(void)
{
	GraphicsContext *gc = new X11Context(800, 500, GraphicsContext::BLACK);
    
    real_point point1, line1, line2, circle1, rectangle1, rectangle2, polygon1, polygon2, polygon3, null_point, offset;
    
    point1.x = 25;
    point1.y = 25;
    
    line1.x = 50;
    line1.y = 25;
    line2.x = 75;
    line2.y = 200;
    
    circle1.x = 100;
    circle1.y = 100;
    
    rectangle1.x = 150;
    rectangle1.y = 50;
    rectangle2.x = 200;
    rectangle2.y = 100;
    
    polygon1.x = 250;
    polygon1.y = 50;
    polygon2.x = 300;
    polygon2.y = 50;
    polygon3.x = 250;
    polygon3.y = 200;
    
    null_point.x = 0;
    null_point.y = 0;
    
    offset.x = 50;
    offset.y = 50;
    
    Point *point = new Point(point1);
    Line *line = new Line(line1, line2);
    Circle *circle = new Circle(circle1, 25);
    Rectangle *rectangle = new Rectangle(rectangle1, rectangle2);
    Polygon *polygon = new Polygon(polygon1);
    polygon->add_point(polygon2);
    polygon->add_point(polygon3);
    
    Image *image = new Image(offset), *imagea, *image2 = new Image();
    Image *little_image = new Image(offset);
    image->add(point);
    imagea = image->clone();
    imagea->add(line);
    little_image->set_name("Little");
    little_image->add(circle);
    little_image->add(rectangle);
    little_image->add(polygon);
    imagea->add(little_image);
    imagea->set_name("Big");
    
    ofstream shapesout;
    shapesout.open("shapes.bin", ios::binary);
    shapesout << imagea;
    shapesout.close();
    
    delete point;
    delete line;
    delete circle;
    delete rectangle;
    delete polygon;
    image->erase();
    delete image;
    
    ifstream shapesin;
    shapesin.open("shapes.bin", ios::binary);
    shapesin >> image2;
    shapesin.close();
    
    image2->draw(gc);
    cout << "Image called " << image2->get_name() << " and has " << image2->size() << " shapes." << endl;
    image2->erase();
    
	getchar();
 
	delete gc;
 
	return 0;
}