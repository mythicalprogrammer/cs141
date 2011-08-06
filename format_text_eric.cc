// Eric Park
// 860766340
// epark
// CS 141 Summer 07
// Project 2

/*
  Hypothesis: Every odd number higher than 2 is a prime.

  Mathematician: 3 is a prime, 5 is a prime, and 7 is a prime. By induction,
                 all odd numbers are primes. The hypothesis must be true.
  Physicist: 3 is a prime, 5 is a prime, 7 is a prime, 9 is not a prime, 11 is
             a prime, and 13 is a prime. 5 of the 6 test cases agree with the
	     hypothesis, so it must be true.
  Engineer: 3 is a prime, 5 is a prime, 7 is a prime, 9 is an approximation of
            a prime, 11 is a prime, 13 is a prime. Therefore, this hypothesis
	    must be true.
  Computer Scientist: Segmentation fault
 */

#include <iostream>
#include <vector>
#include <string>

//////////////////////////////////////////////////////
///
///  Usage:
///
///    format_text text_width
///
///  reads lines of text on standard input, then
///  prints the text, formatted, on standard output.
///
///  line breaking is done to minimize a penalty function.
///
//////////////////////////////////////////////////////

using std::vector;
using std::string;

using std::cout;
using std::cerr;
using std::cin;
using std::endl;

#define DEFAULT_TEXT_WIDTH 60
#define INT_INFINITY (1<<30)

#define MIN(a,b) ((a)<(b)?(a):(b))

// trim trailing blanks from a given string
void
trim(string& s) {
  int i = s.size()-1;  
  while (i >= 0 && s[i] == ' ')
    --i;
  s.erase(i+1);
}

// return the penalty associated with a given line
int line_cost(string line, int text_width) {
  trim(line);
  int gap = text_width - line.size();
  if (gap < 0) gap = -gap+50;
  return gap*gap*gap;
}

//
// given a sequence of n words, and integer text_width
//
// find the minimum total penalty possible for 
// any formatting of words[0], words[1], ..., words[n-1]
//
// return the formatted text as a string
//

string
format_paragraph(vector<string> words, int text_width) {
  
  int n = words.size();

  int cost_table[n];
  string para_table[n];  

  // goal:
  // cost_table[j] = min cost for words[j..n-1] 
  // given that words[j] starts a line
  //
  // and para_table[i] = the formatted string that realizes cost_table[i]

  // initialize

  for (int i = 0;  i < n;  ++i) {
    cost_table[i] = INT_INFINITY;
    para_table[i] = "ERROR!";
  }


  // first, for j such that words j,j+1,...,n-1 all fit on a line
  // set cost_table[j] = 0
  // (special case: word[n-1] doesn't fit on a line, still allow it)

  // YOUR CODE HERE
  int length = words[n - 1].length();
  para_table[n - 1] = words[n - 1];
  cost_table[n - 1] = 0;

  for(int j = n - 2; j >= 0; j--)
    {
      length += words[j].length() + 1;
      if(length <= text_width)
	{
	  cost_table[j] = 0;
	  para_table[j] = words[j] + " " + para_table[j + 1];
	}
      else
	break;
    }

  // next, for i = n-2, n-3, ..., 0, compute cost_table[i]
  // (and para_table[i]) using the recurrence,
  // based on the values cost_table[k+1] for k = j,j+1,...n-2

  // YOUR CODE HERE
  // cost(j) = min{cost(k+1)+pen(j,k):j<=k<=n-2}
  /*
    fill_cell(j)
    {
      k = get_min_k(...);
      cost_vec[j] = cost_vec[k+1] + pen(j,k);
      para_vec[j] = words[j...k] + para_vec[k+1]
    }
  */
  for(int j = n - 2; j >= 0; j--)
    {
      if(cost_table[j] != 0)
	{
	  int min_cost = line_cost(words[j], text_width) + cost_table[j + 1];
	  int new_cost = 0;
	  length = words[j].size() + 1;
	  
	  string temp = words[j] + " ";
	  string word;
	  int min_k;
	  for(int k = j + 1; k < n; k++)
	    {
	      length += words[k].size() + 1;
	      if(text_width - length + 1 >= 0)
		{
		  temp += words[k] + " ";
		  new_cost = line_cost(temp, text_width) + cost_table[k + 1];
		  if(new_cost < min_cost)
		    {
		      min_cost = new_cost;
		      word = temp;
		      min_k = k;
		    }
		}
	    }
	  
	  cost_table[j] = line_cost(word, text_width) + cost_table[min_k + 1];
	  para_table[j] = word + "\n" + para_table[min_k + 1];

	  //cout << cost_table[j] << " " << para_table[j] << endl;
	}
    }
  para_table[0] += "\n";

  return para_table[0];
}

int main(int argc, char *argv[]) {

  int text_width = DEFAULT_TEXT_WIDTH;

  if (argc >= 2) {
    text_width = atoi(argv[1]);
  }

  // read, format, and output a sequence of paragraphs
  // (new paragraph starts with a word "<p>")

  while (std::cin) {

    // get paragraph
    vector<string> words;
    while (std::cin) {
      string word;
      std::cin >> word;
      if (word.empty()) break;
      if (word == "<p>") break;
      words.push_back(word);
    }

    // output paragraph, formatted
    if (words.empty()) continue;
    cout << format_paragraph(words, text_width);
    cout << endl;
  }
}
