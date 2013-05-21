/**
 * Image class that stores multiple shapes (including images)
 * @author Jeff Stubler
 * @date 9 February 2013
 */

#ifndef IMAGE_H
#define IMAGE_H

#include "shape.h"
#include "gcontext.h"
#include <iostream>
#include <list>

#define POINT 1
#define LINE 2
#define CIRCLE 3
#define RECTANGLE 4
#define POLYGON 5
#define IMAGE 6

using namespace std;

class Image: public Shape {
public:
    Image(void);
    Image(const real_point location);
    Image(const Image& right);
    ~Image();
    Image& operator=(const Image& right);
    void draw(GraphicsContext *gc) const;
    void draw(GraphicsContext *gc, real_point offset) const;
    void out(std::ostream& os) const;
    void in(std::istream& is);
    Image *clone(void) const;
    void add(Shape* shape);
    void erase(void);
    int get_code(void) const;
    void set_name(string new_name);
    string get_name(void) const;
    int size(void) const;
private:
    string name;
    list<Shape *> shapes;
};

#endif