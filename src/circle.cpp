/**
 * Circle shape
 * @author Jeff Stubler
 * @date 19 January 2012
 */

#include "circle.h"
#include <cmath>

/**
 * Circle constructor
 * @param location Circle center
 * @param radius Circle radius
 * @param color Circle border color
 */
Circle::Circle(const real_point location, const double radius,
        const unsigned int color) : Shape(location), radius(radius) {
}

/**
 * Copy constructor
 * @param right Circle to copy from
 */
Circle::Circle(const Circle& right) {
    location = right.location;
    color = right.color;
    radius = right.radius;
}

/**
 * Empty destructor
 */
Circle::~Circle(void) {
}

/**
 * Assignment operator
 * @param right Circle to assign from
 * @return Reference to this circle
 */
Circle& Circle::operator=(const Circle& right) {
    Circle::operator=(right);
    radius = right.radius;
    return *this;
}

/**
 * Draw circle with graphics context
 * @param gc Pointer to graphics context to draw with
 */
void Circle::draw(GraphicsContext *gc) const {
    real_point origin;
    origin.x = 0;
    origin.y = 0;
    Circle::draw(gc, origin);
}

void Circle::draw(GraphicsContext *gc, real_point offset) const {
    gc->setColor(color);
    double safe_radius = radius >= 0 ? radius : 0;
    gc->mDrawCircle((int) floor(location.x + offset.x + 0.5),
                    (int) floor(location.y + offset.y + 0.5), floor(safe_radius + 0.5));
}

/**
 * Dump circle to output stream
 * @param os Output stream to dump to
 */
void Circle::out(std::ostream& os) const {
    Shape::out(os);
    os.write(reinterpret_cast<const char *> (&radius), sizeof(radius));
}

/**
 * Restore circle from input stream
 * @param is Input stream to restore from
 */
void Circle::in(std::istream& is) {
    Shape::in(is);
    is.read(reinterpret_cast<char *> (&radius), sizeof(radius));
}

/**
 * Clone this object
 * @return Pointer to cloned instance of this circle
 */
Circle *Circle::clone(void) const {
    return new Circle(*this);
}

/**
 * Emit type code for saving image
 * @return Type code
 */
int Circle::get_code(void) const {
    return 3;
}