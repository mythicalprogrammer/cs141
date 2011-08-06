// CS 141 Lab 1 template
// Your header goes here (include name, login, and lab section)

#include <iostream>
#include <iomanip>
#include <ctime>
#include "Integer.h"
#include <fstream>

using namespace std;

// Factoring algorithm 4: your own improvement


Integer factoring4(Integer n)
{

  Integer i;  


 
  //terminating condition
  /* if( n == 1 )
   {

     return;
     } */ 

  //iterator
  for( i = sqrt(n); i != 2 ;  i--) //= prevprime(i) )
  {

    if ( n%i == 0 )
      {  

	break;
    } 
  }
  //recursive
  //factoring4(n/i);

  return i;
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


  /*cout << "Factoring 4 elapsed time: " << timing(factoring4, n1, n2) << " sec"
       << endl;*/
  Integer NUM = factoring4(n2);
  cout << "Factoring " << n1 <<" " << n2 <<" is " << NUM<<" "<< n2/NUM<<endl;

  return 0;
}

