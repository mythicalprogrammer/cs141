// CS 141 Lab 2 template
// Your header goes here (include name, login, and lab section)

#include <iostream>
#include <sstream>
#include "Integer.h"

using namespace std;

// PART 1: Extended Euclid's algorithm
// Compute d, x, and y such that d = gcd(a, b) = ax + by for given a and b.
void extended_euclid(const Integer &a, const Integer &b,
		     Integer &d, Integer &x, Integer &y)
{
  // Your code goes here

  //Input a,b 
  //Output x,y,d s.t. d = gcd(a,b) = ax + by

  /*
                   x  y  d
  if b = 0 return (1, 0, a) --->   return (a,b,d,x,y) 
                            --->   return (a,0,a,1,y)

  else
  
  (x', y', d ) = extended_euclid( b , a mod b)
  return (y', x' - y' [a/b], d)
          x     y            d

  */

  Integer x_p, y_p;

  if (b == 0)              //base case
    {
      x = 1;
      y = 0;
      d = a;
      
    }
  else
   {
     x_p = x; 
     y_p = y; 
     extended_euclid (b, a % b, d, x_p, y_p);

     x = y_p; 
     y = x_p - y_p * (a/b);      
     
   }
  
 
}


// PART 2: Fast exponentiation algorithm
// Return x to the power of y (modulo n).
Integer fast_exp(const Integer &x, const Integer &y, const Integer &n)
{
 // Your code goes here
  Integer z,even;
  if (y == 0)
    return 1;  
  z = fast_exp(x,y/2,n);


  if ((y%2) == 0)
    return ((z*z)% n);
  else
    return ((x*z*z)%n);

 
  

} 


// Main reads a sequence of numbers from standard input and passes them to
// the appropriate algorithm (extended Euclid's or fast exponentiation).
int main()
{
  const string PROMPT = "> ";
  string input_line;
  Integer i, j, n;

  cout << "\nTo invoke ExtendedEuclid(a, b), enter the two integers a and b\n"
       << "together on a single line, with a and b separated by whitespace.\n"
       << "\nTo invoke FastExponentiation(x, y, n), enter the three integers\n"
       << "x, y, and n together on a single line, separated by whitespace.\n"
       << "\nCtrl-D at the prompt exits.\n\n"
       << PROMPT;

  // Process input line by line, until no more lines available to be read
  while (getline(cin, input_line))
  {
    stringstream tokenizer(input_line);

    // Skip blank lines, comments, and lines with fewer than two integers
    if (input_line.find("#") == 0 || !(tokenizer >> i >> j))
    {
      cout << PROMPT;
      continue;
    }

    if (tokenizer >> n)
    {
      // Three-number input: run fast exponentiation
      cout << i << " ^ " << j << " mod " << n << " = " << fast_exp(i, j, n)
	   << endl;
    }
    else
    {
      // Two-number input: run extended Euclid
      Integer d, x, y;
      extended_euclid(i, j, d, x, y);
      cout << "a=" << i << " b=" << j << " d=" << d << " x=" << x << " y=" << y
	   << endl;
    }

    cout << PROMPT;
  }

  cout << endl;

  return 0;
}

