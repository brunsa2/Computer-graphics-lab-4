/**
 * Shape class that roots a drawable shape with location and color
 * @author Jeff Stubler
 * @date 19 January 2012
 */

#include "shape.h"

/**
 * Empty constructor for copying
 */
Shape::Shape(void) {
}

/**
 * Default constructor
 * @param location Location point
 * @param color Shape color
 */
Shape::Shape(const real_point location, const unsigned int color):
        location(location), color(color) {
}

/**
 * Copy constructor
 * @right Instance to copy from
 */
Shape::Shape(const Shape& right) {
    location = right.location;
    color = right.color;
}

/**
 * Empty destructor in case it's needed
 */
Shape::~Shape(void) {
}

/**
 * Color accessor
 * @return Shape color
 */
unsigned int Shape::get_color(void) const {
    return color;
}

/**
 * Color mutator
 * @param color Shape color
 */
void Shape::set_color(const unsigned int color) {
    this->color = color;
}

/**
 * Location accessor
 * @return Shape location
 */
real_point Shape::get_location(void) const {
    return location;
}

/**
 * Location mutator
 * @param location Shape location
 */
void Shape::set_location(const real_point location) {
    this->location = location;
}

/**
 * Dump shape properties to output stream
 * @param os Output stream to dump to
 */
void Shape::out(std::ostream& os) const {
    os.write(reinterpret_cast<const char *> (&location), sizeof(location));
    os.write(reinterpret_cast<const char *> (&color), sizeof(color));
}

/**
 * Restore shape from dump from input stream
 * @param is Input stream to restore from
 */
void Shape::in(std::istream& is) {
    is.read(reinterpret_cast<char *> (&location), sizeof(location));
    is.read(reinterpret_cast<char *> (&color), sizeof(color));
}

/**
 * Assign this shape to another
 * @param right Shape to copy attributes from
 * @return Reference to this object
 */
Shape& Shape::operator=(const Shape& right) {
    location = right.location;
    color = right.color;
    return *this;
}

/**
 * In operator
 * @param is Input stream
 */
std::istream& operator>>(std::istream& is, Shape& shape) {
    shape.in(is);
    return is;
}

/**
 * Out operator
 * @param os Output stream
 */
std::ostream& operator<<(std::ostream& os, const Shape& shape) {
    shape.out(os);
    return os;
}

/**
 * In operator
 * @param is Input stream
 */
std::istream& operator>>(std::istream& is, Shape *shape) {
    shape->in(is);
    return is;
}

/**
 * Out operator
 * @param os Output stream
 */
std::ostream& operator<<(std::ostream& os, const Shape *shape) {
    shape->out(os);
    return os;
}