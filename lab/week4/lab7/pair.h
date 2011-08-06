#include<cmath>
#include "point.h"
#include <cfloat>

using namespace std;

#ifndef Pair_H
#define Pair_H



class Pair{
	public:
	
	Pair(Point aa, Point bb) ;
	Pair();

	friend std::ostream& operator <<(std::ostream &s, Pair a); 
	
	Point a;
	Point b;
	double d_min; //distance between a and b
};

#endif;
