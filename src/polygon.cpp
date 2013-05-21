/**
 * Polygon shape
 * @author Jeff Stubler
 * @date 19 January 2012
 */

#include "polygon.h"
#include <cmath>

/**
 * Main constructor that takes the first point
 * @param location First point
 * @param color Border color
 */
Polygon::Polygon(const real_point location, const unsigned int color) :
        Shape(location, color) {
}

/**
 * Copy constructor
 * @param right Polygon to copy from
 */
Polygon::Polygon(const Polygon& right) {
    location = right.location;
    color = right.color;
    locations = right.locations;
}

/**
 * Empty destructor
 */
Polygon::~Polygon(void) {
}

/**
 * Assignment operator
 * @param right Polygon to copy from
 * @returns Reference to this polygon
 */
Polygon& Polygon::operator=(const Polygon& right) {
    Polygon::operator=(right);
    locations = right.locations;
    return *this;
}

/**
 * Add a point to the end of the points list of the polygon
 * @param point Point to add to the points list
 */
void Polygon::add_point(const real_point point) {
    locations.push_back(point);
}

/**
 * Clear all of the points except the original point from the polygon
 */
void Polygon::clear_points(void) {
    locations.clear();
}

/**
 * Draws the polygon with a graphics context (if there is only one point nothing
 * will be drawn)
 * @param gc Pointer to graphics context to draw the polygon with
 */
void Polygon::draw(GraphicsContext *gc) const {
    real_point origin;
    origin.x = 0;
    origin.y = 0;
    Polygon::draw(gc, origin);
}

void Polygon::draw(GraphicsContext *gc, real_point offset) const {
    gc->setColor(color);
    if (locations.size() > 0) {
        int x1, x2, y1, y2;
        
        x1 = (int) floor(location.x + offset.x + 0.5);
        y1 = (int) floor(location.y + offset.y + 0.5);
        x2 = (int) floor(locations[0].x + offset.x + 0.5);
        y2 = (int) floor(locations[0].y + offset.y + 0.5);
        gc->bDrawLine(x1, y1, x2, y2);
        
        for (unsigned int point_index = 0; point_index < locations.size() - 1;
             point_index++) {
            x1 = (int) floor(locations[point_index].x + offset.x + 0.5);
            y1 = (int) floor(locations[point_index].y + offset.y + 0.5);
            x2 = (int) floor(locations[point_index + 1].x + offset.x + 0.5);
            y2 = (int) floor(locations[point_index + 1].y + offset.y + 0.5);
            gc->bDrawLine(x1, y1, x2, y2);
        }
        
        x1 = (int) floor(locations[locations.size() - 1].x + offset.x + 0.5);
        y1 = (int) floor(locations[locations.size() - 1].y + offset.y + 0.5);
        x2 = (int) floor(location.x + offset.x + 0.5);
        y2 = (int) floor(location.y + offset.y + 0.5);
        gc->bDrawLine(x1, y1, x2, y2);
    }
}

/**
 * Dump polygon to output stream
 * @param os Output stream to dump to
 */
void Polygon::out(std::ostream& os) const {
    Shape::out(os);
    unsigned int point_count = locations.size();
    os.write(reinterpret_cast<const char *> (&point_count),
            sizeof(point_count));
    for (unsigned int point_index = 0; point_index < locations.size();
            point_index++) {
        os.write(reinterpret_cast<const char *> (&(locations[point_index])),
                sizeof(locations[point_index]));
    }
}

/**
 * Restore polygon from input stream
 * @param is Input stream to restore from
 */
void Polygon::in(std::istream& is) {
    Shape::in(is);
    unsigned int point_count;
    is.read(reinterpret_cast<char *> (&point_count), sizeof(point_count));
    locations.clear();
    for(unsigned int point_index = 0; point_index < point_count;
            point_index++) {
        real_point point;
        is.read(reinterpret_cast<char *> (&point), sizeof(point));
        locations.push_back(point);
    }
}

/**
 * Clone this polygon
 * @returns Pointer to clone of this polygon
 */
Polygon *Polygon::clone(void) const {
    return new Polygon(*this);
}

/**
 * Emit type code for saving image
 * @return Type code
 */
int Polygon::get_code(void) const {
    return 5;
}