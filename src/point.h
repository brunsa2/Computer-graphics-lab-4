/**
 * Point class that daws one pixel
 * @author Jeff Stubler
 * @date 19 January 2012
 */

#ifndef POINT_H
#define POINT_H

#include "shape.h"
#include "gcontext.h"

class Point: public Shape {
public:
    Point(const real_point location,
            const unsigned int color = GraphicsContext::WHITE);
    Point(const Point& right);
    ~Point(void);
    Point& operator=(const Point& right);
    void draw(GraphicsContext *gc) const;
    void draw(GraphicsContext *gc, real_point offset) const;
    void out(std::ostream& os) const;
    void in(std::istream& is);
    Point *clone(void) const;
    int get_code(void) const;
};

#endif