// CS 141 Lab 6 Tree and PriorityQueue class implementations
// Written by Karl Doering 

#include <iostream>
#include <iomanip>
#include "lab3.h"

using namespace std;


///////////////////////////////////////////////////////////////////////////////
// Construct a new single-node binary tree storing the specified character.

Tree::Tree(char c)
{
  this->c = c;
  left = NULL;
  right = NULL;
}


///////////////////////////////////////////////////////////////////////////////
// Destruct tree by deleting left and right subtrees (if any).

Tree::~Tree()
{
  if (left)
  {
    delete left;
  }
  if (right)
  {
    delete right;
  }
}


///////////////////////////////////////////////////////////////////////////////
// Return the height of the tree.

int Tree::height() const
{
  int leftHt = 0, rightHt = 0;

  // Recursively compute heights of left and right subtrees (if present).
  if (left)
  {
    leftHt = left->height();
  }
  if (right)
  {
    rightHt = right->height();
  }

  // Return one more than the maximum of the left and right subtree heights.
  if (leftHt > rightHt)
  {
    return leftHt + 1;
  }
  else
  {
    return rightHt + 1;
  }  
}


///////////////////////////////////////////////////////////////////////////////
// Insert tree t with priority key into the priority queue.

void PriorityQueue::insert(Tree *t, unsigned int key)
{
  pair<unsigned int, Tree*> p(key, t);
  q.push(p);
}


///////////////////////////////////////////////////////////////////////////////
// Remove and return the data item at the top of the priority queue.

Tree *PriorityQueue::removeMin()
{
  pair<unsigned int, Tree*> p = q.top();
  q.pop();

  return p.second;
}


///////////////////////////////////////////////////////////////////////////////
// Return the number of items in the priority queue.

size_t PriorityQueue::size() const
{
  return q.size();
}


///////////////////////////////////////////////////////////////////////////////
// Return the priority (key) of the item at the top of the priority queue.

unsigned int PriorityQueue::minKey() const
{
  pair<unsigned int, Tree*> p = q.top();
  return p.first;
}


///////////////////////////////////////////////////////////////////////////////
// Return character c as a string, filtering out non-displayable characters.

string toString(char c)
{
  if (c < ' ')
  {
    // Decode the special character...
    switch(c)
    {
      case '\0': return "\\0";  // ASCII  0 is null character
      case '\a': return "\\a";  // ASCII  7 is alert (bell)
      case '\b': return "\\b";  // ASCII  8 is backspace
      case '\t': return "\\t";  // ASCII  9 is horizontal tab
      case '\n': return "\\n";  // ASCII 10 is newline (line feed)
      case '\v': return "\\v";  // ASCII 11 is vertical tab
      case '\f': return "\\f";  // ASCII 12 is form feed
      case '\r': return "\\r";  // ASCII 13 is carriage return
      default  : return "--" ;  // some other special character 1-6 or 14-31
    }
  }
  else
  {
    // Just return the character (as a string)
    string s;
    s = c;
    return s;
  }
}


///////////////////////////////////////////////////////////////////////////////
// Dump the table of characters and their frequencies to standard output.
// Characters with a frequency of zero are not included in the output.

void showFreqTable(const unsigned int count[])
{
  unsigned int i, totalNumChars = 0;

  // Add up the total characters seen
  for (i = 0; i <= UCHAR_MAX; ++i)
  {
    totalNumChars += count[i];
  }

  // Quit now if there's nothing to output
  if (totalNumChars == 0)
  {
    cout << "No characters read." << endl;
    return;
  }

  // Print table header
  cout << "ASCII   char   count   frequency\n"
       << "-----   ----   -----   ---------\n"
       << setiosflags(ios::fixed) << setprecision(2);

  // Print table entries, skipping characters which did not occur at all
  for (i = 0; i <= UCHAR_MAX; ++i)
  {
    if (count[i] == 0)
    {
      continue;
    }

    cout << setw(4) << i            // ASCII code of character
	 << setw(7) << toString(i)  // string representation of character
	 << setw(9) << count[i]     // raw character count
	 << setw(11) << 100.0 * count[i] / totalNumChars << '%' << endl;
  }

  // Print table footer
  cout << "               -----   ---------\n"
       << setw(20) << totalNumChars << setw(11) << 100.0 << '%' << endl;
}


///////////////////////////////////////////////////////////////////////////////
// Dump Huffman encoding to standard output.

void showEncoding(const map<char, string>& encoding)
{
  // Quit now if there's nothing to output
  if (encoding.empty())
  {
    cout << "No characters in alphabet to encode." << endl;
    return;
  }

  // Print table header
  cout << "ASCII   char   encoding\n"
       << "-----   ----   --------\n"
       << setiosflags(ios::fixed) << setprecision(2);

  // Print table entries
  for (map<char, string>::const_iterator i = encoding.begin();
       i != encoding.end(); ++i)
  {
    unsigned int c = (*i).first;

    cout << setw(4) << c            // ASCII code of character
	 << setw(7) << toString(c)  // string representation of character
	 << "    " << (*i).second << endl;
  }
}

