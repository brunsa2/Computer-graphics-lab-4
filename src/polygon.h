/**
 * Polygon shape
 * @author Jeff Stubler
 * @date 19 January 2012
 */

#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "shape.h"
#include "gcontext.h"

using namespace std;

class Polygon : public Shape {
public:
    Polygon(const real_point location,
            const unsigned int color = GraphicsContext::WHITE);
    Polygon(const Polygon& right);
    ~Polygon(void);
    Polygon& operator=(const Polygon& right);
    void add_point(const real_point point);
    void clear_points(void);
    void draw(GraphicsContext *gc) const;
    void draw(GraphicsContext *gc, real_point offset) const;
    void out(std::ostream& os) const;
    void in(std::istream& is);
    Polygon *clone(void) const;
    int get_code(void) const;
private:
    vector<real_point> locations;
};

#endif