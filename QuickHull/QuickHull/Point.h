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

	float getAngleWith(Point &P);




	float x, y, angle;
};

