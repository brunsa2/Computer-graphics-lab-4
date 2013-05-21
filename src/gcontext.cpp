/* This is an abstract base class representing a generic graphics
 * context.  Most implementation specifics will need to be provided by
 * a concrete implementation.  See header file for specifics. */

#define _USE_MATH_DEFINES	// for M_PI
#include <cmath>	// for trig functions
#include <cstdlib>	// for int abs
#include "gcontext.h"	

#include <iostream>

#define FRAC_PART(x) (x - (long) x)
#define ONE_MINUS_FRAC_PART(x) (1 - (x - (long) x))

void swap(int &a, int &b) {
    int swapping_store = b;
    b = a;
    a = swapping_store;
}

void swap(double &a, double &b) {
    double swapping_store = b;
    b = a;
    a = swapping_store;
}

/*
 * Destructor - does nothing
 */
GraphicsContext::~GraphicsContext()
{
	// nothing to do
	// here to insure subclasses handle destruction properly
}


/* This is a naive implementation that uses floating-point math
 * and "setPixel" which will need to be provided by the concrete
 * implementation.
 * 
 * Parameters:
 * 	x0, y0 - origin of line
 *  x1, y1 - end of line
 * 
 * Returns: void
 */
void GraphicsContext::drawLine(int x0, int y0, int x1, int y1)
{
	
	// find slope
	int dx = x1-x0;
	int dy = y1-y0;
	
	// make sure we actually have a line
	if (dx != 0 || dy !=0)
	{
		// slope < 1?
		if (std::abs(dx)>std::abs(dy))
		{	// iterate over x
			double slope = (double)dy/dx;
			
			// x increment - need to know which way to go
			int incx = std::abs(dx)/dx;  // will be 1 or -1
			
			for (int x = x0; x != x1; x += incx)
			{
				setPixel(x,y0+slope*(x-x0));
			}
			
			// loop ends on iteration early - catch endpoint
			setPixel(x1,y1);
		} // end of if |slope| < 1 
		else 
		{	// iterate over y
			double islope = (double)dx/dy;
			
			// x increment - need to know which way to go
			int incy = std::abs(dy)/dy;  // will be 1 or -1
			
			for (int y = y0; y != y1; y += incy)
			{
				setPixel(x0+islope*(y-y0),y);
			}
			
			// loop ends on iteration early - catch endpoint
			setPixel(x1,y1);
		} // end of else |slope| >= 1
	} // end of if it is a real line (dx!=0 || dy !=0)
	return;
}

/**
 * Bresenham line algorithm implementation
 *
 * @param x0 Point 1 x coordinate
 * @param y0 Point 1 y coordinate
 * @param x1 Point 2 x coordinate
 * @param y1 Point 2 y coordinate
 */

