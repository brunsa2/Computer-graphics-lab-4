/**
 * Image class that stores multiple shapes (including images)
 * @author Jeff Stubler
 * @date 9 February 2013
 */

#include "image.h"
#include "point.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include "polygon.h"
#include <cmath>

using namespace std;

Image::Image(void) {
    real_point origin;
    origin.x = 0;
    origin.y = 0;
    location = origin;
    name = "";
    shapes = list<Shape *>();
}

Image::Image(const real_point location) : Shape(location, 0) {
    name = "";
    shapes = list<Shape *>();
}

Image::Image(const Image& right) {
    location = right.location;
    color = right.color;
    name = right.name;
    shapes = right.shapes;
}

Image::~Image() {
}

Image& Image::operator=(const Image& right) {
    Shape::operator=(right);
    shapes = right.shapes;
    name = right.name;
    return *this;
}

void Image::draw(GraphicsContext *gc) const {
    for (list<Shape *>::const_iterator shapes_iterator = shapes.begin();
            shapes_iterator != shapes.end(); shapes_iterator++) {
        (*shapes_iterator)->draw(gc, location);
    }
}

void Image::draw(GraphicsContext *gc, real_point offset) const {
    offset.x += location.x;
    offset.y += location.y;
    for (list<Shape *>::const_iterator shapes_iterator = shapes.begin();
         shapes_iterator != shapes.end(); shapes_iterator++) {
        (*shapes_iterator)->draw(gc, offset);
    }
}

void Image::out(std::ostream& os) const {
    Shape::out(os);
    unsigned int name_length = name.length(), shape_count = shapes.size(), code;
    os.write(reinterpret_cast<const char *> (&name_length), sizeof(name_length));
    for (unsigned int char_index = 0; char_index < name.length(); char_index++) {
        char current_char = name[char_index];
        os.write(reinterpret_cast<const char *> (&current_char), sizeof(current_char));
    }
    os.write(reinterpret_cast<const char *> (&shape_count), sizeof(shape_count));
    for (list<Shape *>::const_iterator shapes_iterator = shapes.begin();
         shapes_iterator != shapes.end(); shapes_iterator++) {
        code = (*shapes_iterator)->get_code();
        os.write(reinterpret_cast<const char *> (&code), sizeof(code));
        (*shapes_iterator)->out(os);
    }
}

void Image::in(std::istream& is) {
    real_point null_point;
    null_point.x = 0;
    null_point.y = 0;
    
    Shape::in(is);
    unsigned int name_length, shape_count, code;
    is.read(reinterpret_cast<char *> (&name_length), sizeof(name_length));
    name = "";
    for (unsigned int char_index = 0; char_index < name_length; char_index++) {
        char current_char;
        is.read(reinterpret_cast<char *> (&current_char), sizeof(current_char));
        name += current_char;
    }
    is.read(reinterpret_cast<char *> (&shape_count), sizeof(shape_count));
    shapes.erase(shapes.begin(), shapes.end());
    for (unsigned int shape_index = 0; shape_index < shape_count; shape_index++) {
        is.read(reinterpret_cast<char *> (&code), sizeof(code));
        switch (code) {
            case POINT:
                {
                    Point *point = new Point(null_point);
                    is >> point;
                    Image::add(point);
                    delete point;
                }
                break;
                
            case LINE:
                {
                    Line *line = new Line(null_point, null_point);
                    is >> line;
                    Image::add(line);
                    delete line;
                }
                break;
                
            case CIRCLE:
                {
                    Circle *circle = new Circle(null_point, 0);
                    is >> circle;
                    Image::add(circle);
                    delete circle;
                }
                break;
                
            case RECTANGLE:
                {
                    Rectangle *rectangle = new Rectangle(null_point, null_point);
                    is >> rectangle;
                    Image::add(rectangle);
                    delete rectangle;
                }
                break;
                
            case POLYGON:
                {
                    Polygon *polygon = new Polygon(null_point);
                    is >> polygon;
                    Image::add(polygon);
                    delete polygon;
                }
                break;
                
            case IMAGE:
                {
                    Image *image = new Image();
                    is >> image;
                    Image::add(image);
                    delete image;
                }
                break;
        }
    }
}

Image *Image::clone(void) const {
    return new Image(*this);
}

void Image::add(Shape* shape) {
    shapes.push_back(shape->clone());
}

void Image::erase(void) {
    for (list<Shape *>::const_iterator shapes_iterator = shapes.begin();
         shapes_iterator != shapes.end(); shapes_iterator++) {
        delete *shapes_iterator;
    }
    shapes.erase(shapes.begin(), shapes.end());
}

int Image::get_code(void) const {
    return 6;
}

void Image::set_name(string new_name) {
    name = new_name;
}

/**
 * Emit type code for saving image
 * @return Type code
 */
string Image::get_name(void) const {
    return name;
}

int Image::size(void) const {
    return shapes.size();
}