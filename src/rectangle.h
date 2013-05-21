/**
 * Rectangle shape
 * @author Jeff Stubler
 * @date 19 January 2012
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"
#include "gcontext.h"

class Rectangle : public Shape {
public:
    Rectangle(const real_point location, const real_point to_location,
            const unsigned int color = GraphicsContext::WHITE);
    Rectangle(const real_point location, const real_point location2,
            const real_point location3, const real_point location4,
            const unsigned int color = GraphicsContext::WHITE);
    Rectangle(const Rectangle& right);
    ~Rectangle(void);
    Rectangle& operator=(const Rectangle& right);
    void draw(GraphicsContext *gc) const;
    void draw(GraphicsContext *gc, real_point offset) const;
    void out(std::ostream& os) const;
    void in(std::istream& is);
    Rectangle *clone(void) const;
    int get_code(void) const;
private:
    real_point location2, location3, location4;
};

#endif