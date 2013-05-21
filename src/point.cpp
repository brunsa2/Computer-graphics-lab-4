/**
 * Point class that daws one pixel
 * @author Jeff Stubler
 * @date 19 January 2012
 */

#include "point.h"
#include <cmath>

/**
 * Default constructor
 * @param location Point location
 * @param color Point color
 */
Point::Point(const real_point location, const unsigned int color) :
        Shape(location, color) {
}

/** 
 * Copy constructor
 * @param right Point to copy from
 */
Point::Point(const Point& right) {
    location = right.location;
    color = right.color;
}

/**
 * Empty destructor
 */
Point::~Point(void) {
}

/**
 * Assignment operator
 * @param right Point to assign from
 * @retrun Reference to this object
 */
Point& Point::operator=(const Point& right) {
    Shape::operator=(right);
    return *this;
}

/**
 * Draws the point
 * @param gc Graphics context pointer to draw with
 */
void Point::draw(GraphicsContext *gc) const {
    real_point origin;
    origin.x = 0;
    origin.y = 0;
    Point::draw(gc, origin);
}

void Point::draw(GraphicsContext *gc, real_point offset) const {
    gc->setColor(color);
    gc->setPixel((int) floor(location.x + offset.x + 0.5), (int) floor(location.y + offset.y + 0.5));
}

/**
 * Dump point to output stream
 * @param os Output stream to dump to
 */
void Point::out(std::ostream& os) const {
    Shape::out(os);
}

/**
 * Restore point from dump
 * @param is Input stream to restore from
 */
void Point::in(std::istream& is) {
    Shape::in(is);
}

/**
 * Clone this object and return it
 * @return Pointer to new point object
 */
Point *Point::clone(void) const {
    return new Point(*this);
}

/**
 * Emit type code for saving image
 * @return Type code
 */
int Point::get_code(void) const {
    return 1;
}