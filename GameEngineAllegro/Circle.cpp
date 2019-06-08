#include "pch.h"

#include "Point.cpp"
#include "Shape.cpp"

class Ellipse : public Shape
{
public:
	double Radius;

	/*virtual Point GetF1() = 0;
	virtual Point GetF2() = 0;*/

	//virtual operator StaticEllipse() const = 0;

	virtual ~Ellipse() {};

protected:
	Ellipse() {};
};

class StaticEllipse : Ellipse
{
private:
	Point Focus1;
	Point Focus2;

public:
	StaticEllipse(Point focus1, Point focus2) : Focus1(focus1), Focus2(focus2) {	}

};

class MovingEllipse : public Ellipse
{
private:
	std::function<std::tuple<Point, Point>()> Foci;

public:
	MovingEllipse(std::function<std::tuple<Point, Point>()> foci) : Foci(foci) {}

	operator StaticEllipse() const
	{
		std::tuple<Point, Point> foci = Foci();
		return StaticEllipse(std::get<0>(foci), std::get<1>(foci));
	}
};