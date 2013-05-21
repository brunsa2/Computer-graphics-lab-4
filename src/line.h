/**
 * Line class that daws a line
 * @author Jeff Stubler
 * @date 19 January 2012
 */

#ifndef LINE_H
#define LINE_H

#include "shape.h"
#include "gcontext.h"

class Line: public Shape {
public:
    Line(const real_point location, const real_point to_location,
          const unsigned int color = GraphicsContext::WHITE);
    Line(const Line& right);
    ~Line(void);
    real_point get_to_location(void) const;
    void set_to_location(const real_point to_location);
    Line& operator=(const Line& right);
    void draw(GraphicsContext *gc) const;
    void draw(GraphicsContext *gc, real_point offset) const;
    void out(std::ostream& os) const;
    void in(std::istream& is);
    Line *clone(void) const;
    int get_code(void) const;
private:
    real_point to_location;
};

#endif