void GraphicsContext::bDrawLine(int x0, int y0, int x1, int y1) {
    int current_x = x0, current_y = y0;
    int dx = x1 - x0, dy = y1 - y0;
    int distance_difference = 2 * dy - dx;
    int above_adjustment = 2 * dy;
    int below_adjustment = 2 * (dy - dx);
    int y_reflection_factor = 1;
    bool swap_coordinates = false;
    
    // If abs(slope) > 1, swap x and y (reflect across y=x)
    if (abs(dy) > abs(dx)) {
        swap(current_x, current_y);
        swap(x0, y0);
        swap(x1, y1);
        
        dx = x1 - x0; dy = y1 - y0;
        distance_difference = 2 * dy - dx;
        above_adjustment = 2 * dy;
        below_adjustment = 2 * (dy - dx);
        swap_coordinates = true;
    }
    
    // Make sure that x will traverse positively
    if(x1 < x0) {
        swap(x0, x1);
        swap(y0, y1);
        
        current_x = x0;
        current_y = y0;
        
        dx = x1 - x0; dy = y1 - y0;
        distance_difference = 2 * dy - dx;
        above_adjustment = 2 * dy;
        below_adjustment = 2 * (dy - dx);
    }
    
    // If slope < 1, reflect y across y=0 
    if (dy < 0) {
        current_y = -current_y;
        dy = -dy;
        y_reflection_factor = -y_reflection_factor;
        
        distance_difference = 2 * dy - dx;
        above_adjustment = 2 * dy;
        below_adjustment = 2 * (dy - dx);
    }
    
    // First point
    if (swap_coordinates) {
        setPixel(current_y, current_x);
    } else {
        setPixel(current_x, y_reflection_factor * current_y);
    }
    
    // Traverse the line
    if (swap_coordinates) {
        while (current_x < x1) {
            current_x++;
            if (distance_difference < 0) distance_difference += above_adjustment;
            else {
                current_y++;
                distance_difference += below_adjustment;
            }
            setPixel(y_reflection_factor * current_y, current_x);
        }
    } else {
        while (current_x < x1) {
            current_x++;
            if (distance_difference < 0) distance_difference += above_adjustment;
            else {
                current_y++;
                distance_difference += below_adjustment;
            }
            setPixel(current_x, y_reflection_factor * current_y);
        }
    }
}

/**
 * Xiaolin Wu's line algorithm implementation (based on implementation
 * at Wikipedia.org, http://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm retrieved 8 January 2012).
 * This implementation implements switching but still does not seem to work with
 * cases m > 1 or m = 1. m = 1 may not work at all with the algorithm because the
 * line directly coincides along the pixels without calculating for smoothing.
 *
 * @param x0 Point 1 x coordinate
 * @param y0 Point 1 y coordinate
 * @param x1 Point 2 x coordinate
 * @param y1 Point 2 y coordinate
 */

void GraphicsContext::xDrawLine(double x0, double y0, double x1, double y1) {
    bool swap_coordinates = false;
    double dx = x1 - x0, dy = y1 - y0;
    
    std::cerr << "Line from (" << x0 << ", " << y0 << ") to (" << x1 << ", " << y1 << ")" << std::endl;
    std::cerr << "dx = " << dx << ", dy = " << dy << std::endl;
    
    if (abs(dy) > abs(dx)) {
        swap(x0, y0);
        swap(x1, y1);
        
        dx = x1 - x0; dy = y1 - y0;
    }
    
    if(x1 < x0) {
        swap(x0, x1);
        swap(y0, y1);
        
        dx = x1 - x0; dy = y1 - y0;
    }
    
    if (!swap_coordinates) {
        double m = dy / (double) dx;

        int int_x0 = (int) floor(x0 + 0.5);
        double y0_end = y0 + m * (x0 - int_x0);
        double x0_gap = ONE_MINUS_FRAC_PART(x0 + 0.5);
        int floor_y0 = (int) floor(y0_end);
        setPixel(int_x0, floor_y0, ONE_MINUS_FRAC_PART(y0_end) * x0_gap);
        setPixel(int_x0, floor_y0 + 1, FRAC_PART(y0_end) * x0_gap);

        int int_x1 = (int) floor(x1 + 0.5);
        double y1_end = (int) (y1 + m * (x1 - int_x1));
        double x1_gap = FRAC_PART(x1 + 0.5);
        int floor_y1 = (int) floor(y1_end);
        setPixel(int_x1, floor_y1, ONE_MINUS_FRAC_PART(y0_end) * x1_gap);
        setPixel(int_x1, floor_y1 + 1, FRAC_PART(y1_end) * x1_gap);
                 
        double current_y = y0_end + m;
        for (int current_x = int_x0 + 1; current_x < int_x1; current_x++) {
            setPixel(current_x, floor(current_y), ONE_MINUS_FRAC_PART(current_y));
            setPixel(current_x, floor(current_y) + 1, FRAC_PART(current_y));
            current_y += m;
        }
    } else {
        double inv_m = dx / (double) dy;
        
        int int_y0 = (int) floor(y0 + 0.5);
        double x0_end = x0 + inv_m * (y0 - int_y0);
        double y0_gap = ONE_MINUS_FRAC_PART(y0 + 0.5);
        int floor_x0 = (int) floor(x0_end);
        setPixel(floor_x0, int_y0, ONE_MINUS_FRAC_PART(x0_end) * y0_gap);
        setPixel(floor_x0 + 1, int_y0, FRAC_PART(x0_end) * y0_gap);
        
        int int_y1 = (int) floor(y1 + 0.5);
        double x1_end = (int) (x1 + inv_m * (y1 - int_y1));
        double y1_gap = FRAC_PART(y1 + 0.5);
        int floor_x1 = (int) floor(x1_end);
        setPixel(floor_x1, int_y1, ONE_MINUS_FRAC_PART(x0_end) * y1_gap);
        setPixel(floor_x1 + 1, int_y1, FRAC_PART(x1_end) * y1_gap);
        
        double current_x = x0_end + inv_m;
        for (int current_y = int_y0 + 1; current_y < int_y1; current_y++) {
            setPixel(floor(current_x), current_y, ONE_MINUS_FRAC_PART(current_x));
            setPixel(floor(current_x) + 1, current_y, FRAC_PART(current_x));
            current_x += inv_m;
        }
    }
}



