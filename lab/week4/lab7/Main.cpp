//include your first name, last name, login, student id here


#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cfloat>
//#include "Point.h"
#include "pair.h"

using namespace std;

//merges two subsets in increasing order
void merge_x(vector<Point> &points, int from, int mid, int to)
{

	const int n = to - from + 1;
	vector<Point> temp(n);
	
	int i, j , k;
	for(k = 0, i = from, j = mid + 1; i  <= mid && j <= to; k++)
	{
		if(points[i].x < points[j].x)
		{
			temp[k] = points[i];
			i++;
		}
		else
		{
			temp[k] = points[j];
			j++;
		}	
	}
	
	for(; i <= mid; i++, k++)
	{
		temp[k] = points[i];
	}
	
	for(; j <= to; j++, k++)
	{
		temp[k] = points[j];
	}
	
	for(k = 0; k < n; k++)
	{
		points[k + from] = temp[k];
	}

	return ;
}

//sorts a set of points by x coordinate in increasing order
void merge_sort_x(vector<Point> &points, int from, int to)
{
	if(from == to)
	{
		return;
	}
	
	int mid = (to + from)/2;
	merge_sort_x(points, from, mid);
	merge_sort_x(points, mid + 1, to);
	merge_x(points, from, mid, to);
	
	return ;

}
//merges two subset in increasing order
void merge_y(vector<Point> &points, int from, int mid, int to)
{
	const int n = to - from + 1;
	vector<Point> temp(n);
	
	int i, j , k;
	for(k = 0, i = from, j = mid + 1; i  <= mid && j <= to; k++)
	{
		if(points[i].y < points[j].y)
		{
			temp[k] = points[i];
			i++;
		}
		else
		{
			temp[k] = points[j];
			j++;
		}
	}
	
	for(; i <= mid; i++, k++)
	{
		temp[k] = points[i];
	}
	
	for(; j <= to; j++, k++)
	{
		temp[k] = points[j];
	}
	
	for(k = 0; k < n; k++)
	{
		points[k + from] = temp[k];
	}

}

//sorts set of points by y coordinate in increasing order
void merge_sort_y(vector<Point> &points, int from, int to)
{
	if(from == to)
	{
		return;
	}
	
	int mid = (to + from)/2;
	merge_sort_y(points, from, mid);
	merge_sort_y(points, mid + 1, to);
	merge_y(points, from, mid, to);
	return;


}

//finds which pair has the shortest distance
Pair min(Pair a, Pair b) 
{ 
	if(a.d_min > b.d_min )
	{
		return b;
	}
	else 
	{
		return a;
	}
}


//finds closest pair in a set of points
//it takes a vector of points; when it is called first time from main, "to" must be set to vector's size minus 1 (i.e. to the last element of vector)

Pair cp(vector<Point> &point_set, int from, int to)
{
  int n = to - from + 1;
  if(n <= 1)
    {
      return Pair();
    }
  else if(n == 2)
    {
      return Pair(point_set[from], point_set[to]);
    }
  else
    {
      
      merge_sort_x(point_set, from, to);
      int mid = (from + to)/2;
      double middle_line = (point_set[mid].x + point_set[mid+1].x) /2 ;
      
      //recursively call cp to find the min in the left part 
      Pair min_L = cp(point_set, from, mid);
      
      //recursively call cp to find the min in the right part
      Pair min_R = cp(point_set, mid+1, to);
      
      
      /*
	your code goes here	
	
	To define a middle strip which is with in delta to the middle-line from both sides
	
	To find out the min-distance pair in the middle strip
	
	Finally return the overall min-distance pair
		
	Note, you may want to use the merge_sort_y function that is provided previously.
	
	
      */
      Pair min_dist;
      return min_dist;
    }
}

int main(int argc, char* argv[])
{
	string file_input = argv[1];
	ifstream instr;
	instr.open(file_input.c_str(), ios::in);
	string aline;
	
	//read points from input file into a set
	//points in input file should be in the format: x y in each line
	vector<Point> aSet;
	
	while(!instr.eof())
	{
		getline(instr, aline);
		if(!aline.empty())
		{
			Point apoint = Point(aline);
			aSet.push_back(apoint);
		}
	}
	instr.close();

	//call cp to find the closest pair among the points from the file
	Pair res = cp(aSet, 0, aSet.size() - 1) ;

	cout << "The closest pair is " << res << endl;
	return 0;
}
