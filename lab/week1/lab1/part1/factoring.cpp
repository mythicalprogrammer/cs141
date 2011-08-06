// CS 141 Lab 1 template
// Your header goes here (include name, login, and lab section)

#include <iostream>
#include <iomanip>
#include <ctime>
#include "Integer.h"

using namespace std;


// Factoring algorithm 1: divide by all numbers from 2 to n-1
void factoring1(Integer /*n*/)
{ /*
  // Your code goes here

  Integer i;  

  //terminating condition
  if( n == 1 )
    return;
  //iterator
  for( i = 2; i < n; ++i )
  {
    
    if ( n%i == 0 )
      break;
     
  }
  //recursive
  factoring1(n/i);
  */
}



// Factoring algorithm 2: divide by all numbers from 2 to sqrt(n)
void factoring2(Integer n)
{
  // Your code goes here
  Integer i;  

  //terminating condition
  if( n == 1 )
    return;
  //iterator
  for( i = 2; i <= sqrt(n); ++i )
  {
    
    if ( n%i == 0 )
      break;
     
  }
  //recursive
  factoring2(n/i);

}


// Factoring algorithm 3: improvement on (2) using array of primes
void factoring3(Integer n)
{
  // Your code goes here


  static Integer prime_array[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
  static const int array_size = 10;
  Integer i;  


  //terminating condition
  if( n == 1 ) 
    return;
  //iterator
  for( i = 0; i < array_size; ++i )
  {
    if ( n % prime_array[i] == 0 )
      {
	break;
      }
  }

  if (i == array_size)
  {
    Integer sqrt_n = sqrt(n);
    for (i = 31; i < sqrt_n; ++i)
    {
     if ( n % i == 0 )
      {
	break;
      } 
    }
  }
  else
  {
    i = prime_array[i];
  }
  //recursive
  factoring3(n/i);




}


// Factoring algorithm 4: your own improvement


void factoring4(Integer n)
{
  // Your code goes here
 
  //COmments -- THIS IS MY IMPROVEMNT 
  //1. I just add more number into the array.
  //2. And skip multiple of twos
  //<(^_^)> (^_)>> <(^_^)> <<(_^) Kirby dance
  static Integer prime_array[30] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 
				    53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 
				    109, 113};
  static const int array_size = 30;
  Integer i;  


  //terminating condition
  if( n == 1 ) 
    return;
  //iterator
  for( i = 0; i < array_size; ++i )
  {
    if ( n % prime_array[i] == 0 )
      {
	break;
      }
  }

  if (i == array_size)
  {
    Integer sqrt_n = sqrt(n);
    for (i = 113; i < sqrt_n; i+=2)
    {
      if (n % i == 0 )
      {
	break;
      } 
    }
  }
  else
  {
    i = prime_array[i];
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

  cout << setiosflags(ios::fixed) << setprecision(2);

  cout << "Factoring 1 elapsed time: " << timing(factoring1, n1, n2) << " sec"
       << endl;

  cout << "Factoring 2 elapsed time: " << timing(factoring2, n1, n2) << " sec"
       << endl;

  cout << "Factoring 3 elapsed time: " << timing(factoring3, n1, n2) << " sec"
       << endl;

  cout << "Factoring 4 elapsed time: " << timing(factoring4, n1, n2) << " sec"
       << endl;

  return 0;
}

