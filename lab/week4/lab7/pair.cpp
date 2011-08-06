#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include "pair.h"

using namespace std; 

std::ostream& operator <<(std::ostream &s, Pair c)
{
	s << "(" << c.a.x << ", " << c.a.y << ") (" << c.b.x << ", " << c.b.y << "), " << "d = " << c.d_min ; 
	return s; 
} // cout << c;


Pair::Pair(Point aa, Point bb) 
{
	a = aa; b = bb;
	d_min = sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y),2)); 
};

Pair::Pair()
{
	a = Point(0, 0); 
	b = Point(0,0); 
	d_min = DBL_MAX; 
}
