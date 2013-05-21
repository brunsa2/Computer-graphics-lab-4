/**
 * Rectangle shape
 * @author Jeff Stubler
 * @date 19 January 2012
 */

#include "rectangle.h"
#include <cmath>

/**
 * Constructor taking two corner points
 * @param location First location point
 * @param to_location Second location point
 * @param color Border color
 */
Rectangle::Rectangle(const real_point location, const real_point to_location,
        const unsigned int color) : Shape(location, color)
        {
    location2.x = to_location.x;
    location2.y = location.y;
    location3.x = to_location.x;
    location3.y = to_location.y;
    location4.x = location.x;
    location4.y = to_location.y;
}

/** 
 * Constructor for all four corners
 * @param location Point 1
 * @param location2 Point 2
 * @param location3 Point 3
 * @param location4 Point 4
 * @param color Border color
 */
Rectangle::Rectangle(const real_point location, const real_point location2,
        const real_point location3, const real_point location4,
        const unsigned int color) : Shape(location, color),
        location2(location2), location3(location3), location4(location4) {
}

/**
 * Copy constructor
 * @param right Rectange to copy from
 */
Rectangle::Rectangle(const Rectangle& right) {
    location = right.location;
    color = right.color;
    location2 = right.location2;
    location3 = right.location3;
    location4 = right.location4;
}

/**
 * Empty destructor
 */
Rectangle::~Rectangle(void) {
}

/**
 * Assignment operator
 * @param right Rectangle to assign from
 * @returns Reference to this rectangle
 */
Rectangle& Rectangle::operator=(const Rectangle& right) {
    Rectangle::operator=(right);
    location2 = right.location2;
    location3 = right.location3;
    location4 = right.location4;
    return *this;
}

/**
 * Draw this rectangle
 * @param gc Pointer to graphics context to draw with
 */
void Rectangle::draw(GraphicsContext *gc) const {
    real_point origin;
    origin.x = 0;
    origin.y = 0;
    Rectangle::draw(gc, origin);
}

void Rectangle::draw(GraphicsContext *gc, real_point offset) const {
    int x1 = (int) floor(location.x + offset.x + 0.5);
    int x2 = (int) floor(location2.x + offset.x + 0.5);
    int x3 = (int) floor(location3.x + offset.x + 0.5);
    int x4 = (int) floor(location4.x + offset.x + 0.5);
    int y1 = (int) floor(location.y + offset.y + 0.5);
    int y2 = (int) floor(location2.y + offset.y + 0.5);
    int y3 = (int) floor(location3.y + offset.y + 0.5);
    int y4 = (int) floor(location4.y + offset.y + 0.5);
    gc->setColor(color);
    gc->bDrawLine(x1, y1, x2, y2);
    gc->bDrawLine(x2, y2, x3, y3);
    gc->bDrawLine(x3, y3, x4, y4);
    gc->bDrawLine(x4, y4, x1, y1);
}

/**
 * Dump this rectangle to an output stream
 * @param os Output stream to dump to
 */
void Rectangle::out(std::ostream& os) const {
    Shape::out(os);
    os.write(reinterpret_cast<const char *> (&location2), sizeof(location2));
    os.write(reinterpret_cast<const char *> (&location3), sizeof(location3));
    os.write(reinterpret_cast<const char *> (&location4), sizeof(location4));
}

/**
 * Restore this rectangle from an input stream
 * @param is Input stream to restore from
 */
void Rectangle::in(std::istream& is) {
    Shape::in(is);
    is.read(reinterpret_cast<char *> (&location2), sizeof(location2));
    is.read(reinterpret_cast<char *> (&location3), sizeof(location3));
    is.read(reinterpret_cast<char *> (&location4), sizeof(location4));
}

/**
 * Clone this rectangle
 * @returns Pointer to clone of this rectangle
 */
Rectangle *Rectangle::clone(void) const {
    return new Rectangle(*this);
}

/**
 * Emit type code for saving image
 * @return Type code
 */
int Rectangle::get_code(void) const {
    return 4;
}