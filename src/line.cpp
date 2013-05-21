/**
 * Line class that daws a line
 * @author Jeff Stubler
 * @date 19 January 2012
 */

#include "line.h"
#include <cmath>

/**
 * Constructor for line
 * @param location Start location for line
 * @param to_location End point
 * @param color Line color
 */
Line::Line(const real_point location, const real_point to_location,
        const unsigned int color) : Shape(location, color),
        to_location(to_location) {
}

/**
 * Copy constructor
 * @param right Line to copy
 */
Line::Line(const Line& right) {
    location = right.location;
    to_location = right.to_location;
    color = right.color;
}

/**
 * Empty destructor
 */
Line::~Line(void) {
}

/**
 * Assignment operator
 * @param right Line to assign from
 * @return Reference to this line
 */
Line& Line::operator=(const Line& right) {
    Shape::operator=(right);
    to_location = right.to_location;
    return *this;
}

/**
 * Draws the line
 * @param gc Graphics context pointer to draw the line with
 */
void Line::draw(GraphicsContext *gc) const {
    real_point origin;
    origin.x = 0;
    origin.y = 0;
    Line::draw(gc, origin);
}

void Line::draw(GraphicsContext *gc, real_point offset) const {
    gc->setColor(color);
    gc->bDrawLine((int) floor(location.x + offset.x + 0.5), (int) floor(location.y + offset.y + 0.5),
                  (int) floor(to_location.x + offset.x + 0.5), (int) floor(to_location.y + offset.y + 0.5));
}

/**
 * Dumps the line to an output stream
 * @param os Output stream to dump line to
 */
void Line::out(std::ostream& os) const {
    Shape::out(os);
    os.write(reinterpret_cast<const char *> (&to_location),
            sizeof(to_location));
}

/**
 * Restores a line from an output stream
 * @param is Input stream to restore from
 */
void Line::in(std::istream& is) {
    Shape::in(is);
    is.read(reinterpret_cast<char *> (&to_location), sizeof(to_location));
}

// Attempt at clone method
Line *Line::clone(void) const {
    return new Line(*this);
}

/**
 * Emit type code for saving image
 * @return Type code
 */
int Line::get_code(void) const {
    return 2;
}