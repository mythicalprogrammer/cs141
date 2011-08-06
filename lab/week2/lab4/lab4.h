// CS 141 Lab 4 header file
// Contains Tree, PriorityQueue, and BitWriter class definitions, along with
// output functions for frequency tables and Huffman encoding maps.

#ifndef LAB4_H
#define LAB4_H

#include <iostream>
#include <map>
#include <queue>

///////////////////////////////////////////////////////////////////////////////
// Tree (node) class for Huffman coding.
// Note that all data is stored in the leaves of the tree (and is public).

class Tree
{
public:
  // Construct a new single-node binary tree storing the specified character.
  Tree(char = '\0');

  // Destruct tree by deleting left and right subtrees (if any).
  ~Tree();

  // Return the height of the tree.
  int height() const;

  // Each node in the tree stores at most one character, and pointers to the
  // left and right subtrees.
  // For internal nodes: left and/or right is non-NULL; c is undefined
  // For leaves: c is the character represented; both left and right are NULL
  char c;
  Tree *left;
  Tree *right;
};


///////////////////////////////////////////////////////////////////////////////
// Priority queue class for Huffman coding (min-heap).
// This is basically a wrapper around STL's priority queue (max-heap).

class PriorityQueue
{
public:
  // Insert tree t with priority key into the priority queue.
  void insert(Tree *t, unsigned int key);

  // Remove and return the data item at the top of the priority queue.
  Tree *removeMin();

  // Return the number of items in the priority queue.
  size_t size() const;

  // Return the priority (key) of the item at the top of the priority queue,
  // without removing it from the queue.  Undefined behavior if size() < 1.
  unsigned int minKey() const;

protected:
  std::priority_queue<std::pair<unsigned int, Tree*>,
		 std::vector<std::pair<unsigned int, Tree*> >,
		 std::greater_equal<std::pair<unsigned int, Tree*> > > q;
};


///////////////////////////////////////////////////////////////////////////////
// Bit writer class for Huffman coding.
// Writes variable-length strings of ones and zeros as 8-bit character output.

class BitWriter
{
public:
  // Construct a new bit writer on the specified output stream.
  BitWriter(std::ostream &);

  // Destruct bit writer, flushing any remaining data to stream (if possible).
  ~BitWriter();

  // Write (the binary representation of) string of 1s and 0s to the output.
  // Characters other than '1' and '0' in the string are ignored.
  void write(std::string);

  // Flush output buffer, appending 0 bits as necessary to output final char.
  // Upon exit, bitsLeft() == 0.
  void flush();

  // Return the number of bits that must be written in order to fill the
  // current character, causing it to be written to the output stream.
  size_t bitsLeft() const;

protected:
  unsigned char bitBuffer;
  size_t bitBufferFree;
  std::ostream *out;
};


///////////////////////////////////////////////////////////////////////////////
// Functions to output frequency tables and Huffman encoding maps.

// Dump the table of characters and their frequencies to standard output.
// Characters with a frequency of zero are not included in the output.
void showFreqTable(const unsigned int count[]);

// Dump Huffman encoding to standard output.
// Binary Huffman code is represented by a string of zeros and ones.
void showEncoding(const std::map<char, std::string>& encoding);

#endif /* LAB4_H */

