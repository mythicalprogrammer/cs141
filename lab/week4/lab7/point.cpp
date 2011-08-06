#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "point.h"

using namespace std;
	
Point::Point(string aline)
{
	istringstream in(aline);
	double xx, yy;
	in >> xx >> yy;
	
	x = xx; y = yy;
}

std::ostream& operator <<(std::ostream &s, Point a)
{
	s << a.x << " " << a.y; 
	return s; 
} 

std::istream& operator >>(std::istream &s, Point &a)
{
		string p;
		getline(s, p);
		istringstream instr(p);
		double x, y;
		instr >> x >> y;
		a = Point(x, y);
		return s;
}