/* This is a naive implementation that uses floating-point math
 * and "setPixel" which will need to be provided by the concrete
 * implementation.
 * 
 * Parameters:
 * 	x0, y0 - origin/center of circle
 *  radius - radius of circle
 * 
 * Returns: void
 */
void GraphicsContext::drawCircle(int x0, int y0, unsigned int radius)
{
	// This is a naive implementation that draws many line
	// segments.  Also uses floating point math for poor performance

	// also, large circle will be "jagged"
	
	// start at 0 degrees
	int oldx = radius;
	int oldy = 0;

	// go from 1 to 360 degrees
	for (int segment =1; segment<=360; segment += 1)
	{
		int newx = std::cos(segment*M_PI/180)*radius;
		int newy = std::sin(segment*M_PI/180)*radius;

		// hit four quadrants
		drawLine(x0+oldx,y0+oldy,x0+newx,y0+newy);
		
		oldx = newx;
		oldy = newy;
		
	}
	
	return;	
}

/**
 * Midpoint circle algorithm implementation (based on lecture and sample code
 * from Wikipedia.org)
 *
 * @param x0 x coordinate
 * @param y0 y coordinate
 * @param r Radius
 */

void GraphicsContext::mDrawCircle(int x0, int y0, unsigned int radius) {
    int p = 1 - radius;
    int x_adjustment = 1;
    int y_adjustment = -2 * radius;
    int current_x = 0, current_y = radius;
    
    setPixel(x0 - radius, y0);
    setPixel(x0 + radius, y0);
    setPixel(x0, y0 - radius);
    setPixel(x0, y0 + radius);
    
    while (current_x < current_y) {
        if (p >= 0) {
            current_y--;
            // Based on p_{i+1} = p_i = 2(x_{i+1} - y_{y+1}) + 1
            y_adjustment += 2;
            p += y_adjustment;
        }
        current_x++;
        // Based on p_{i+1} = p_i + 2x_{x+1} + 1
        x_adjustment += 2;
        p += x_adjustment;
        
        setPixel(x0 - current_x, y0 - current_y);
        setPixel(x0 - current_x, y0 + current_y);
        setPixel(x0 + current_x, y0 - current_y);
        setPixel(x0 + current_x, y0 + current_y);
        
        setPixel(x0 - current_y, y0 - current_x);
        setPixel(x0 - current_y, y0 + current_x);
        setPixel(x0 + current_y, y0 - current_x);
        setPixel(x0 + current_y, y0 + current_x);
    }
}



void GraphicsContext::endLoop()
{
	run = false;
}
