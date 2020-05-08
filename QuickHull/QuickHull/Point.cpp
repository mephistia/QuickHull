#include "Point.h"
#include <math.h>   



Point::Point()
{
}


Point::~Point()
{
}

Point Point::operator=(const Point & P)
{
	x = P.x;
	y = P.y;
	angle = P.angle;
	return *this;
}

bool Point::operator==(const Point & P)
{
	return (x == P.x && y == P.y);
}

bool Point::operator<(const Point & P)
{
	return(angle < P.angle);
}

double Point::getAngleWith(Point & P)
{
	if (P.x == x) { 
		return 0; 
	}

	return atan2(P.y - y, P.y - x) * 180 / M_PI;

}

Point::Point(float a, float b)
{
	x = a;
	y = b;
	angle = 0;
}
