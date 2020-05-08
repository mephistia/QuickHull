#define _USE_MATH_DEFINES
#pragma once
class Point
{
public:
	Point();
	~Point();

	Point(float a, float b);


	Point operator = (const Point &P);

	bool operator == (const Point &P);

	bool operator < (const Point &P);

	double getAngleWith(Point &P);




	float x, y;
	double angle;
};

