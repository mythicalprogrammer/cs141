// CS 141 Lab 4 Tree, PriorityQueue, and BitWriter class implementations
// Written by Karl Doering for Spring 2005 lab sections

#include <iostream>
#include <iomanip>
#include "lab4.h"

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
// Construct a new bit writer on the specified output stream.

BitWriter::BitWriter(ostream &out)
{
  bitBuffer = '\0';
  bitBufferFree = CHAR_BIT;
  this->out = &out;
}


///////////////////////////////////////////////////////////////////////////////
// Destruct bit writer, flushing any remaining data to stream (if possible).

BitWriter::~BitWriter()
{
  if (*out)
  {
    flush();
  }
}


///////////////////////////////////////////////////////////////////////////////
// Write (the binary representation of) string of 1s and 0s to the output.
// Characters other than '1' and '0' in the string are ignored.

void BitWriter::write(string bitstring)
{
  for (string::iterator c = bitstring.begin(); c != bitstring.end(); ++c)
  {
    // Ignore anything in the string other than zeros and ones.
    if (!(*c == '0' || *c == '1'))
    {
      continue;
    }

    // Put the bit in the buffer.
    bitBuffer |= *c & 1;
    bitBufferFree--;

    // If the buffer is now full, output it; otherwise, just shift left by one
    // to make room for the next bit.
    if (!bitBufferFree)
    {
      out->put(bitBuffer);
      bitBuffer = '\0';
      bitBufferFree = CHAR_BIT;
    }
    else
    {
      bitBuffer <<= 1;
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
// Flush output buffer, appending 0 bits as necessary to output final char.
// Upon exit, bitsLeft() == 0.

void BitWriter::flush()
{
  if (bitBufferFree != CHAR_BIT)
  {
    bitBuffer <<= bitBufferFree - 1;
    out->put(bitBuffer);
    // bitBuffer = '\0' not needed here as we're shifted left by at least 1 bit
    bitBufferFree = CHAR_BIT;
  }

  // Now that we're finished writing to the stream, flush the stream itself.
  out->flush();
}


///////////////////////////////////////////////////////////////////////////////
// Return the number of bits that must be written in order to fill the
// current character, causing it to be written to the output stream.

size_t BitWriter::bitsLeft() const
{
  return bitBufferFree % CHAR_BIT;
}


///////////////////////////////////////////////////////////////////////////////
// Return character c as a string, filtering out non-displayable characters.

string toString(char c)
{
  if (c < ' ' || c > 126)
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
    unsigned int c = (*i).first & 0xff;

    cout << setw(4) << c            // ASCII code of character
	 << setw(7) << toString(c)  // string representation of character
	 << "    " << (*i).second << endl;
  }
}

