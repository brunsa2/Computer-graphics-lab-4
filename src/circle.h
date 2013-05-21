/**
 * Circle shape
 * @author Jeff Stubler
 * @date 19 January 2012
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include "gcontext.h"

class Circle : public Shape {
public:
    Circle(const real_point location, const double radius,
          const unsigned int color = GraphicsContext::WHITE);
    Circle(const Circle& right);
    ~Circle(void);
    Circle& operator=(const Circle& right);
    void draw(GraphicsContext *gc) const;
    void draw(GraphicsContext *gc, real_point offset) const;
    void out(std::ostream& os) const;
    void in(std::istream& is);
    Circle *clone(void) const;
    int get_code(void) const;
private:
    double radius;
};

#endif