// CS 141 Lab 6 template
// Your header goes here (include name, login, and lab section)
// Charles Ma, Anh Quoc Doan
// cma,qdoan
// Lab Section 001
// For this week's lab, you need to at the minimum implement buildFreqTable
// and buildHuffmanTree.

#include <iostream>
#include <fstream>
#include <map>

// The Tree and PriorityQueue classes are defined here, as well as functions
// to output frequency tables and encodings.  (Read the header file.)
#include "lab3.h"

using namespace std;



///////////////////////////////////////////////////////////////////////////////
// Build a table of frequencies of all characters readable from input.
// count is an array from 0..UCHAR_MAX, with element i representing the
// number of occurrences of the character static_cast<char>(i) in the input.

void buildFreqTable(istream &input, unsigned int count[])
{
  // TODO: Initialize count array 
  for(unsigned int i = 0; i <= UCHAR_MAX; i++)
    count[i] = 0;

  // TODO: Read characters from input and update count array
  //char temp;
  char c;
  while(input.get(c))
    {
      count[static_cast<char>(c)]++;
    }
}


///////////////////////////////////////////////////////////////////////////////
// Build Huffman tree from frequency count, using the algorithm given on page
// freq is the array 0..UCHAR_MAX of frequencies of characters.
// The constructed Huffman tree is returned (Tree *); caller is responsible
// for freeing memory used when done.

Tree *buildHuffmanTree(const unsigned int freq[])
{
  // TODO: Initialize a priority queue
  PriorityQueue huff;
  // TODO: For each character in the input alphabet, create a single-node
  // binary tree storing that character, and insert it into the priority
  // queue, using that character's frequency as the key
  for(unsigned int i = 0; i < UCHAR_MAX; i++)
    {
      if(freq[i] != 0)
      huff.insert(new Tree(i), freq[i]); 
    }

  // TODO: If the queue is empty, stop now as there's nothing to encode
  if(huff.size() == 0)
    return NULL;
  // TODO: While there are at least two trees in the queue, extract the two
  // trees and their frequencies, and create a new binary tree with the
  // extracted trees as subtrees.  Insert this new tree back into the priority
  // queue, with a key of the sum of the frequencies.
  while(huff.size() >= 2)
    {
      
      int new_key = huff.minKey();
      Tree *a = huff.removeMin();
      new_key += huff.minKey();
      Tree *b = huff.removeMin();
      Tree *c = new Tree();
      c->left = a;
      c->right = b;
      huff.insert(c, new_key);
    }
      
  // TODO: Remove the final tree from the priority queue and return it
  return huff.removeMin();
}


///////////////////////////////////////////////////////////////////////////////
// Generate Huffman encoding from the Huffman (sub)tree t.
// encoding is represented as a map from the character being encoded to a
// string of 0s and 1s representing the Huffman code.
// encoding is initially empty; entries are added for every leaf encountered
// as the tree is traversed.
// prefix contains the portion of the code from the root of the Huffman tree
// to the current (sub)tree t being processed.  (Hint: implement recursively.)

void generateEncoding(Tree *t, map<char, string>& encoding, string prefix = "")
{
  if(t == NULL)
    return;
  // TODO: Generate encodings for left and right subtrees, where present
  if(t->c == '\0')
    {
      // if(t->left == NULL && t->right == NULL)
      generateEncoding(t->left, encoding, prefix+"0");
      generateEncoding(t->right, encoding,prefix+"1");
      
    }
  else
  // TODO: Otherwise, if this is a leaf node, add the encoding for the
  // character represented by this node to the encoding map
    encoding[t->c] = prefix;
}


///////////////////////////////////////////////////////////////////////////////
// Main reads text from either stdin or file, then builds and displays
// frequency count and Huffman encoding.

int main(int argc, char *argv[])
{
  unsigned int freqs[UCHAR_MAX + 1];
  ifstream infile;

  // If an argument was specified, assume a filename and attempt to read
  // input from it
  if (argc > 1)
  {
    infile.open(argv[1]);
    if (!infile)
    {
      cerr << "Unable to open " << argv[1] << " for input.\n";
      return 1;
    }

    // Build frequency count from file input
    buildFreqTable(infile, freqs);
  }
  else
  {
    cout << "Enter text on standard input (Ctrl-D by itself to stop)." << endl;

    // Build frequency count from standard input
    buildFreqTable(cin, freqs);
  }

  // Dump frequency count to standard output
  showFreqTable(freqs);

  // Build Huffman tree from frequency count
  Tree *huffmanTree = buildHuffmanTree(freqs);

  // Quit now if Huffman tree generation failed for some reason
  if (!huffmanTree)
  {
    cerr << "No Huffman tree generated.\n";
    if (infile)
    {
      infile.close();
    }    
    return 1;
  }

  // Generate Huffman encoding from Huffman tree
  map<char, string> encoding;
  generateEncoding(huffmanTree, encoding);

  // Dump Huffman encoding to standard output
  cout << endl;
  showEncoding(encoding);

  // Actually do Huffman encoding of input, and print compression statistics
  // Will be done in next week's lab...
  //huffmanEncode(input, encoding, output);

  // Close input file (if there is one)
  if (infile)
  {
    infile.close();
  }

  // Free memory allocated from building Huffman tree
  delete huffmanTree;
  
  return 0;
}

