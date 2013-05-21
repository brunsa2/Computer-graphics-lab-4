/**
 * Shape class that roots a drawable shape with location and color
 * @author Jeff Stubler
 * @date 19 January 2012
 */

#ifndef SHAPE_H
#define SHAPE_H

#include "gcontext.h"
#include <iostream>

typedef struct {
    double x;
    double y;
} real_point;

class Shape {
public:
    Shape(void);
    Shape(const real_point location,
            const unsigned int color = GraphicsContext::WHITE);
    Shape(const Shape& right);
    virtual ~Shape();
    unsigned int get_color(void) const;
    void set_color(const unsigned int color);
    real_point get_location(void) const;
    void set_location(const real_point location);
    virtual void draw(GraphicsContext *gc) const = 0;
    virtual void draw(GraphicsContext *gc, real_point offset) const = 0;
    virtual void out(std::ostream& os) const;
    virtual void in(std::istream& is);
    virtual Shape *clone(void) const = 0;
    virtual int get_code(void) const = 0;
protected:
    virtual Shape& operator=(const Shape& right);
    real_point location;
    unsigned int color;
};

std::istream& operator>>(std::istream& is, Shape& shape);
std::ostream& operator<<(std::ostream& os, const Shape& shape);
std::istream& operator>>(std::istream& is, Shape *shape);
std::ostream& operator<<(std::ostream& os, const Shape *shape);

#endif