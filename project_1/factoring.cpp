// CS 141 Lab 1 template
// Your header goes here (include name, login, and lab section)

#include <iostream>
#include <iomanip>
#include <ctime>
#include "Integer.h"

using namespace std;

// Factoring algorithm 4: your own improvement


void factoring4(Integer n)
{
  // Your code goes here
 
  //COmments -- THIS IS MY IMPROVEMNT 
  //1. I just add more number into the array.
  //2. And skip multiple of twos
  //<(^_^)> (^_)>> <(^_^)> <<(_^) Kirby dance
  /*  static Integer prime_array[168] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 
				    53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 
				    109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
                                    173, 179, 181, 191, 193, 197, 199, 211, 223, 227,
                                    229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
                                    281, 283, 293, 307, 311, 313, 317, 331, 337, 347,
                                    349, 353, 359, 367, 373, 379, 383, 389, 397, 401,
                                    409, 419, 421, 431, 433, 439, 443, 449, 457, 461,
                                    463, 467, 479, 487,	491, 499, 503, 509, 521, 523,
                                    541, 547, 557, 563,	569, 571, 577, 587, 593, 599,
                                    601, 607, 613, 617, 619, 631, 641, 643, 647, 653,
                                    659, 661, 673, 677, 683, 691, 701, 709, 719, 727,
                                    733, 739, 743, 751,	757, 761, 769, 773, 787, 797,
                                    809, 811, 821, 823,	827, 829, 839, 853, 857, 859,
                                    863, 877, 881, 883,	887, 907, 911, 919, 929, 937,
                                    941, 947, 953, 967, 971, 977, 983, 991, 997};
  static const int array_size = 168; */
  /*  Integer i;  


  //terminating condition
  if( n == 1 ) 
    return;

    Integer sqrt_n = sqrt(n);
    for (i = 2; i < sqrt_n; i+=2)
    {
      if (n % i == 0 )
      {
	cout<<i<<endl;
	break;
      } 
    } 

  //recursive
  factoring4(n/i); */
  Integer i;  

  //terminating condition
  if( n == 1 )
   {
     //cout<<i<<endl;
     return;
   } 
  //iterator
  for( i = 2; i <= sqrt(n); ++i )
  {
    //cout<<i<<endl;
    if ( n%i == 0 )
      {  //cout << i <<endl;
    cout << i <<endl;
    cout<< n/i<<endl;
      return;
    } 
  }
  //recursive
  factoring4(n/i);
} 




// Run factoringx function with all numbers between n1 and n2 inclusive.
// Return the total elapsed execution time in seconds.
double timing(void (*factoringx)(Integer), Integer n1, Integer n2)
{
  clock_t start, finish;

  start = clock();                  // get starting time

  for (Integer i = n1; i <= n2; ++i)
    (*factoringx)(i);

  finish = clock();                 // get finishing time

  double elapsed = finish - start;  // determine elapsed time

  return elapsed / CLOCKS_PER_SEC;
}


// Main runs each of the four algorithms and prints the elapsed execution
// time for each algorithm run.
int main(int argc, char *argv[])
{
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " start_num end_num" << endl;
    return 1;
  }

  Integer n1 = argv[1];
  Integer n2 = argv[2];


  cout << "Factoring 4 elapsed time: " << timing(factoring4, n1, n2) << " sec"
       << endl;

  return 0;
}

